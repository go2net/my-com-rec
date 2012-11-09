/*--------------------------------------------------------------------------*/
/**@file     config.h
   @brief    Ò»Ð©»ù±¾²ÎÊýµÄÅäÖÃ
   @author
   @date   2010-12-13
   @note   AC309N
*/
/*----------------------------------------------------------------------------*/
//#define UART_ENABLE
#ifdef UART_ENABLE
#define USE_UART_P24_P25
#endif

#define MUTE_CTRL_LEVEL_NORMAL
//#define NO_IR_REMOTE
//#define DEFAULT_VOL		30
//#define INDEPENDENT_REC_LED

//#define IIC_GPIO_USE_P00_P01
//#define IIC_GPIO_USE_P02_P03
//#define EXCHANGE_AUX_CHANNEL
//#define CUSTOM_DEFINED_FOLDER
//#define NO_LED_DISPLAY
//#define REC_GPIO_CTRL

//#define FM_USE_RDA5807
//#define FM_USE_BK1080
//#define FM_USE_QN8035
//#define FM_USE_AR1015

//#define K015_SW005_REC_V001
//#define K015_JR3006_REC_V001
//#define K3016_JR_SW005_REC_V001
//#define K800_ZX800_REC_V001
//#define K797_LHD_797_REC_V001
//#define K820_LHD_820_REC_V001
//#define K800_ZX_800_REC_V001
//#define K800_KDL_800_REC_V001
//#define K800_YDS_800_REC_V001
//#define K813_FW_813_REC_V001
//#define K1033_XINGLEI_1033_REC_V001
//#define K000_LUOMAO_308_REC_V001
//#define K646_ZX_308_REC_V001
//#define K1059_LS_1059_REC_V001
//#define K1075_LS_1075_REC_V001
//#define K2035_SES_2035_REC_V001
//#define K2035_SES_2035_REC_V002
//#define K000_LYXD_00000_REC_V001
//#define K1071_HYM_1071_REC_V001
//#define K1081_WK_1081_REC_V001
//#define K1093_XL_1093_REC_V001
//#define K1091_JK_1091_REC_V001
//#define K000_XL_X15_REC_V001
//#define K000_XL_DNK411_REC_V001
//#define K000_HYM_01_004_REC_V001
//#define K000_CHENGQIANG_REC_V003
//#define K1093_YJH_1093_REC_V001
//#define K1120_LHD_1120_REC_V001
//#define K1118_YJH_1118_REC_V001
//#define K2069_SES_2069_REC_V001
//#define KSBSX_SES_20A_REC_V001
//#define K1153_AJR_LSK8_REC_V001
//#define K1189_AJR_LSK8_REC_V001
//#define K0000_XFW_GL005_REC_V001
//#define K1181_YDT_1181_REC_V001
//#define K0000_GW_613_REC_V001
#define K0000_BHT_C202_REC_V001


#if defined(K0000_BHT_C202_REC_V001)

#define IIC_GPIO_USE_P02_P03

#define ADKEY_PORT_P06
#define LED_GPIO_USE_P04
#define DISP_HI_NO_BAR

#define LED_GPIO_PORT_CUSTOMERIZED

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_REC_TIME_PAUSE

#define MUTE_PORT_USE_P01
#define EXCHANGE_AUX_CHANNEL
#define FM_SCAN_ALL_PP_ONE_KEY

#define FM_USE_BK1080
#define DEL_REC_FILE_ONLY
#endif


#if defined(K0000_GW_613_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define LED_USE_NORMAL_4X8
#if 1
#define COMMON_CATHODE	
#define GUOWEI_ADKEY_RES_1
#endif

#define INDEPENDENT_REC_LED
#define MUSIC_NO_PLAY_LED
#define REC_LED_GPIO_USE_P07

#define ADKEY_PORT_P06

#define PLAY_STATUS_SPARK_WHEN_RECORDING
#define POWER_OFF_IN_IDEL
//#define NO_IDLE_MODE_FUNC
#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_DUMP
#define EXCHANGE_AUX_CHANNEL
#define LED_RUN_FAST_WHEN_PLAY_MODE_AT_REP_ONE
#define DISP_REC_IN_ENCODE_MODE

#define DEFAULT_GOTO_AUX
#define FM_USE_QN8035
#define QN_SCAN_ST_ENABLE
#define NO_LED_BRIGHTNESS_FADEOUT

