/*--------------------------------------------------------------------------*/
/**@file   led.h
   @brief  LED驱动头文件
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#ifndef _LED_H_
#define	_LED_H_


#ifdef __C51__
#if defined(LED_GPIO_PORT_CUSTOMERIZED)||defined(COMMON_CATHODE)
#define led_com_out() P3DIR &= ~0x1F; P3PU|= 0x1f; P3PD |= 0x1f;
#define led_seg_out() P1DIR &= ~0xFF;P1PU|= 0xFf; 
#else
#define led_com_out() P3DIR &= ~0x1F; P3HD = 0x1f,P3PD |= 0x1f; PWM4CON = 0xdf
#define led_seg_out() P1DIR &= ~0x7F
#endif
#define LED_A   0
#define LED_B	1
#define LED_C	2
#define LED_D	3
#define LED_E	4
#define LED_F	5
#define LED_G	6
#define LED_H	7

//for LED0
#if defined(K015_SW005_REC_V001)
#define LED0_AUX	  BIT(LED_A)
#define LED0_FM	      	  BIT(LED_B)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#elif defined(LED_USE_NORMAL_4X8)
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      	  BIT(LED_H)//0//BIT(LED_B)
#define LED0_USB	  0//BIT(LED_C)
#define LED0_SD		  0//BIT(LED_D)
#define LED0_2POINT	  BIT(LED_H)
#define LED0_WMA       0//BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_F)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#elif defined(K800_ZX_800_REC_V001)||defined(K646_ZX_308_REC_V001)
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      BIT(LED_G)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  BIT(LED_F)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#elif defined(K000_CHENGQIANG_REC_V003)||defined(K2069_SES_2069_REC_V001)||defined(K0000_BHT_C202_REC_V001)
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      BIT(LED_F)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  //T(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	  BIT(LED_G)//BIT(LED_G)
#elif defined(K000_XL_X15_REC_V001)||defined(K1153_AJR_LSK8_REC_V001)
#define LED0_AUX	  BIT(LED_A)
#define LED0_FM	      	  BIT(LED_C)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_E)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_G)
#define LED0_WMA      0//BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#define LED0_BAT_H	  BIT(LED_F)
#define LED0_BAT_L     BIT(LED_B)
#elif defined(K4006_SES_1234_REC_V001)
#define LED0_AUX	  BIT(LED_D)
#define LED0_FM	      	  BIT(LED_F)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_A)
#define LED0_SD		  BIT(LED_B)
#define LED0_2POINT	  BIT(LED_G)
#define LED0_WMA       0//BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#define LED0_BAT_H	  BIT(LED_E)
#define LED0_BAT_L     BIT(LED_C)
#elif defined(K1081_WK_1081_REC_V001)
#define LED0_AUX	  BIT(LED_D)
#define LED0_FM	      	  BIT(LED_B)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_A)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA       0//BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#define LED0_BAT_H	  BIT(LED_F)
#define LED0_BAT_L     BIT(LED_G)

#elif defined(K2035_SES_2035_REC_V001)||defined(K2035_SES_2035_REC_V002)
#define LED0_AUX	  0// BIT(LED_A)
#define LED0_FM	      	  BIT(LED_B)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_A)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA       BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_G)
#define LED0_REC	  BIT(LED_D)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  0//BIT(LED_A)
#define LED0_PAUSE	  0//BIT(LED_B)

#define LED0_BAT_H	  BIT(LED_F)
#define LED0_BAT_L     BIT(LED_G)
#elif defined(K0000_XFW_GL005_REC_V001)
#define LED0_AUX	  BIT(LED_F)
#define LED0_FM	      BIT(LED_G)//0//BIT(LED_B)
#define LED0_USB	  	BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      	0//BIT(LED_F)
#define LED0_MP3	  	0//BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#elif defined(K1189_AJR_LSK8_REC_V001)
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      BIT(LED_G)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  0//BIT(LED_F)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	 BIT(LED_F)
#elif defined(NOR_LED_EXCHANGE_FM_MP3_ICON)
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      BIT(LED_G)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  BIT(LED_F)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)
#else
#define LED0_AUX	  0//BIT(LED_A)
#define LED0_FM	      BIT(LED_F)//0//BIT(LED_B)
#define LED0_USB	  BIT(LED_C)
#define LED0_SD		  BIT(LED_D)
#define LED0_2POINT	  BIT(LED_E)
#define LED0_WMA      BIT(LED_F)
#define LED0_MP3	  BIT(LED_G)
#define LED0_WAV	  0
#define LED0_1POINT   0
#define LED0_PLAY	  BIT(LED_A)
#define LED0_PAUSE	  BIT(LED_B)
#define LED0_REC	  0//BIT(LED_G)

#ifdef USE_BAT_MANAGEMENT

#ifndef LED0_BAT_H
#define LED0_BAT_H	  BIT(LED_F)
#endif

#ifndef LED0_BAT_L
#define LED0_BAT_L	  BIT(LED_G)
#endif
#endif


#if 0

#define LED0_PLAY	 	BIT(LED_A)
#define LED0_PAUSE	 	BIT(LED_B)
#define LED0_USB		BIT(LED_C)
#define LED0_SD			BIT(LED_D)
#define LED0_2POINT		BIT(LED_E)	  
#define LED0_MP3		BIT(LED_F)
#define LED0_MHZ	    BIT(LED_G)
#define LED0_FM			BIT(LED_G)	
#endif
#endif
#ifdef USE_BAT_MANAGEMENT

#ifndef LED0_BAT_H
#define LED0_BAT_H	  BIT(LED_F)
#endif

#ifndef LED0_BAT_L
#define LED0_BAT_L	  BIT(LED_G)
#endif
#endif

enum									//LED 数码管显示ICON定义
{
    LED_MASK_FM_ICON = 0,
    LED_MASK_UDISK_ICON,
    LED_MASK_SD_ICON,
    LED_MASK_MP3_ICON,
    LED_MASK_2DOT_ICON,
    LED_MASK_PLAY_ICON,
    LED_MASK_PAUSE_ICON,	   	//0x0C
			

    LED_MASK_CHAR0 = 0x40,				//LED字符显示定义
    LED_MASK_CHAR1,
    LED_MASK_CHAR2,
    LED_MASK_CHAR3,
    LED_MASK_CHAR4,
    LED_MASK_CHAR5,
    LED_MASK_CHAR6,
    LED_MASK_CHAR7,						//0x47

    LED_FM_ICON = 0x80,
    LED_UDISK_ICON,
    LED_SD_ICON,
    LED_MP3_ICON,
    LED_2DOT_ICON,
    LED_PLAY_ICON,
    LED_PAUSE_ICON,					//0x9C
	  				

    LED_CHAR0 = 0xC0,				//LED字符显示定义
    LED_CHAR1,
    LED_CHAR2,
    LED_CHAR3,
    LED_CHAR4,
    LED_CHAR5,
    LED_CHAR6,
    LED_CHAR7,						//0xC7


    LED_ALL_NO_FLASH = 0xfe,
    LED_ALL_FLASH = 0xFF,
};


void clear_led(void);
#if (NO_DISP != monitor)
    void disp_scan(void);
#endif
void led_putchar(u8 chardata,u8 loc);
void init_led_disp();

void led_flash_set(u8 chardata);
void led_cmd(u8 key);
void led_set_brightness(u8 br);
void led_disp_icon(u8 id);
void clr_led_flash_icon(u8 id);
void clr_led_disp_icon(u8 id);
void led_flash_icon(u8 flag);
void led_flash_section(u8 flag);


//#define led_disp_icon(n)    LED_BUFF[0] |= n
//#define led_flash_icon(n)    LED_FLASH[0] |= n

extern _idata u8 LED_BUFF[5];   ///<LED显存
extern _idata u8 LED_FLASH[5];



#endif


#define LED_COM1   P30
#define LED_COM2   P31
#define LED_COM3   P32
#define LED_COM4   P33
#define LED_COM5   P34

#define LED_COM    P3

#define LED_COM_MASK   P3PU
#define LED_COM_PD_MASK   P3PD

#define LED_SEG    P1




#endif
