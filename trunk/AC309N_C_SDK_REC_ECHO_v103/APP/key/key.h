/*--------------------------------------------------------------------------*/
/**@file   key.h
   @brief  ������Ϣɨ��ͷ�ļ�
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef	_KEY_H_
#define _KEY_H_

#include "config.h"

#ifdef __C51__


typedef struct _KEY_VOICE
{
    u16 vol;
    u16 cnt;
    u16 start;
    u16 end;
} KEY_VOICE;

///msg define
enum
{
    MSG_0 = 0,
    MSG_1,
    MSG_2,
    MSG_3,
    MSG_4,
    MSG_5,
    MSG_6,
    MSG_7,
    MSG_8,
    MSG_9,
    MSG_100,
    MSG_DEVICE_REMOVED,
    MSG_CHANGE_WORK_MODE,
    MSG_MUSIC_NEW_DEVICE_IN,
    MSG_MUSIC_SELECT_NEW_DEVICE,
    MSG_MUSIC_SELECT_NEW_FILE,
    MSG_MUSIC_PLAY_NEW_FILE,
    MSG_VOL_UP,
    MSG_VOL_DOWN,
    MSG_MUSIC_NEXT_FILE,
    MSG_MUSIC_PREV_FILE,
    MSG_MUSIC_PP,
    MSG_MUSIC_PLAY,
    MSG_MUSIC_PAUSE,
    MSG_MUSIC_FF,
    MSG_MUSIC_FR,
    MSG_MUSIC_FFR_DONE,
    MSG_MUSIC_NEXT_EQ,
    MSG_MUSIC_PREV_EQ,
    MSG_NEXT_PLAYMODE,
    MSG_PREV_PLAYMODE,
    MSG_NEXT_WORKMODE,
    MSG_PREV_WORKMODE,
    MSG_PICH_SONG,
    MSG_PICH_DEVICE,
    MSG_NEXT_DEVICE,
    MSG_PREV_DEVICE,
    MSG_REV_SW,
	MSG_REV_STRONG_UP,
	MSG_REV_STRONG_DOWN,	
    MSG_REV_DEEP_UP,
    MSG_REV_DEEP_DOWN,


    MSG_FM_NEXT_STEP,
    MSG_FM_PREV_STEP,
    MSG_FM_NEXT_STATION,
    MSG_FM_PREV_STATION,
    MSG_FM_PP,
    MSG_FM_SCAN_ALL,
    MSG_FM_SCAN_ALL_UP,
    MSG_FM_SCAN_ALL_DOWN,
    MSG_FM_SCAN_UP,
    MSG_FM_SCAN_DOWN,
    MSG_CH_SET,
    MSG_CH_SAVE,
    MSG_KEY_CHANGE,

    MSG_NO_DEVICE,
    MSG_MUTE,
    MSG_UNMUTE,
    MSG_MUTE_UNMUTE,
    MSG_POWER_ON,
    MSG_POWER_DOWN,
    MSG_POWER_KEY_HOLD,
    MSG_100MS,
    MSG_200MS,					  //53
    /*
    	MSG_RTC_SETTING,
    	MSG_RTC_NEXT,
    	MSG_RTC_PREV,
    	MSG_RTC_PLUS,
    	MSG_RTC_MINUS,
    */
    MSG_CLOSE_ALARM,
    MSG_SYS_DOWN,
    MSG_REQUEST_Y,
    MSG_REQUEST_N,

    MSG_REC_FIND,
    MSG_REC_START,
    MSG_REC_STOP,
    MSG_REC_PAUSE,
    MSG_REC_CONTINUE,
    MSG_REC_PLAY,
    MSG_REC_KEY,
	MSG_REC_PP,
	MSG_REPEAT_REC,
    MSG_DEVICE_MODE,
	MSG_KALAOK,
	MSG_DEL_ALL_FILE,
    MSG_DEL_CURR_FILE,
	MSG_ENCODE_FAT_FULL,

    MSG_USB_DISK_IN = 0xE0,
    MSG_USB_DISK_OUT,
    MSG_USB_PC_IN,
    MSG_USB_PC_OUT,
    MSG_SDMMC_IN,
    MSG_SDMMC_OUT,
    MSG_PC_MUTE,
    MSG_PC_UNMUTE,
    MSG_AUX_IN,
    MSG_AUX_OUT,
    MSG_MIC_IN,
    MSG_MIC_OUT,    
    MSG_MIC_IN_CLEAR,    
    MSG_HALF_SECOND,
    MSG_LOW_POWER,
    MSG_NORMAL_POWER,
    MSG_ALM_ON,
    MSG_ENCODE_END,
    MSG_DECODE_FILE_END = 0xFD,
    MSG_DECODE_DISK_ERR = 0xFE,
    NO_MSG = 0xff,
};
enum {