#define THREE_SEC_AT_VALID_STATION

//#define INDEPENDENT_AUX_VOL_KEY
//#define AMP_MODE_SELECT_PORT_USE_P04
#define EXTENDED_AUX_FUNC
#endif


#if defined(K1181_YDT_1181_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define LED_GPIO_PORT_CUSTOMERIZED

#define ADKEY_PORT_P06
#define LED_GPIO_USE_P07

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define FM_USE_AR1015

#define USE_AMP_MODE_SELECT
#define AMP_MODE_SELECT_PORT_USE_P04
#endif

#if defined(K0000_XFW_GL005_REC_V001)

#define IIC_GPIO_USE_P02_P03

#define ADKEY_PORT_P06
#define IR_KEYBOARD_TYPE_3
#define LED_GPIO_USE_P07

#define POWER_OFF_IN_IDEL

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P01
#define EXCHANGE_AUX_CHANNEL
#define NO_ENCODE_FUNC

#define DISP_LINE_STR

#define AUX_DETECT_USE_P17
#define USE_LINE_IN_DETECT_FUNC

#define FM_USE_BK1080
#define FM_USE_RDA5807

//#define AMP_MODE_SELECT_PORT_USE_P0
#endif


#if defined(K1189_AJR_LSK8_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define NO_IR_REMOTE
#define COMMON_CATHODE
#define LED_COMMON_SCAN_COM_USE_P17
#define NO_LED_BRIGHTNESS_FADEOUT
#undef MUTE_CTRL_LEVEL_NORMAL

#define ADKEY_PORT_P06
#define IDLE_MODE_FOR_VOICE_AMP
#define REC_LED_GPIO_USE_P04

#define DISP_PAUS_STR
#define DISP_LINE_STR
#define MUSIC_NO_PLAY_LED
#define INDEPENDENT_REC_LED
#define NO_REC_LED_SPARK_IN_REC

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

//#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_GOTO_IDLE
#define USE_MANUAL_IDLE_FUNC

//#define AUX_DETECT_USE_P07
//#define USE_LINE_IN_DETECT_FUNC

#define FM_USE_BK1080
#define USE_HPHONE_DETECT
#define HP_DETECT_USE_P34

#define USE_AMP_MODE_SELECT
#define MUTE_PORT_USE_P07
//#undef MUTE_CTRL_LEVEL_NORMAL
#endif

#if defined(K1153_AJR_LSK8_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define NO_IR_REMOTE
#define LED_GPIO_PORT_CUSTOMERIZED

#define ADKEY_PORT_P06
#define IDLE_MODE_FOR_VOICE_AMP
#define REC_LED_GPIO_USE_P04

#define MUTE_PORT_FOR_2_AMP
#define AMP_2_MUTE_PORT_USE_P07
#define DISP_PAUS_STR
#define DISP_LINE_STR
#define MUSIC_NO_PLAY_LED
#define INDEPENDENT_REC_LED
#define NO_REC_LED_SPARK_IN_REC

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_GOTO_IDLE
#define USE_MANUAL_IDLE_FUNC

//#define AUX_DETECT_USE_P07
//#define USE_LINE_IN_DETECT_FUNC

#define FM_USE_RDA5807
#define USE_HPHONE_DETECT
#define HP_DETECT_USE_P34

#define USE_AMP_MODE_SELECT
//#define AMP_MODE_SELECT_PORT_USE_P0
#endif


#if defined(KSBSX_SES_20A_REC_V001)

#define IIC_GPIO_USE_P00_P01
//#define NO_IR_REMOTE

#define ADKEY_PORT_P06
#define IDLE_MODE_FOR_VOICE_AMP
//#define CUSTOM_DEFINED_FOLDER

#define USE_TWO_ADKEY

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_GOTO_IDLE
#define USE_MANUAL_IDLE_FUNC

//#define AUX_DETECT_USE_P07
//#define USE_LINE_IN_DETECT_FUNC

#define FM_USE_AR1015
//#define USE_HPHONE_DETECT
//#define HP_DETECT_USE_P02

#define USE_AMP_MODE_SELECT
#define AMP_MODE_SELECT_PORT_USE_P04
#endif

#if defined(K2069_SES_2069_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define NO_IR_REMOTE
#define LED_GPIO_PORT_CUSTOMERIZED

