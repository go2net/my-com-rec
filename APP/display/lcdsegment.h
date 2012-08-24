
#include "config.h"
#if(LCD_DISP == monitor)

#ifndef _LCDSEGMENT_H_
#define _LCDSEGMENT_H_

/*
COM1 P30
COM2 P31
COM3 P32
COM4 P33
SEG0~7   P10~P17
SEG8     P34
*/
#define 	DIG_A	0x01
#define 	DIG_B	0x02
#define 	DIG_C	0x04
#define 	DIG_D	0x08
#define 	DIG_E	0x10
#define 	DIG_F	0x20
#define 	DIG_G	0x40
#define 	DIG_H	0x80
#ifdef __C51__

#if 0
#define play_led_seg_out() P0DIR &= ~0x80;P0PU |= 0x80;
#endif


#if defined(K820_LHD_820_REC_V001)
#define   com_init()      P3PU |= (0x0F);P3PD |= (0x0F)
#define   close_com(n)    com_init();P3DIR |= (0x0F);P3DIR &= ~(1<<(n))
    
#define	set_com(n)      P3 |= (1<<(n))
#define   clr_com(n)       P3 &= ~(1<<(n)) 
	
#define   seg_init()      P1DIR =0;P3DIR &= ~(1<<4)//;P3PU &= ~(1<<4);P3PD &= ~(1<<4)
#define   seg07_port(n)   	P1 = n
#define   seg8_port(n)	P34 = n
#define   bklt_init()	  P3DIR &= ~(1<<0);P3 |= (1<<0);
#else

#define   com_init()      P3PU |= (0x1F);P3PD |= (0x1F)
#define   close_com(n)    com_init();P3DIR |= (0x1F);P3DIR &= ~(1<<(n))
    
#define	set_com(n)      P3 |= (1<<(n))
#define   clr_com(n)       P3 &= ~(1<<(n)) 
	
#define   seg_init()      P1DIR = 0;P3DIR &= ~(1<<4)//;P3PU &= ~(1<<4);P3PD &= ~(1<<4)
#define   seg07_port(n)   	P1 = n
#define   seg8_port(n)	P34 = n
#define   bklt_init()	  P3DIR &= ~(1<<0);P3 |= (1<<0);
#endif

#endif

enum {

	USB_ICON,
	SD_ICON,
	AUX_ICON,
	FM_ICON,
	REP_1_ICON,
	REP_ALL_ICON,
	COL_ICON,
	PLAY_ICON,
	MP3_ICON,
	F1BC_ICON,
	NONE_ICON,
};

#if defined(K820_LHD_820_REC_V001)

#define USB_DEV_MASK	0x0100
#define F_USB_DEV  		(lcd_buff[0])	

#define AUX_DEV_MASK	0x0001
#define F_AUX_DEV  		(lcd_buff[3])

#define SD_DEV_MASK	0x0001
#define F_SD_DEV		(lcd_buff[1])	

#define FM_DEV_MASK	0x0100
#define F_FM_DEV		(lcd_buff[1])	

#define POINTS_MASK		0x0004
#define F_POINTS		(lcd_buff[3])	

#define FM_MHZ_MASK	0x0100
#define F_MHZ_DEV		(lcd_buff[1])	

#define AM_KHZ_MASK	0x0000
#define F_KHZ_DEV		(lcd_buff[0])	

#define FM_P1_MASK		0x0000
#define F_P1_DEV		(lcd_buff[3])	


#define RTC_ICON_MASK	0x0000
#define F_RTC_ICON		(lcd_buff[3])

#define RTC_ALM_MASK	0x0000
#define F_RTC_ALM		(lcd_buff[3])	

#define RTC_PM_MASK	0x0000
#define F_RTC_PM		(lcd_buff[2])

#define RTC_AM_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])


#define SPK_MUTE_MASK	0x0000
#define SPK_ICON		(lcd_buff[0])	

#define BATTERY_MASK	0x0000
#define BAT_ICON		(lcd_buff[0])	

#define TRADEMARK_MASK	0x0000
#define TRADEMARK_ICON		(lcd_buff[0])	

#define NUM_1BC_MASK	0x0000
#define F_NUM_1BC		(lcd_buff[2])	

#define REP_ALL_MASK	0x0040
#define REP_ONE_MASK	0x0001
#define F_REP_ALL		(lcd_buff[3])
#define F_REP_ONE 		(lcd_buff[0])

//#define L_ICON_BUF		(lcd_buff[4])
#define L1_ICON_MASK	0x0000
#define L1_ICON_BUF		(lcd_buff[0])
#define L2_ICON_MASK	0x0000
#define L2_ICON_BUF		(lcd_buff[1])
#define L3_ICON_MASK	0x0000
#define L3_ICON_BUF		(lcd_buff[2])
#define L4_ICON_MASK	0x0000
#define L4_ICON_BUF		(lcd_buff[3])

#else

#define USB_DEV_MASK	0x0000
#define REP_ONE_MASK	0x0000
#define F_USB_DEV  		lcd_buff[0]	
#define F_REP_ONE 		lcd_buff[0]

#define FM_DEV_MASK	0x0051
#define SD_DEV_MASK	0x0000
#define F_FM_DEV		(lcd_buff[3])	
#define F_SD_DEV		(lcd_buff[1])	

#define RTC_PM_MASK	0x0000
#define NUM_1BC_MASK	0x0001
#define F_RTC_PM		(lcd_buff[2])
#define F_NUM_1BC		(lcd_buff[1])	

#define RTC_AM_MASK	0x0000
#define AUX_DEV_MASK	0x0000
#define POINTS_MASK		0x0004
#define RTC_ALM_MASK	0x0000
#define REP_ALL_MASK	0x0000
#define F_RTC_AM		(lcd_buff[3])
#define F_AUX_DEV		(lcd_buff[3])	
#define F_POINTS		(lcd_buff[3])	
#define F_RTC_ALM		(lcd_buff[3])	
#define F_REP_ALL		(lcd_buff[3])	



#define F_BAT_1			(lcd_buff[0])	
#define F_BAT_2			(lcd_buff[1])	
#define F_BAT_3			(lcd_buff[2])	
#define F_BAT_4			(lcd_buff[3])	
#endif

void init_seg_lcd_disp(void);
void seg_lcd_disp_scan(void);
void seg_lcd_disp_icon(u8 id);
void seg_lcd_flash_icon(u8 id);
void seg_lcd_set_brightness(u8 br);
void led_putchar(u8 chardata,u8 loc);

#endif

#endif
