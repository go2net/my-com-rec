/*--------------------------------------------------------------------------*/
/**@file    id3.h
   @brief   ID3V2���ļ���Ϣͷ
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/

#include "id3.h"
#include "lcd.h"
#include "uart.h"

extern u8 _xdata decode_buffer[];
extern DECODER_MSG _xdata *dec_msg;
extern FSAPIMSG _pdata fs_msg;
extern u8 music_type;
extern FIL xdata fat_ptr1;
#define ID3_DISP_BUF_LEN				128

/** ���ID3V2��Ϣ�Ľṹ����� */
ID3V2_PARSE _xdata s_id3v2;					///<id3v2��Ϣ�ṹ
u8 _xdata id3_tag_buf[ID3_DISP_BUF_LEN];	///<ID3 tag buff
u8 id3_tag_len;								///<ID3 tag����

u8 _xdata id3_cache_buf[3][256] _at_ 0x4000;


#define MAX_ID3   3 ///<��ȡ��ID3V2��Ŀ����

u8 _bdata id3_get;      ///<��ȡ��ID3V2�ı�Ǳ�������ǻ�ȡ������Щ��Ϣ

sbit id3_title = id3_get ^0;
sbit id3_tpe = id3_get ^1;
sbit id3_tal = id3_get ^2;

_code char ID3_title_v2_34[] = "TPE1TALBTIT2";// ID3V2.3/4��Ҫ���ҵ�FrameID Table
_code char ID3_title_v2_2[] = "TP1TALTT2"; // ID3V2.2��Ҫ���ҵ�FrameID Table


