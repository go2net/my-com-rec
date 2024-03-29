/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    一些基本参数的配置
   @author
   @date   2010-12-13
   @note   AC309N
*/
/*----------------------------------------------------------------------------*/
#ifndef _CONFIG_
#define _CONFIG_

#include "AC309N.h"
#include "typedef.h"
#include "entry.h"
#include "clock.h"

#define JK_PX33_3094_REC_V001

#define DEL_REC_FILE_ONLY
#define REC_PLAY_BREAK_POINT
//#define NO_IR_REMOTE
#define NO_LED_DISPLAY
#define INDEPENDENT_FM_OSC
#define OSC_USE_12M
#define NOT_USE_LINE_IN_FUNC
#define QN_SCAN_ST_ENABLE


#define USB_DEVICE_ENABLE		0		///根据客户选用的bsp库，对应地选择是否打开
#define RTC_ENABLE              0       ///<RTC使能，如果不需要使用RTC功能，此处填0


//显示屏选择

#define DISP_LED5X7           1
#define DLED				  2
#define NO_DISP				  3

#define monitor           DISP_LED5X7//   NO_DISP//      

#ifdef __C51__
#include "intrins.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "encode.h"

typedef enum
{
    DIS_SD_CMD_CHK = 0,	///<在命令检测SD卡在线状态的情况下，暂停SD在线检测
    EN_SD_CMD_CHK,		///<在命令检测SD卡在线状态的情况下，恢复SD在线检测
    SET_SD_H_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测100MS一次
    SET_SD_L_CHK,		///<在命令检测SD卡在线状态的情况下，SD不在线时检测1S一次
}Sd_api_cmd;


//fm模块选择
#define RDA5807      0
#define CL6017G      0
#define BK1080       0
#define KT0830EG     0
#define QN8035       1


#if ((1 == RDA5807)||(1 == CL6017G)||(1 == BK1080)||(1 == KT0830EG)||(1 == QN8035))		///<是否有fm模块
#define FM_MODULE			1
#else
#define FM_MODULE			0
#endif
enum
{
    MUSIC_MODE = 0,
#if USB_DEVICE_ENABLE
    USB_DEVICE_MODE,
#endif

#if FM_MODULE 
    FM_RADIO_MODE,
#endif

    AUX_MODE,
#if RTC_ENABLE
    RTC_MODE,
#endif
    REC_MIC_MODE,
    IDLE_MODE,
};


#if(NO_DISP == monitor)
    #define    set_brightness(n)
    #define    set_brightness_fade_out()
    #define    set_brightness_all_on()
    #define    disp_port(n)
    #define    disp_scan()
    extern void flashled(u8 fre);
    extern void disp_dled(void);
    extern void dled_ctl(u8 flag);
#else
    extern void flashled(u8 fre);
    extern void disp_dled(void);
    extern void dled_ctl(u8 flag);
    extern void set_brightness(u8 br);
    extern void set_brightness_fade_out(void);
    extern void set_brightness_all_on(void);
    extern void disp_port(u8 menu);
#endif

#endif
                               //(PLL_IN_OSC0_32K | PLL_IN_OSC0_4M | PLL_IN_OSC0_12M | PLL_IN_OSC1_4M | PLL_IN_OSC1_12M | PLL_IN_HPRC)//
//输入时钟选择，具体请见clock.h                                         
#if defined(OSC_USE_12M)
#define INPUT_OSC_SELECT                PLL_IN_OSC1_12M// PLL_IN_HPRC//
#else
#define INPUT_OSC_SELECT                PLL_IN_OSC0_32K // PLL_IN_HPRC//
#endif
#define SHARE_32768_PERIPHERALS    0					///<是否与外设共用32768晶体，0：不共用，1：共用晶体（如收音等）


                                       
///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 RTC_MODE
#else
#define MAX_WORK_MODE	 FM_RADIO_MODE
#endif

#define IDLE_WORK_MODE   REC_MIC_MODE


//音乐播放功能选择
#define    BREAK_POINT_PLAY_EN				1			//是否允许断点播放功能
#define    LAST_MEM_FILE_PLAY_EN            0			//是否允许记忆文件序号播放功能
//#define    ID3_TAG_EN						0
#define    FF_FR_EN                         1			//是否允许快进快退功能
#define    FF_FR_MUSIC                      1			//在快进快退时，是否需要听到声音

#define    BURST_OUT_POINT_SAVE_ENABLE      0			//突然断电使能位,1有效,3.3V需要电容支持至少100μF
#define    MUSIC_FADE_OUT_EN				0			//切换歌曲的淡出使能， 1有效
#define    VIRTUAL_ENABLE                   1           ///<虚拟设别使能 1：enable；0：disable；

#define   KALAOK_FUNCTION     				0		   ///<开卡拉ok功能
#define   CH_MODE_SUBTRACT					0          ///<在music模式下开了扩音机时是否要把歌曲声相减

#define     ECHO_ENABLE                     0          ///<混响功能使能
//sd检测模式
#define SDMMC_CLK_MODE   1	  ///<使用SD clk 查询模式
#define SDMMC_GPIO_MODE  0	  ///<使用独立的GPIO做SD在线查询模式



#define     MP3CLK      BIT(6)
#define     SPIURCLK    BIT(4)
#define     DACCLK      BIT(6)   
#define     USBCLK      BIT(0)
#define     SDCLK       BIT(5)



#define     REC_MIC_GAIN     6
#define     REC_MIC_VOL      55
#define     REC_AMUX_GAIN    3
#define     REC_ECHO_STRONG  145

#define     ECHO_MIC_GAIN    7
#define     ECHO_MIC_VOL     64
#define     ECHO_STRONG      150




#endif
