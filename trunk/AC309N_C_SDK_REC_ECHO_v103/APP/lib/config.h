/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    һЩ��������������
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


#define USB_DEVICE_ENABLE		0		///���ݿͻ�ѡ�õ�bsp�⣬��Ӧ��ѡ���Ƿ��
#define RTC_ENABLE              0       ///<RTCʹ�ܣ��������Ҫʹ��RTC���ܣ��˴���0


//��ʾ��ѡ��

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
    DIS_SD_CMD_CHK = 0,	///<��������SD������״̬������£���ͣSD���߼��
    EN_SD_CMD_CHK,		///<��������SD������״̬������£��ָ�SD���߼��
    SET_SD_H_CHK,		///<��������SD������״̬������£�SD������ʱ���100MSһ��
    SET_SD_L_CHK,		///<��������SD������״̬������£�SD������ʱ���1Sһ��
}Sd_api_cmd;


//fmģ��ѡ��
#define RDA5807      0
#define CL6017G      0
#define BK1080       1
#define KT0830EG     0
#define QN8035       0


#if ((1 == RDA5807)||(1 == CL6017G)||(1 == BK1080)||(1 == KT0830EG)||(1 == QN8035))		///<�Ƿ���fmģ��
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
//����ʱ��ѡ�񣬾������clock.h                                         
#define INPUT_OSC_SELECT                PLL_IN_OSC0_32K // PLL_IN_HPRC//
#define SHARE_32768_PERIPHERALS    0					///<�Ƿ������蹲��32768���壬0�������ã�1�����þ��壨�������ȣ�


                                       
///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 RTC_MODE
#else
#define MAX_WORK_MODE	 AUX_MODE
#endif

#define IDLE_WORK_MODE   REC_MIC_MODE


//���ֲ��Ź���ѡ��
#define    BREAK_POINT_PLAY_EN				1			//�Ƿ�����ϵ㲥�Ź���
#define    LAST_MEM_FILE_PLAY_EN            0			//�Ƿ���������ļ���Ų��Ź���
//#define    ID3_TAG_EN						0
#define    FF_FR_EN                         1			//�Ƿ����������˹���
#define    FF_FR_MUSIC                      1			//�ڿ������ʱ���Ƿ���Ҫ��������

#define    BURST_OUT_POINT_SAVE_ENABLE      0			//ͻȻ�ϵ�ʹ��λ,1��Ч,3.3V��Ҫ����֧������100��F
#define    MUSIC_FADE_OUT_EN				0			//�л������ĵ���ʹ�ܣ� 1��Ч
#define    VIRTUAL_ENABLE                   1           ///<�������ʹ�� 1��enable��0��disable��

#define   KALAOK_FUNCTION     				0		   ///<������ok����
#define   CH_MODE_SUBTRACT					0          ///<��musicģʽ�¿���������ʱ�Ƿ�Ҫ�Ѹ��������

#define     ECHO_ENABLE                     0          ///<���칦��ʹ��
//sd���ģʽ
#define SDMMC_CLK_MODE   1	  ///<ʹ��SD clk ��ѯģʽ
#define SDMMC_GPIO_MODE  0	  ///<ʹ�ö�����GPIO��SD���߲�ѯģʽ



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