/*----------------------------------------------------------------------------*/
/**@brief   �ڴ����ݱȽϺ���
   @param   * s1:���ݵ�ַ��* s2:���ݵ�ַ��len������
   @return  ��ȱ�־λ
   @note    u8 my_memcmp(u8 _xdata *s1, u8 _code *s2, u8 len)
*/
/*----------------------------------------------------------------------------*/
u8 my_memcmp(u8 _xdata *s1, u8 _code *s2, u8 len)
{
    u8 i;
    for (i = 0; i < len; i++)
    {
        if ((*(s1 + i )) != (*(s2 + i)))
            return 1;
    }

    return 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   ASCII���ʽ������
   @param   * buf:���������ݵ�ַ��* s2:���ݵ�ַ��len������
   @return  ת������
   @note    u8 ascii_format(u8 _xdata *buf, u8 format, u8 len)
*/
/*----------------------------------------------------------------------------*/
u8 ascii_format(u8 _xdata *buf, u8 format, u8 len)
{
    u8 i, j;
    u8 _xdata *ptr;

    ptr = buf;

    switch (format)
    { /* encoding type */

    case 0:  /* ISO-8859-1 (0 - 255 maps directly into unicode) */
    case 3:  /* UTF-8 */
        for (i = 0; i < len; i++)
        {
            if (*buf =='\0')
            {
                len = i;
                break;
            }
            if ((*buf < 0x20) || (*buf > 0x7f))
            {
                *ptr++ = '-';
                buf++;
            }
            else
                *ptr++ = *buf;

            buf++;
        }
        break;

    case 1:  /* UTF-16 with BOM */
        buf += 2;
        len -= 2;
    case 2:  /* UTF-16BE without BOM */
    default:
        for (i = 0; i < len; i += 2)
        {
            if ((buf[i] == 0) && (buf[i + 1] == 0))
            {
                break;
            }

            j = buf[i + 1];

            if (j != 0)
            {
                j = '-';
            }
            else
                j = buf[i];

            if ((j < 0x20) || (j > 0x7f))
            {
                j = '-';
            }

            *ptr++ = j;
        }

        len = i/2;
        break;
    }

    return len;
}
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡMP3��ǩ
   @param   ��
   @return  ��
   @note    void get_mp3_tag(void)
*/
/*----------------------------------------------------------------------------*/
void get_mp3_tag(void)
{
    u8 i,j,k;
    u8 _code * id3_table;

    id3_get = 0;

    f_seek(SEEK_SET, dec_msg->tag_len, dec_msg->tag_len >> 16);
    my_memset((u8 _xdata *)&s_id3v2, 0, sizeof(ID3V2_PARSE));

    while (ff_id3v2_check(decode_buffer, &s_id3v2)) //����ȡID3ͷ��ͷ��Ϣ
    {
        ff_cal_id3v2_tag_len(decode_buffer);
        while (ff_id3v2_parse(decode_buffer, &s_id3v2))
        {
            if (s_id3v2.id3v2_version == 2)
            {
                id3_table = ID3_title_v2_2;
                j = 3;
            }
            else
            {
                id3_table = ID3_title_v2_34;
                j = 4;
            }
            k = 0;
            for (i = 0; i < 3; i++)
            {
                if (!my_memcmp(decode_buffer, id3_table + i*j, j))
                {
                    if (s_id3v2.tlen > 128)
                        k = 128;
                    else
                        k = s_id3v2.tlen;

                    my_memset((u8 _xdata *)decode_buffer, 0, k + 2);
                    f_read(0, decode_buffer, k);
                    j = ascii_format(decode_buffer + 1, decode_buffer[0], k - 1);			//��һ���ֽ�Ϊ�ַ��ı��룬ʵ�ʵ����ݴӵڶ����ַ���ʼ�����ݵĳ���Ҫ��ȥ�����ַ�
                    id3_cache_buf[i][0] = j;
                    my_memcpy(id3_cache_buf[i] + 1, decode_buffer + 1, j);
                    break;
                }
            }

            f_seek(SEEK_CUR, s_id3v2.tlen - k,(s_id3v2.tlen - k) >> 16);
        }
    }
    fat_ptr1.flag = 0;
    //��ʾ˳��:TPE1-TALB-TIT2
    for (i = 0; i < 3; i++)
    {
        k = id3_cache_buf[i][0];
        j = ID3_DISP_BUF_LEN - id3_tag_len;
        k = k >= j?j:k;
        if (k > 0)
        {
            my_memcpy(id3_tag_buf + id3_tag_len, id3_cache_buf[i] + 1, k);

            id3_tag_buf[id3_tag_len + k] = ' ';
            id3_tag_len = id3_tag_len+k+1;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ȡWMA��ǩ
   @param   ��
   @return  ��
   @note    void get_wma_tag(void)
*/
/*----------------------------------------------------------------------------*/
void get_wma_tag(void)
{

}
/*----------------------------------------------------------------------------*/
/**@brief   ��ȡ��Ƶ��ǩ
   @param   ��
   @return  ��
   @note    void get_music_tag(void)
*/
/*----------------------------------------------------------------------------*/
void get_music_tag(void)
{
    my_memset((u8 _xdata *)id3_cache_buf, 0, 256*3);
    my_memset((u8 _xdata *)id3_tag_buf, 0, ID3_DISP_BUF_LEN);
    id3_tag_len = 0;

    if (music_type == IS_MP3)
    {
        get_mp3_tag();
    }
    else if (music_type == IS_WMA)
    {
        get_wma_tag();
    }

    if (id3_cache_buf[2][0] == 0)
    {
        my_memset((u8 _xdata *)decode_buffer, 0, 522);



        if (fs_getfile_longname(decode_buffer))									//��ȡ���ļ���
        {
            ascii_format(decode_buffer, 2, decode_buffer[521]*2);
            my_memcpy(id3_tag_buf + id3_tag_len,  decode_buffer, decode_buffer[521]);
            id3_tag_len += decode_buffer[521];
        }
        else
        {
            my_memcpy(id3_tag_buf + id3_tag_len, (u8 _xdata *)fs_msg.fname,    12);
            id3_tag_len += 12;
        }
    }
}