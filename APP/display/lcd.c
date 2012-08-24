/*--------------------------------------------------------------------------*/
/**@file     lcd.c
   @brief    ����LCD���ײ�����
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "disp.h"


#if (DISP_DOT_LCD == 1)
#include "lcd.h"
#include "uart.h"
#include "my_printf.h"
#include "resource.c"

extern u8 _xdata id3_tag_buf[128];
extern u8 id3_tag_len;
extern u8 _pdata music_spec[9];


_xdata u8 LCDBuff[8][132]; ///<�Դ�
u8 _idata monitor_cmd;
bool set_page, set_clumn;
u8 _idata font_size;
u8 _idata currPage;                	///<��ǰPAGE
u8 _idata updata_page_len;         	///<���µ�PAGE��Ŀ
coordinate LCDsite;         		///<��ʾ����
//coordinate flash_start, flash_end;
volatile bool spi_busy;     		///<SPIӲ��æ���
u16 _idata roll_counter;
u16 _idata roll_disp_len;
coordinate _idata roll_start, roll_end;
u8 LCDPAGE;	  ///<LCD��������ʾ�ߴ����
u8 LCDCOLUMN; ///<LCD��������ʾ�ߴ����

u8 _code lcd_init_table[] =
{
    LCD_SOFT_RST,
    LCD_BIAS_SET | 0x00,   //lcd bias setting
    LCD_ADC_SEL,           //0XA0 ADC
    LCD_COMMON_MODE,       //0xc8 common output mode
    (LCD_V0_RATIO | 0x03),   //Resistor Ratio
    LCD_POWER_MODE,        //0x2f lcd power control
    LCD_START_LINE | 0x0,    //0x40
    LCD_ON,
    LCD_ELE_VOLUME,        //0X81 /electronic Volume
    //LCD_ALL_ON
};   ///<lcd ��ʼ�������


u8 _code lcd_bmp_size_table[][2] =
{
    {2, 15},
    {0, 0},
    {2, 15},
    {0, 0},
    {0, 0},
    {4, 31},
    {2, 22},
    {2, 23},
    {2, 22},
    {2, 11},
    {2, 11},
    {2, 11},
    {2, 11},
    {2, 17},
    {2, 17},
    {2, 17},
    {2, 17},
    {2, 17},
};

u16 _code lcd_bmp_add_table[] =
{
    gImage_sd,
    0,
    gImage_udisk,
    0,
    0,
    gImage_vol,
    gImage_mp3,
    gImage_wma,
    gImage_wav,
    gImage_play_all,
    gImage_play_folder,
    gImage_play_one,
    gImage_play_random,
    gImage_eqnor,
    gImage_eqpop,
    gImage_eqrck,
    gImage_eqjaz,
    gImage_eqcls
};


/*----------------------------------------------------------------------------*/
/**@brief    ��ȫ����ֻ��BUFF��������
   @param
   @return
   @note     void DispClear(void)
*/
/*----------------------------------------------------------------------------*/
void clear_lcd(void)
{
    while (spi_busy);
    my_memset(&LCDBuff[0][0], 0x0, 8*132);
    LCD_Buff_position(LCD_START_LUMN, 0);

}
/*----------------------------------------------------------------------------*/
/**@brief    ������ָ������ֻ��BUFF��������
   @param    p1:��ʼ page
   @param    p2:����page
   @return
   @note     void LCDClearArea(u8 p1,u8 p2)
*/
/*----------------------------------------------------------------------------*/
void clear_lcd_area(u8 p1,u8 p2)
{
    while (spi_busy);
    for (;p1 <= p2;p1++)
    {
        my_memset(&LCDBuff[p1][0], 0, 132);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    ��LCD������һ������
   @param    cmd: ����
   @return
   @note     void LCDSendCmd(u8 cmd)
*/
/*----------------------------------------------------------------------------*/
void LCDSendCmd(u8 cmd)
{
    LCD_A0_L;    //LCD_COMMAND
    _nop_();
    _nop_();
    _nop_();
    LCD_CS_L;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    SPIBUF = cmd;
    while (!(SPICON & 0x80)); //�ȴ��������
    SPICON &= ~0x80;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    LCD_CS_H;
}

/*----------------------------------------------------------------------------*/
/**@brief    ������ʾ����ʼ����
   @param     x:������
   @param     y:������
   @return
   @note      void LCD_SET(u8 y,u8 x)
*/
/*----------------------------------------------------------------------------*/
void LCD_SET(u8 y,u8 x)
{
    LCDSendCmd(LCD_COLUMN_HIGH | x>>4);
    LCDSendCmd(LCD_COLUMN_LOW | (0x0f & x));
    LCDSendCmd(LCD_PAGE_ADDR | y);
}

/*----------------------------------------------------------------------------*/
/**@brief  ���õ�ǰ��ʾ������
   @param  x : ������; y : ������;
   @return ��
   @note   LCD_Buff_position
*/
/*----------------------------------------------------------------------------*/
void LCD_Buff_position(u8 x,u8 y)  //������Ļ����  x:0~127 column address    y:0~3 page address
{
    LCDsite.x = x;
    LCDsite.y = y;
}

void LCD_Buff_setx(u8 x)
{
    LCDsite.x = x;
}

void LCD_Buff_sety(u8 y)
{
    LCDsite.y = y;
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ʾ��ʼ������
   @param
   @return
   @note    void DispInit(void)
*/
/*----------------------------------------------------------------------------*/
void init_dot_lcd_disp(void)
{
    u8 i;

    LCDPORT_OUT();
    LCDPORT_H();
    LCD_RES_L;
    delay(1000);
    LCD_RES_H;
    SPIBAUD = 10;
    SPICON = 0x0B;						//select Port1
    spi_busy = 0;

    for (i = 0; i < sizeof(lcd_init_table); i++)
    {
        LCDSendCmd(lcd_init_table[i]);
        delay(1000);
    }

#if (monitor == DISP_LCD_12832)
    LCDPAGE = 4;
    LCDCOLUMN = 128;
    LCDSendCmd(LCD_CONTRAST_12832);
#elif ((monitor == DISP_LCD_12864_PAR) || (monitor == DISP_LCD_12864_SER))
    LCDPAGE = 8;
    LCDCOLUMN = 128;
    LCDSendCmd(LCD_CONTRAST_12864);
#endif
    //LCDSendCmd(LCD_ALL_ON);
}

/*----------------------------------------------------------------------------*/
/**@brief   �����е���ģ���뵽ָ����������
   @param   y:�����ꣻx�����ꣻdat:��λ����ģ
   @return  ��
   @note    void to_lcdbuff(u8 y,u8 x, u8 dat)
*/
/*----------------------------------------------------------------------------*/
void to_lcdbuff(u8 y,u8 x, u8 dat)
{
    if ( (x >= LCD_END_LUMN ) || (y >= LCDPAGE ) )
    {
        return;
    }
    LCDBuff[y][x] = dat;
}

/*----------------------------------------------------------------------------*/
/**@brief   �ڵ�ǰ������Ļ�������ƫ��
   @param   X����ƫ��;Y����ƫ��;
   @return  ��
   @note    void set_lcd_position(u8 y,u8 x)
*/
/*----------------------------------------------------------------------------*/
void set_lcd_position(u8 y,u8 x)
{
    LCDsite.x += x;
    LCDsite.y += y;
}

/*----------------------------------------------------------------------------*/
/**@brief   ��ģ�Ŵ󵽃ɱ�����
   @param   ��λ�Ć�����ģ
   @return  �Ŵ�16λ������ģ
   @note    u16 display_sizex2(u8 chardata)
*/
/*----------------------------------------------------------------------------*/
u16 display_sizex2(u8 chardata)
{
    u16 result = 0;
    u8 i;

    for (i = 0; i < 8; i++)
    {
        result <<= 1;
        if (chardata & 0x80)
            result++;
        result <<= 1;
        if (chardata & 0x80)
            result++;
        chardata <<= 1;
    }
    return result;
}

/*----------------------------------------------------------------------------*/
/**@brief   ��һ��ָ����С��ͼƬ�����ִ���
   @param   y:�гߴ磻x���гߴ磻*bmpһ��ָ��ͼƬģ�͵�ָ�루ͼƬ����CODE����
   @return  ��
   @note    void lcd_disp_bmp(u8 y,u8 x,u8 _code *bmp)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_bmp(u8 y,u8 x,u8 _code *bmp)
{
    u8 i,j;

    for (i = 0;i < x;i++)
    {
        for (j = 0;j < y;j++)
        {
            if (font_size == 3)
                to_lcdbuff(LCDsite.y+j,LCDsite.x,*(bmp+j*x+i) | 0x01);
            else
                to_lcdbuff(LCDsite.y+j,LCDsite.x,*(bmp+j*x+i));
        }
        LCDsite.x++;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   LCD��ʾ����id����ʾͼƬ
   @param   id:ͼƬ��
   @return  ��
   @note    void lcd_disp_bmp_via_id(u8 id)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_bmp_via_id(u8 id)
{
    lcd_disp_bmp(lcd_bmp_size_table[id][0], lcd_bmp_size_table[id][1], (u8 _code *)lcd_bmp_add_table[id]);
}
/*----------------------------------------------------------------------------*/
/**@brief   LCD��ʾ����
   @param   mode:���roll_counter��־
   @return  ��
   @note    void lcd_roll_disp(u8 mode)
*/
/*----------------------------------------------------------------------------
void lcd_roll_disp(u8 mode)
{
    //if (roll_en)
    bool id3_flag=0;
    {
        if (mode == 0)							//reset
            roll_counter = 0;

        if (id3_tag_len < ((LCD_END_LUMN - LCD_START_LUMN)/ 8))
        {
            id3_flag=1;
            roll_counter = 0;
        }


        if ((roll_counter == 0)&&(id3_flag==1))	  //�ļ�����С��16
        {
            LCD_Buff_position(LCD_START_LUMN+2,2);
            printf_str(id3_tag_buf);
        }
        else if ((roll_counter == 0)&&(id3_flag==0)) //reset
        {
            LCD_Buff_position(LCD_START_LUMN,2);
            printf_str(id3_tag_buf);
        }
        else
        {
            my_memcpy( &LCDBuff[2][LCD_START_LUMN],&LCDBuff[2][LCD_START_LUMN + 1] ,LCD_END_LUMN-1);
            my_memcpy( &LCDBuff[3][LCD_START_LUMN],&LCDBuff[3][LCD_START_LUMN + 1] ,LCD_END_LUMN-1);
            LCDBuff[2][LCD_END_LUMN - 1] = 0;
            LCDBuff[3][LCD_END_LUMN - 1] = 0;                                            
            LCD_Buff_position(LCD_END_LUMN - 8 - (u8)roll_counter % 8,2);
            printf_str(id3_tag_buf + (roll_counter / 8) + ((LCD_END_LUMN-8) >> 3));
        }

        roll_counter++;
        if (roll_counter >= (id3_tag_len*8))
        {
            roll_counter = 0;
        }

        draw_lcd(2,4);
    }              
}
*/

/*----------------------------------------------------------------------------*/
/**@brief   LCD��ʾƵ��
   @param   ��
   @return  ��
   @note    void lcd_disp_spec(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_disp_spec(void)
{
    u8 _code music_spec_table[] = {0x80, 0xc0, 0xe0, 0xf0, 0xf8,0xfc,0xfe,0xff};
    u8 i, j, k;
    u32 buf;

    clear_lcd_area(4, 7);

    for (i = 0; i < 9; i++)
    {
        buf = 0x0;
        k = music_spec[i];
        if (k > 31)
            k = 31;

        {
            if ((k / 8) == 0)
            {
                ((u8 *)(&buf))[3] = music_spec_table[k];
            }
            else if ((k / 8) == 1)
            {
                ((u8 *)(&buf))[3] = 0xff;
                ((u8 *)(&buf))[2] = music_spec_table[k%8];
            }
            else if ((k / 8) == 2)
            {
                ((u8 *)(&buf))[3] = 0xff;
                ((u8 *)(&buf))[2] = 0xff;
                ((u8 *)(&buf))[1] = music_spec_table[k%8];
            }
            else
            {
                ((u8 *)(&buf))[3] = 0xff;
                ((u8 *)(&buf))[2] = 0xff;
                ((u8 *)(&buf))[1] = 0xff;
                ((u8 *)(&buf))[0] = music_spec_table[k%8];
            }
        }

        for (j = 0; j < 4; j++)
        {
            LCDsite.x = LCD_START_LUMN + 4 + i * 14;
            LCDsite.y = 4 + j;
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
            LCDBuff[LCDsite.y][LCDsite.x++] = ((u8 *)(&buf))[j];
        }
    }

    draw_lcd(4,8);
}
/*----------------------------------------------------------------------------*/
/**@brief   LCD��ʾ�����
   @param   ��
   @return  ��
   @note    void lcd_cmd(u8 key)
*/
/*----------------------------------------------------------------------------*/
void lcd_cmd(u8 key)
{
    if (key == 'c')
    {
        clear_lcd();
    }
    else if (key == 'e')
    {
        font_size = 1;
    }
    else if (key == 'o')
    {
        font_size = 0;
    }
    else if (key == 'a')
    {
        font_size = 2;
    }
    else if (key == 'k')
    {
        font_size = 3;
    }
    else if (key == 'p')
    {
        lcd_disp_spec();
    }
    else if (key == 'w')
    {
#if ((monitor == DISP_LCD_12832)  || (monitor == DISP_LCD_12864_SER)  || (monitor == DISP_LCD_12864_PAR))
        while (spi_busy);
#endif
    }
}

/*----------------------------------------------------------------------------*/
/**@brief   LCD��ʾ�ַ�
   @param   chardata���ַ�����
   @return  ��
   @note    void lcd_putchar (u8 chardata)
*/
/*----------------------------------------------------------------------------*/
void lcd_putchar (u8 chardata)
{
    u8 i;
    u16 temp;

    if (chardata == '\n')							//����
    {
        LCDsite.y++;
        if (LCDsite.y >= LCDPAGE)
            LCDsite.y = 0;
        LCDsite.x = LCD_START_LUMN;
    }
    else if ((font_size == 2) || (font_size == 3))
    {
        if (chardata == ':')
        {
            lcd_disp_bmp(1,3,gImage_small_dot);
        }
        else
        {
            lcd_disp_bmp(1,6,gImage_number + ((chardata - '0') * 6));
        }
    }
    else if (font_size == 1)
    {
        for (i = 0;i<8;i++)
        {
            if (LCDsite.x >= (LCDCOLUMN - 2))
            {
                return ;
            }
            temp = display_sizex2(CharsTable[16*(chardata - ' ')+i]);//fontBuff[i]);
            to_lcdbuff(LCDsite.y,LCDsite.x,temp);
            to_lcdbuff(LCDsite.y,LCDsite.x+1,temp);
            to_lcdbuff(LCDsite.y+1,LCDsite.x,temp>>8);
            to_lcdbuff(LCDsite.y+1,LCDsite.x+1,temp>>8);

            temp = display_sizex2(CharsTable[16*(chardata - ' ')+i+8]);//fontBuff[i+8]);
            to_lcdbuff(LCDsite.y+2,LCDsite.x,temp);
            to_lcdbuff(LCDsite.y+2,LCDsite.x+1,temp);
            to_lcdbuff(LCDsite.y+2+1,LCDsite.x,temp>>8);
            to_lcdbuff(LCDsite.y+2+1,LCDsite.x+1,temp>>8);
            LCDsite.x += 2;
        }
    }
    else
    {
        for (i = 0 ;i<8;i++)
        {
            if (LCDsite.x >= LCD_END_LUMN)
            {
                return ;
            }
            to_lcdbuff(LCDsite.y,LCDsite.x,CharsTable[16*(chardata - ' ')+i]);//fontBuff[i]);
            to_lcdbuff(LCDsite.y+1,LCDsite.x,CharsTable[16*(chardata - ' ')+i+8]);//fontBuff[i+8]);
            LCDsite.x++;
        }
    }

}


/*----------------------------------------------------------------------------*/
/**@brief   �����Դ�����ݵ�LCD
   @param   start_page �����¿�ʼ����ʼPage
   @param   page_len �����µ�Page��
   @return
   @note    void updataLCD(u8 start_page, u8 page_len)
*/
/*----------------------------------------------------------------------------*/
void draw_lcd(u8 start_page, u8 page_len)
{
    while (spi_busy);
    currPage = start_page;
    updata_page_len = page_len;
    interrupt_init(11, lcd_dma_isr);
    SPIDMAISREN();
}
/*----------------------------------------------------------------------------*/
/**@brief   LCD DMA�ж�
   @param   ��
   @return	��
   @note    void lcd_dma_isr(void)
*/
/*----------------------------------------------------------------------------*/
void lcd_dma_isr(void)
{
    PSW = 0x08;
    DPCON = 0x0;

    LCD_CS_H;
    _nop_();
    _nop_();
    _nop_();
    if (updata_page_len == 0)
    {
        spi_busy = 0;
        SPIDMAISRDIS();
        return;
    }

    spi_busy = 1;
    LCD_SET(currPage, 0);
    _nop_();
    _nop_();
    _nop_();
    LCD_A0_H;
    _nop_();
    _nop_();
    _nop_();
    LCD_CS_L;
    _nop_();
    _nop_();
    _nop_();
    SPICON &= ~BIT(7);
    SPIDMAADR = ((u16)(&LCDBuff[currPage][0])) >> 8;
    SPIDMAADR = ((u16)(&LCDBuff[currPage][0]));

    SPIDMACNT = 132 / 2;

    currPage++;
    updata_page_len--;
}
#else
void lcd_dma_isr(void)
{
}
#endif

