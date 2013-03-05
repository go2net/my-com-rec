/*--------------------------------------------------------------------------*/
/**@file   disp.h
   @brief    ��ʾģ��ͷ�ļ�
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef   _DISP_H_
#define  _DISP_H_

#include "config.h"
#include "my_printf.h"

#ifdef __C51__

enum
{
    MENU_NULL = 0,
    MENU_PLAY,
    MENU_PAUSE,
    MENU_MAIN_VOL,
    MENU_EQ,
    MENU_POWER_UP,
    MENU_PLAYMODE,
    MENU_NOFILE,
    MENU_NODEVICE,
    MENU_PLAY_TIME,
    MENU_FILENUM,
    MENU_INPUT_NUMBER,
    MENU_WAIT,
    MENU_USBDEV_MAIN,
    MENU_MUSIC_MAIN,
    MENU_FM_MAIN,
    MENU_FM_DISP_FRE,
    MENU_FM_FIND_STATION,
    MENU_FM_CHANNEL,
    MENU_USBREMOVE,
    MENU_SDREMOVE,
    MENU_SCAN_DISK,
    MENU_AUX,
    MENU_RTC,
    MENU_RTC_PWD,
    MENU_ALM_UP,
    MENU_ALM_SET,
    MENU_ALM_REQUEST,
	MENU_REC_MAIN ,
	MENU_REC_ERR,
    MENU_SET_EQ,
    MENU_SET_PLAY_MODE,
    MENU_RECWORKING,
    MENU_REC,
	MENU_REC_PAUSE,
	MENU_REC_DEL,
    MENU_REV_DEEP,
    MENU_REV_STRONG,
    MENU_200MS_REFRESH = 0x80,
    MENU_100MS_REFRESH,

    MENU_HALF_SEC_REFRESH,
    MENU_POWER_DOWN,
};

void disp_power_on(void);
void disp_fm_freq(void);
void disp_input_number(u16 num);
void disp_main_vol(u8 vol);



void disp_music_play_time(void);
void disp_music_format(void);
void disp_roll_ctrl(u8 mode);
void disp_main_menu_refresh(void);
void disp_eq(void);
void disp_play_mode(void);
void init_display(void);

void disp_bmp(u8 id);
void clear_display(void);
void disp_flash_icon(u8 id);
//void flashled(u8 fre);
//void disp_dled(void);
//void dled_ctl(u8 flag);

//#if (NO_DISP != monitor)

//#endif
enum{

	LED_OFF,
	LED_FAST,
	LED_SLOW,
	LED_ON,
};

void disp_rec_working(void);
#endif

#define SUB_MENU_TIME         (1*6)

#endif