#define ADKEY_PORT_P06
#define IDLE_MODE_FOR_VOICE_AMP
//#define CUSTOM_DEFINED_FOLDER

#define USE_TWO_ADKEY

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_GOTO_IDLE
#define USE_MANUAL_IDLE_FUNC

#define NOT_USE_LINE_IN_FUNC
#define FM_USE_AR1015
#define USE_HPHONE_DETECT
#define HP_DETECT_USE_P02

#define USE_AMP_MODE_SELECT
#define AMP_MODE_SELECT_PORT_USE_P04
#endif

#if defined(K1118_YJH_1118_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define NO_IR_REMOTE
//efine CUSTOM_DEFINED_FOLDER
#define LED_GPIO_PORT_CUSTOMERIZED
#define REC_PLAY_BREAK_POINT
#define ADKEY_RES_VALUE_2
#define ADKEY_PORT_P06
#define NOR_LED_EXCHANGE_FM_MP3_ICON
#define USE_TWO_ADKEY
#define DISP_PAUSE_STR

#define DEFAULT_VOL			MAX_MAIN_VOL
#define REPEAT_MODE_USE_ONE_ALL

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define FM_PLAY_KEY_FOR_PAUSE

#define FM_USE_BK1080
#define USE_HPHONE_DETECT
#define HP_DETECT_USE_P04
#endif

#if defined(K1120_LHD_1120_REC_V001)

#define IIC_GPIO_USE_P00_P01

#define LED_GPIO_PORT_CUSTOMERIZED
//#define LED_COMMON_SCAN_COM_USE_P17

#define NOR_LED_EXCHANGE_FM_MP3_ICON

#define MUTE_PORT_USE_P03

#define EXCHANGE_AUX_CHANNEL

#define LED_GPIO_USE_P02

#define FM_USE_BK1080
#define ADKEY_PORT_P06

//#define DEFAULT_VOL			MAX_MAIN_VOL

#define DEFAULT_GOTO_IDLE

#endif

#if defined(K1093_YJH_1093_REC_V001)

#define IIC_GPIO_USE_P00_P01

#undef  MUTE_CTRL_LEVEL_NORMAL
#define NOR_LED_EXCHANGE_FM_MP3_ICON

#define MUTE_PORT_USE_P03

#define EXCHANGE_AUX_CHANNEL

#define LED_GPIO_USE_P02

#define FM_USE_AR1015

#define IDLE_MODE_FOR_VOICE_AMP

#define USE_AMP_MODE_SELECT

//#define DEFAULT_VOL			MAX_MAIN_VOL
#define ADKEY_PORT_P06

#define DEFAULT_GOTO_IDLE

#endif

#if defined(K000_CHENGQIANG_REC_V003)

#define NO_IR_REMOTE
#define IIC_GPIO_USE_P02_P03
#define LED_CUSTOM_SCAN_HARDWARE
#define DISP_HI_NO_BAR
#define MUTE_PORT_USE_P01

#define EXCHANGE_AUX_CHANNEL

#define LED_GPIO_USE_P00

#define FM_USE_RDA5807

//#define DEFAULT_VOL			MAX_MAIN_VOL
#define ADKEY_PORT_P07
#define CUSTOME_ADKEY_NUM_13
#define CUSTOM_DEFINE_VOL
#define DEFAULT_USE_EQ_ROCK

#define CUSTOM_FREQ_FILTER

#define DEFAULT_GOTO_IDLE
#define MUTE_AMP_IN_IDLE_MODE
#define USE_MIC_INPUT_VOLT_FOR_DETECTION

#define MICPHONE_GPIO_DETECTION
#if 0
//#define USE_LINE_IN_DETECT_FUNC
//#define AUX_DETECT_SHARE_WITH_IIC
//#define AUX_DETECT_USE_P03
#endif

#define USE_MANUAL_IDLE_FUNC
#define USE_AMP_MODE_SELECT
#define AMP_MODE_SELECT_PORT_USE_P06

#endif

#if defined(K000_HYM_01_004_REC_V001)

#define IIC_GPIO_USE_P00_P01

#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_AR1015

#define DEFAULT_VOL			MAX_MAIN_VOL
#define ADKEY_PORT_P06

#define DEFAULT_GOTO_IDLE
#define REC_GPIO_CTRL
#define MICPHONE_GPIO_DETECTION