	SYS_PWR_ON,
	SYS_PWR_OFF,
	SYS_PWR_IDLE,
	
};
void timer3Init_ir(void);
void timer3isr(void);
void key_init(void);
void keyScan(void);
void adc_scan(void);
u8 keyDetect(void);
u8 app_get_msg(void);
void key_table_sel(u8 sel);
u8 ldoin_voltage(void);
void set_key_tone(void);
void alarm_tone(void);
void bmt_hdlr(void);
void Bat_icon_chk(void);
void power_key_hdlr(u8  pwr_cmd);

void kv_init(void);
#endif


#define ADC_KEY_IO7     0xFF
#define ADC_KEY_IO6     0xFE
#define ADC_KEY_IO5     0xFD
#define ADC_KEY_IO4     0xFC
#define ADC_KEY_IO3     0xFB
#define ADC_KEY_IO2     0xFA

#define ADC_VDD_12     0xf8
#define ADC_LDOIN      0xf9
#define ADC_MAX_USED   0x03

//////////////////////////////////////////////////////////
#define    EVENT_UDISK_IN       0
#define    EVENT_UDISK_OUT		1
#define    EVENT_PC_IN			2
#define    EVENT_PC_OUT			3
#define    EVENT_SDMMC_IN		4
#define    EVENT_SDMMC_OUT		5
#define    EVENT_PC_MUTE		6
#define    EVENT_PC_UNMUTE		7
#define    EVENT_AUX_IN			8
#define    EVENT_AUX_OUT		9
#define    EVENT_ALM_ON			10



#define KEY_BASE_CNT  8
#define KEY_LONG_CNT  (75)
#define KEY_HOLD_CNT  15



#define  NO_KEY              0xff
#define  NO_EVENT            0xff
#define  MAX_EVENT           16

/*ir key define*/
#define IR_00                   0
#define IR_01                   1
#define IR_02                   2
#define IR_03                   3
#define IR_04                   4
#define IR_05                   5
#define IR_06                   6
#define IR_07                   7
#define IR_08                   8
#define IR_09                   9
#define IR_10                   10
#define IR_11                   11
#define IR_12                   12
#define IR_13                   13
#define IR_14                   14
#define IR_15                   15
#define IR_16                   16
#define IR_17                   17
#define IR_18                   18
#define IR_19                   19
#define IR_20                   20
#define IR_21                   21
#define IR_22                   22

