/*--------------------------------------------------------------------------*/
/**@file   music.h
   @brief  musicͷ�ļ�
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "config.h"
#include "tff.h"
#include "iic.h"
#include "disp.h"
#include "key.h"

#ifdef __C51__

enum
{
    REPEAT_ALL = 0,
    REPEAT_FOLDER,
    REPEAT_ONE,
    REPEAT_RANDOM,
    REPEAT_BACK,
    
};


enum
{
    UNKNOW_FORMAT = 0,
    IS_WAV,
    IS_WMA,
    IS_MP3,
    NOT_SUPPORT,
};

enum 							//config command
{
    MAD_STOP = 0,				//���Ž�ֹͣ������ģ���Ѿ����ر�
    MAD_PLAY,					//���ڲ�����
    MAD_PAUSE,					//������ͣ
    MAD_FAST_FORWARD,
    MAD_FAST_REVERASE,
    MAD_INIT,					//���ų�ʼ��
    MAD_FF,
    MAD_FR,
    MAD_STOP_WAIT,				//��ǰ�������Ž���������Ҫ��ʱһ��ʱ�����ֹͣ
    MAD_PLAY_END,				//��ǰ�������Ž�������ǰ����������δֹͣ����ģ��
};

enum							//�����ļ��ķ�ʽ����
{
    PLAY_NEXT_FILE = 0,
    PLAY_AUTO_NEXT,
    PLAY_FIRST_FILE,  		    //�ӵ�һ���ļ�����
    PLAY_BREAK_POINT,           //�Ӽ����ļ���λ�ÿ�ʼ����
    PLAY_LAST_FILE,				//�����һ���ļ�����
    PLAY_PREV_FILE,
    PLAY_SEL_FILE,
};


typedef struct _ID3V2_PARSE
{
    u8 isv34;
    u8 unsync;
    u8 tunsync;
    u8 id3v2_version;
    u8 id2v3_flags;
    u8 taghdrlen;
    u32 id3v2_len;				// ID3 �ܳ���, ������֡ͷ��Footer preset
    u32 tlen;					// ��ǰID3 frame���ȣ�������֡ͷ
} ID3V2_PARSE;

typedef struct _DECODER_MSG
{
    u16 (_code *read_file) (u8 _xdata *buffer, u16 len);
    u8 (_code *seek_file) (u8, u16, u16);
    u8 (_code *file_status) (void);
    u32 (_code *f_tell_fptr)(void);
    u32 (_code *f_tell_fsize)(void);
    void (_code *f_backup)(u8 file_index, FIL_BACKUP _xdata *buf);
    void (_code *f_restore)(u8 file_index, FIL_BACKUP _xdata *buf);
    u8 * eq_table;
    u8 _xdata *buffer;      //������ʹ�õ�buffer
    u16  buffer_len;
    u8  format;             //��Ƶ��ʽ��1��2��3��MP3�� 8~15��WAV��16~23��WMA
    u32 id1;
    u16 total_time;         //������ʱ��
    u16 play_time;          //��ǰ����ʱ�䣬��λΪ��
    u32 bit_rate;           //��ǰ֡�ı�����, MP3��ʽʱ�����2000��ϵ��
    u16 sample_rate;        //��ǰ֡�Ĳ�����
    u32 tag_len;
    u32 id2;
    u8  err;
    u8  err_counter;
}DECODER_MSG;

typedef struct _DISK_MUSIC_POINT
{
    u16     id0;		// �ļ�����,�����ļ�ʱ,���������������ܵ��ļ���
    u32	    id1;			// ��ǰ�ļ����
    u32	    id2;			// �ļ�����
} DISK_MUSIC_POINT;

DECODER_MSG _xdata * get_dec_msg_ptr(void);
u32 ff_id3v2_frame_len(const u8 _xdata *buf);
bool ff_id3v1_match(u8 _xdata *buf);
bool ff_id3v2_parse(u8 _xdata *buf, ID3V2_PARSE _xdata *id3);
void ff_id3v2_parse_header(u8 _xdata *buf, ID3V2_PARSE _xdata *id3);
bool ff_id3v2_check(u8 _xdata * buf, ID3V2_PARSE _xdata *id3);
void ff_cal_id3v2_tag_len(const u8 _xdata * buf);

///////
void music_decode(void);
void get_mp3_play_time(void);
void backup_music_point(void);
#endif

#define FR_LIMIT_SIZE    50L					//����֧�ֵ�����ļ���С,��MΪ��λ
#define FF_FR_STEP			2					//������˵Ĳ�����ÿ�����ڿ������˵�ʱ�䣬����Ϊ��λ



#endif