#define USE_MANUAL_IDLE_FUNC
#define POWER_ON_DEFAULT_IN_IDLE

#endif

#if defined(K000_XL_DNK411_REC_V001)

#define USE_AMP_MODE_SELECT
#undef  MUTE_CTRL_LEVEL_NORMAL

#define NO_PLAY_STATUS_LED
#define AUX_USE_PP_KEY_FOR_MUTE

#define NO_IR_REMOTE

#define ADKEY_PORT_P06


#define USE_BAT_MANAGEMENT
#define CHARGER_DET_USE_VPP
#define CHARGER_DETECT_INDICATOR
#define CHARGER_IND_TYPE_1

#define HP_DETECT_USE_P04
#define USE_HPHONE_DETECT

#define IIC_GPIO_USE_P02_P03
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define FM_USE_BK1080

#define AUX_DETECT_USE_P07
#define USE_LINE_IN_DETECT_FUNC

#define DEFAULT_VOL		MAX_MAIN_VOL
//#define CUSTOM_DEFINED_FOLDER
#endif

#if defined(K000_XL_X15_REC_V001)

#define IIC_GPIO_USE_P00_P01

#define LED_GPIO_USE_P07
#define AUX_USE_PP_KEY_FOR_MUTE

#define NO_IR_REMOTE

#define INDEPENDENT_FM_OSC

#define ADKEY_PORT_P06

#define USE_BAT_MANAGEMENT
#define CHARGER_DET_USE_PORT_P17
#define CHARGER_DETECT_INDICATOR
#define CHARGER_IND_TYPE_1

#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define FM_USE_AR1015
//#define DEFAULT_GOTO_AUX
#define AUX_DETECT_USE_P04
#define USE_LINE_IN_DETECT_FUNC

#define DEFAULT_VOL		MAX_MAIN_VOL
#define VDD_VOLT_CAL_USE_PORT_P02

#endif

#if defined(K1091_JK_1091_REC_V001)

#define NO_LED_DISPLAY
#define INDEPENDENT_REC_LED
#define REC_LED_GPIO_USE_P04
#define DEFAULT_GOTO_IDLE
#undef  MUTE_CTRL_LEVEL_NORMAL

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P02
#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_AR1015

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
#endif


#if defined(K1093_XL_1093_REC_V001)

#define NO_PLAY_STATUS_LED

#define ADKEY_PORT_P06
#undef  MUTE_CTRL_LEVEL_NORMAL
#define USE_AMP_MODE_SELECT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

 #define FM_USE_AR1015
#define DEFAULT_VOL			MAX_MAIN_VOL

#define CUSTOM_DEFINED_FOLDER
#endif

#if defined(K1081_WK_1081_REC_V001)

#define NO_PLAY_STATUS_LED
#define AUX_USE_PP_KEY_FOR_MUTE

#define NO_IR_REMOTE
#define JOG_STICK_FUNC
#define ADKEY_PORT_P06
#define USE_TWO_ADKEY
#define USE_10_PLUS_FUNC
#define USE_BAT_MANAGEMENT
#define CHARGER_DET_USE_VPP
#define CHARGER_DETECT_INDICATOR
#define CHARGER_IND_TYPE_1

#define HP_DETECT_USE_P17
#define USE_HPHONE_DETECT

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define FM_USE_BK1080

//#define DEFAULT_VOL		15
//#define CUSTOM_DEFINED_FOLDER
#endif

#if defined(K1075_LS_1075_REC_V001)

#define NO_LED_DISPLAY

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_QN8035

#define DEFAULT_VOL		16
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
#endif


#if defined(K1071_HYM_1071_REC_V001)

#define IIC_GPIO_USE_P00_P01

#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_AR1015

#define DEFAULT_VOL			MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#define DEFAULT_GOTO_IDLE
//#define NOT_USE_LINE_IN_FUNC
#define USE_MANUAL_IDLE_FUNC
#define POWER_ON_DEFAULT_IN_IDLE

#endif


#if defined(K000_LYXD_00000_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define JOG_STICK_FUNC
#define JOG_STICK_FUNC_USE_TWO

#define NO_IR_REMOTE
#define HP_DETECT_USE_VPP

#define MICPHONE_REC_ONLY

#define NO_PLAY_STATUS_LED

#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_QN8035

#define USE_HPHONE_DETECT

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06