//////////////////////////////////
#define NKEY_00               0xff
#define NKEY_01               0xff
#define NKEY_02               0xff
#define NKEY_03               0xff
#define NKEY_04               0xff
#define NKEY_05               0xff
#define NKEY_06               0xff
#define NKEY_07               0xff
#define NKEY_08               0xff
#define NKEY_09               0xff
#define NKEY_0A               0xff
#define NKEY_0B               0xff
#define NKEY_0C               0xff
#define NKEY_0D               0xff
#define NKEY_0E               0xff
#define NKEY_0F               0xff
#define NKEY_10               0xff
#define NKEY_11               0xff
#define NKEY_12               0xff
#define NKEY_13               0xff
#define NKEY_14               0xff
#define NKEY_15               0xff
#define NKEY_16               0xff
#define NKEY_17               0xff
#define NKEY_18               0xff
#define NKEY_19               0xff
#define NKEY_1A               0xff
#define NKEY_1B               0xff
#define NKEY_1C               0xff
#define NKEY_1D               0xff
#define NKEY_1E               0xff
#define NKEY_1F               0xff
#define NKEY_20               0xff
#define NKEY_21               0xff
#define NKEY_22               0xff
#define NKEY_23               0xff
#define NKEY_24               0xff
#define NKEY_25               0xff
#define NKEY_26               0xff
#define NKEY_27               0xff
#define NKEY_28               0xff
#define NKEY_29               0xff
#define NKEY_2A               0xff
#define NKEY_2B               0xff
#define NKEY_2C               0xff
#define NKEY_2D               0xff
#define NKEY_2E               0xff
#define NKEY_2F               0xff
#define NKEY_30               0xff
#define NKEY_31               0xff
#define NKEY_32               0xff
#define NKEY_33               0xff
#define NKEY_34               0xff
#define NKEY_35               0xff
#define NKEY_36               0xff
#define NKEY_37               0xff
#define NKEY_38               0xff
#define NKEY_39               0xff
#define NKEY_3A               0xff
#define NKEY_3B               0xff
#define NKEY_3C               0xff
#define NKEY_3D               0xff
#define NKEY_3E               0xff
#define NKEY_3F               0xff
#define NKEY_40               0xff
#define NKEY_41               0xff
#define NKEY_42               0xff
#define NKEY_43               0xff
#define NKEY_44               0xff
#define NKEY_45               0xff
#define NKEY_46               0xff
#define NKEY_47               0xff
#define NKEY_48               0xff
#define NKEY_49               0xff
#define NKEY_4A               0xff
#define NKEY_4B               0xff
#define NKEY_4C               0xff
#define NKEY_4D               0xff
#define NKEY_4E               0xff
#define NKEY_4F               0xff
#define NKEY_50               0xff
#define NKEY_51               0xff
#define NKEY_52               0xff
#define NKEY_53               0xff
#define NKEY_54               0xff
#define NKEY_55               0xff
#define NKEY_56               0xff
#define NKEY_57               0xff
#define NKEY_58               0xff
#define NKEY_59               0xff
#define NKEY_5A               0xff
#define NKEY_5B               0xff
#define NKEY_5C               0xff
#define NKEY_5D               0xff
#define NKEY_5E               0xff
#define NKEY_5F               0xff
#define NKEY_60               0xff
#define NKEY_61               0xff
#define NKEY_62               0xff
#define NKEY_63               0xff
#define NKEY_64               0xff
#define NKEY_65               0xff
#define NKEY_66               0xff
#define NKEY_67               0xff
#define NKEY_68               0xff
#define NKEY_69               0xff
#define NKEY_6A               0xff
#define NKEY_6B               0xff
#define NKEY_6C               0xff
#define NKEY_6D               0xff
#define NKEY_6E               0xff
#define NKEY_6F               0xff
#define NKEY_70               0xff
#define NKEY_71               0xff
#define NKEY_72               0xff
#define NKEY_73               0xff
#define NKEY_74               0xff
#define NKEY_75               0xff
#define NKEY_76               0xff
#define NKEY_77               0xff
#define NKEY_78               0xff
#define NKEY_79               0xff
#define NKEY_7A               0xff
#define NKEY_7B               0xff
#define NKEY_7C               0xff
#define NKEY_7D               0xff
#define NKEY_7E               0xff
#define NKEY_7F               0xff
#define NKEY_80               0xff
#define NKEY_81               0xff
#define NKEY_82               0xff
#define NKEY_83               0xff
#define NKEY_84               0xff
#define NKEY_85               0xff
#define NKEY_86               0xff
#define NKEY_87               0xff
#define NKEY_88               0xff
#define NKEY_89               0xff
#define NKEY_8A               0xff
#define NKEY_8B               0xff
#define NKEY_8C               0xff
#define NKEY_8D               0xff
#define NKEY_8E               0xff
#define NKEY_8F               0xff
#define NKEY_90               0xff
#define NKEY_91               0xff
#define NKEY_92               0xff
#define NKEY_93               0xff
#define NKEY_94               0xff
#define NKEY_95               0xff
#endif