//#define LED_GPIO_USE_P07
#endif

#if defined(K2035_SES_2035_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define IR_KEYBOARD_TYPE_2
//#undef MUTE_CTRL_LEVEL_NORMAL
#define IDLE_MODE_FOR_VOICE_AMP

#define EXCHANGE_AUX_CHANNEL
#define MUTE_PORT_USE_P03

#define FM_USE_AR1015

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
//#define LED_GPIO_USE_P07

#define DEFAULT_GOTO_IDLE
#define NOT_USE_LINE_IN_FUNC
#define USE_MANUAL_IDLE_FUNC

#define USE_BAT_MANAGEMENT
#define VDD_VOLT_CAL_USE_PORT_P04

#define USE_AMP_MODE_SELECT
#endif

#if defined(K2035_SES_2035_REC_V002)

#define IIC_GPIO_USE_P00_P01

//#undef MUTE_CTRL_LEVEL_NORMAL
#define IDLE_MODE_FOR_VOICE_AMP

#define IR_KEYBOARD_TYPE_2
#define IIC_GPIO_USE_P00_P01

#define EXCHANGE_AUX_CHANNEL
#define MUTE_PORT_USE_P03
//#define POWER_OFF_IN_IDEL
#define FM_USE_AR1015

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
//#define LED_GPIO_USE_P07

#define DEFAULT_GOTO_IDLE
#define NOT_USE_LINE_IN_FUNC
//#define USE_MANUAL_IDLE_FUNC
#define USE_BAT_MANAGEMENT
#define VDD_VOLT_CAL_USE_PORT_P04

#define USE_AMP_MODE_SELECT

#endif

#if defined(K1059_LS_1059_REC_V001)

#define NO_LED_DISPLAY

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define FM_USE_QN8035

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
#endif

#if defined(K646_ZX_308_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#define AUX_DETECT_USE_P02
#define USE_LINE_IN_DETECT_FUNC
#endif

#if defined(K000_LUOMAO_308_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define LED_GPIO_USE_P07

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
#define DEFAULT_GOTO_IDLE

#endif


#if defined(K1033_XINGLEI_1033_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#endif

#if defined(K813_FW_813_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#endif

#if defined(K813_FW_813_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		MAX_MAIN_VOL
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#endif

#if defined(K800_YDS_800_REC_V001)

#define IIC_GPIO_USE_P00_P01

#define MUTE_PORT_USE_P03

#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		30
#define ADKEY_PORT_P06

#define FM_USE_AR1015

#endif

#if defined(K800_KDL_800_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		28
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER
#define MICPHONE_GPIO_DETECTION
#define MIC_DETECT_PORT_USE_P17

#define FM_USE_AR1015

#endif

#if defined(K800_ZX_800_REC_V001)

#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03
#define EXCHANGE_AUX_CHANNEL
#define POWER_ON_DEFAULT_IN_AUX
#define DEFAULT_VOL		28
#define ADKEY_PORT_P06
#define CUSTOM_DEFINED_FOLDER

#endif

#if defined(K820_LHD_820_REC_V001)
#define IIC_GPIO_USE_P00_P01
#define MUTE_PORT_USE_P03

#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define ADKEY_PORT_P06
#define LED_GPIO_USE_P07
#define CUSTOM_DEFINED_FOLDER
#define REPEAT_MODE_USE_ONE_ALL

#endif

#if defined(K797_LHD_797_REC_V001)
#define DEFAULT_VOL		24
#define INDEPENDENT_FM_OSC
#define OSC_USE_12M
#define FM_CHIP_BYPASS
#define NO_LED_DISPLAY
#define USE_12M_CRYSTAL
#define MUTE_PORT_USE_P25
#define ADKEY_PORT_P02
#define IIC_GPIO_USE_P05_P17
#define LED_GPIO_USE_P16
#define CUSTOM_DEFINED_FOLDER
#endif

#if defined(K3016_JR_SW005_REC_V001)
#define IIC_GPIO_USE_P02_P03
#define FM_USE_BK1080
#define NO_PLAY_STATUS_LED
#define ADKEY_PORT_P06
#define POWER_OFF_IN_IDEL
#endif


#if defined(K015_JR3006_REC_V001)
#define IIC_GPIO_USE_P02_P03
#define FM_USE_QN8035
#define NO_PLAY_STATUS_LED
#define ADKEY_PORT_P06
#define JINRUI_IR_KEYBOARD_TYPE
#define USE_MUSIC_STOP_FUNC
//#define DEFAULT_GOTO_IDLE
//#define NO_FM_CHIP_GOTO_MP3
#endif

#if defined(K015_SW005_REC_V001)
#define IIC_GPIO_USE_P02_P03
#define FM_USE_QN8035
#define NO_PLAY_STATUS_LED
#define ADKEY_PORT_P06
#define POWER_OFF_IN_IDEL
#endif


#ifndef _CONFIG_
#define _CONFIG_

#include "AC309N.h"
#include "typedef.h"
#include "entry.h"
#include "clock.h"



#define USB_DEVICE_ENABLE		0		///¸ù¾Ý¿Í»§Ñ¡ÓÃµÄbsp¿â£¬¶ÔÓ¦µØÑ¡ÔñÊÇ·ñ´ò¿ª
#define RTC_ENABLE              0       ///<RTCÊ¹ÄÜ£¬Èç¹û²»ÐèÒªÊ¹ÓÃRTC¹¦ÄÜ£¬´Ë´¦Ìî0


//ÏÔÊ¾ÆÁÑ¡Ôñ

#define DISP_LED5X7           1
#define DLED				  2
#define NO_DISP				  3
#define LCD_DISP				  4

#ifdef LCD_GPIO_DRV
#define monitor       LCD_DISP
#else
#define monitor       DISP_LED5X7//NO_DISP//  
#endif

#ifdef __C51__
#include "intrins.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "encode.h"

typedef enum
{
    DIS_SD_CMD_CHK = 0,	///<ÔÚÃüÁî¼ì²âSD¿¨ÔÚÏß×´Ì¬µÄÇé¿öÏÂ£¬ÔÝÍ£SDÔÚÏß¼ì²â
    EN_SD_CMD_CHK,		///<ÔÚÃüÁî¼ì²âSD¿¨ÔÚÏß×´Ì¬µÄÇé¿öÏÂ£¬»Ö¸´SDÔÚÏß¼ì²â
    SET_SD_H_CHK,		///<ÔÚÃüÁî¼ì²âSD¿¨ÔÚÏß×´Ì¬µÄÇé¿öÏÂ£¬SD²»ÔÚÏßÊ±¼ì²â100MSÒ»´Î
    SET_SD_L_CHK,		///<ÔÚÃüÁî¼ì²âSD¿¨ÔÚÏß×´Ì¬µÄÇé¿öÏÂ£¬SD²»ÔÚÏßÊ±¼ì²â1SÒ»´Î
}Sd_api_cmd;

#ifdef UART_ENABLE
#define NO_FM_CHIP
#endif

//fmÄ£¿éÑ¡Ô
#if defined(NO_FM_CHIP)
#define RDA5807      0
#define CL6017G      0
#define BK1080       0
#define KT0830EG     0
#define QN8035       0
#define AR1015      0
#elif defined(FM_USE_RDA5807)
#define RDA5807      1
#define CL6017G      0
#define BK1080       0
#define KT0830EG     0
#define QN8035       0
#define AR1015      0
#elif defined(FM_USE_QN8035)
#define RDA5807      0
#define CL6017G      0
#define BK1080       0
#define KT0830EG     0
#define QN8035       1
#define AR1015      0
#elif defined(FM_USE_AR1015)
#define RDA5807      0
#define CL6017G      0
#define BK1080       0
#define KT0830EG     0
#define QN8035       0
#define AR1015     1
#else
#define RDA5807      0
#define CL6017G      0
#define BK1080       1
#define KT0830EG     0
#define QN8035       0
#define AR1015      0
#endif

#if defined(K800_ZX_800_REC_V001)||defined(K813_FW_813_REC_V001)
#undef BK1080
#define BK1080       0
#undef AR1015
#define AR1015      1
#define INDEPENDENT_FM_OSC
#endif

#if(AR1015 ==1)
#define INDEPENDENT_FM_OSC
#endif

#if ((1 == RDA5807)||(1 == CL6017G)||(1 == BK1080)||(1 == KT0830EG)||(1 == QN8035)||(1 == AR1015))		///<ÊÇ·ñÓÐfmÄ£¿é
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

#ifndef NOT_USE_LINE_IN_FUNC
    AUX_MODE,
#endif

#if RTC_ENABLE
    RTC_MODE,
#endif

    IDLE_MODE,
    
    REC_MIC_MODE,    
};


#if(NO_DISP == monitor)
    #define    set_brightness(n)
    #define    set_brightness_fade_out()
    #define    set_brightness_all_on()
    #define    disp_port(n)
    #define    disp_scan()
    void flashled(u8 fre);
    void disp_dled(void);
    void dled_ctl(u8 flag);
#else
    void  flashled(u8 fre);
    void  disp_dled(void);
    void  dled_ctl(u8 flag);
    extern void set_brightness(u8 br);
    extern void set_brightness_fade_out(void);
    extern void set_brightness_all_on(void);
    extern void disp_port(u8 menu);
#endif

#endif
                               //(PLL_IN_OSC0_32K | PLL_IN_OSC0_4M | PLL_IN_OSC0_12M | PLL_IN_OSC1_4M | PLL_IN_OSC1_12M | PLL_IN_HPRC)//
//ÊäÈëÊ±ÖÓÑ¡Ôñ£¬¾ßÌåÇë¼ûclock.h   
#if defined(OSC_USE_12M)
#define INPUT_OSC_SELECT                PLL_IN_OSC1_12M// PLL_IN_HPRC//
#else
#define INPUT_OSC_SELECT                PLL_IN_OSC0_32K // PLL_IN_HPRC//
#endif
#define SHARE_32768_PERIPHERALS    0					///<ÊÇ·ñÓëÍâÉè¹²ÓÃ32768¾§Ìå£¬0£º²»¹²ÓÃ£¬1£º¹²ÓÃ¾§Ìå£¨ÈçÊÕÒôµÈ£©


                                       
///////work mode
#if RTC_ENABLE
#define MAX_WORK_MODE	 RTC_MODE
#else

#ifdef NOT_USE_LINE_IN_FUNC
#define MAX_WORK_MODE	 FM_RADIO_MODE
#else
#define MAX_WORK_MODE	 AUX_MODE
#endif

#ifdef USE_MANUAL_IDLE_FUNC
#undef MAX_WORK_MODE
#define MAX_WORK_MODE	 IDLE_MODE
#endif

#endif

#define IDLE_WORK_MODE   REC_MIC_MODE


//ÒôÀÖ²¥·Å¹¦ÄÜÑ¡Ôñ
#define    BREAK_POINT_PLAY_EN				0			//ÊÇ·ñÔÊÐí¶Ïµã²¥·Å¹¦ÄÜ
#define    LAST_MEM_FILE_PLAY_EN            1			//ÊÇ·ñÔÊÐí¼ÇÒäÎÄ¼þÐòºÅ²¥·Å¹¦ÄÜ
//#define    ID3_TAG_EN						0
#define    FF_FR_EN                         1			//ÊÇ·ñÔÊÐí¿ì½ø¿ìÍË¹¦ÄÜ
#define    FF_FR_MUSIC                      0			//ÔÚ¿ì½ø¿ìÍËÊ±£¬ÊÇ·ñÐèÒªÌýµ½ÉùÒô

#define    BURST_OUT_POINT_SAVE_ENABLE      0			//Í»È»¶ÏµçÊ¹ÄÜÎ»,1ÓÐÐ§,3.3VÐèÒªµçÈÝÖ§³ÖÖÁÉÙ100¦ÌF
#define    MUSIC_FADE_OUT_EN				1			//ÇÐ»»¸èÇúµÄµ­³öÊ¹ÄÜ£¬ 1ÓÐÐ§
#define    VIRTUAL_ENABLE                   1           ///<ÐéÄâÉè±ðÊ¹ÄÜ 1£ºenable£»0£ºdisable£»

//sd¼ì²âÄ£Ê½

#define SDMMC_CLK_MODE   1	  ///<Ê¹ÓÃSD clk ²éÑ¯Ä£Ê½
#define SDMMC_GPIO_MODE  0	  ///<Ê¹ÓÃ¶ÀÁ¢µÄGPIO×öSDÔÚÏß²éÑ¯Ä£Ê½



#define     MP3CLK      BIT(6)
#define     SPIURCLK    BIT(4)
#define     DACCLK      BIT(6)
#define     USBCLK      BIT(0)
#define     SDCLK       BIT(5)


#endif

