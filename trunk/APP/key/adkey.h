/*--------------------------------------------------------------------------*/
/**@file   adkey.h
   @brief  AD按键定义
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#ifndef	_ADKEY_H_
#define _ADKEY_H_
#include "my_adkey.h"
/************ADKEY GROUP 1****************/

#if defined(CUSTOME_ADKEY_NUM_13)
#define ADKEY1			0xf300
#define ADKEY1_0		0xDF00
#define ADKEY1_1		0xD000
#define ADKEY1_2		0xC000
#define ADKEY1_3		0xB000
#define ADKEY1_4		0xA000
#define ADKEY1_5		0x9300
#define ADKEY1_6		0x8300
#define ADKEY1_7		0x7300
#define ADKEY1_8		0x6400
#define ADKEY1_9		0x5300
#define ADKEY1_10		0x4300
#define ADKEY1_11		0x3400
#define ADKEY1_12		0x1600
#elif defined(ADKEY_RES_VALUE_2)

#define ADKEY1			(0xff40-0xe840)/2+0xe840
#define ADKEY1_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY1_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY1_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY1_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY1_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY1_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY1_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY1_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY1_8		(0x1e40-0x0)/2+0x0
#elif defined(NEW_ADKEY_RES_CAL_MOTHED)

#define RES_PULL_UP			22000		/// 3.3K
#define RES_1				16000
#define RES_2				24000
#define RES_3				36000	
#define RES_4				51000
#define RES_5				220000
#define RES_6				510000
#define RES_7				910000
#define RES_8				220000

#define ADKEY1_8			(((255*RES_2)/(RES_2+RES_PULL_UP)+(255*RES_1)/(RES_1+RES_PULL_UP))/2)
#define ADKEY1_7			(((255*RES_3)/(RES_3+RES_PULL_UP)+(255*RES_2)/(RES_2+RES_PULL_UP))/2)	
#define ADKEY1_6			(((255*RES_4)/(RES_4+RES_PULL_UP)+(255*RES_3)/(RES_3+RES_PULL_UP))/2)	
#define ADKEY1_5			(((255*RES_5)/(RES_5+RES_PULL_UP)+(255*RES_4)/(RES_4+RES_PULL_UP))/2)
#define ADKEY1_4			(((255*RES_6)/(RES_6+RES_PULL_UP)+(255*RES_5)/(RES_5+RES_PULL_UP))/2)
#define ADKEY1_3			(((255*RES_7)/(RES_7+RES_PULL_UP)+(255*RES_6)/(RES_6+RES_PULL_UP))/2)
#define ADKEY1_2			(((255*RES_8)/(RES_8+RES_PULL_UP)+(255*RES_7)/(RES_7+RES_PULL_UP))/2)
#define ADKEY1_1			0xF0
#define ADKEY1_0			0xF0
#define ADKEY1			0xF0
#elif defined(GUOWEI_ADKEY_RES_1)
#define ADKEY1			(0xf000)
#define ADKEY1_0		(0xf000)
#define ADKEY1_1		(0xf000)
#define ADKEY1_2		0xf000
#define ADKEY1_3		0xf000
#define ADKEY1_4		0xDB00
#define ADKEY1_5		0xC000
#define ADKEY1_6		0xA500
#define ADKEY1_7		0x8E00
#define ADKEY1_8		0x7300
#else

#define ADKEY1			(0xf000)
#define ADKEY1_0		(0xf000)
#define ADKEY1_1		(0xf000)
#define ADKEY1_2		0xd400
#define ADKEY1_3		0xb080
#define ADKEY1_4		0x9040
#define ADKEY1_5		0x7000
#define ADKEY1_6		0x4DC0
#define ADKEY1_7		0x2D40
#define ADKEY1_8		(0x1F80)/2

#endif

#if defined(CUSTOME_ADKEY_NUM_13)

#define TOTAL_KEY_NUM	14

u16 _code adkey1_check_table[] = {ADKEY1_0, ADKEY1_1, ADKEY1_2, ADKEY1_3, ADKEY1_4, ADKEY1_5, ADKEY1_6, ADKEY1_7, ADKEY1_8,
								ADKEY1_9,ADKEY1_10,ADKEY1_11,ADKEY1_12,};
//
#define ADKEY1_MUSIC_SHORT		\
                                				/*00*/    MSG_REC_KEY,\
							    	/*01*/    MSG_VOL_DOWN,\
								/*02*/    MSG_VOL_UP,\
								/*03*/    MSG_MUSIC_PREV_FILE,\
								/*04*/    MSG_MUSIC_NEXT_FILE,\
								/*05*/    MSG_NEXT_PLAYMODE,\
								/*06*/    MSG_MUSIC_NEXT_EQ,\
								/*07*/    MSG_POWER_DOWN,\
								/*08*/    MSG_MUSIC_PREV_FILE,\
								/*09*/    MSG_MUSIC_NEXT_FILE,\
								/*10*/    MSG_NEXT_WORKMODE,\
								/*11*/    MSG_MUSIC_PP,\
								/*12*/    MSG_MUSIC_PP,\
								/*13*/    MSG_MUSIC_PP,

#define ADKEY1_MUSIC_LONG		\
                                				/*00*/    MSG_NEXT_PLAYMODE,\
                                				/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    MSG_NEXT_WORKMODE,\
								/*12*/    MSG_DEL_CURR_FILE,\
								/*13*/    MSG_POWER_DOWN,


#define ADKEY1_MUSIC_HOLD		\
                                				/*00*/    NO_MSG,\
                                				/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_MUSIC_FR,\
								/*04*/    MSG_MUSIC_FF,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    MSG_VOL_DOWN,\
								/*09*/    MSG_VOL_UP,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,

#define ADKEY1_MUSIC_LONG_UP	\
                                				/*00*/    NO_MSG,\
                                				/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    MSG_MUSIC_FFR_DONE,\
								/*04*/    MSG_MUSIC_FFR_DONE,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,

const u8 _code adkey1_msg_music_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_MUSIC_SHORT},
    /*长按*/		{ADKEY1_MUSIC_LONG},
    /*连按*/		{ADKEY1_MUSIC_HOLD},
    /*长按抬起*/	{ADKEY1_MUSIC_LONG_UP},
};

//
#define ADKEY1_FM_SHORT			\
								/*00*/    MSG_REC_KEY,\
							    	/*01*/    MSG_VOL_DOWN,\
								/*02*/    MSG_VOL_UP,\
								/*03*/    MSG_FM_PREV_STATION,\
								/*04*/    MSG_FM_NEXT_STATION,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    MSG_POWER_DOWN,\
								/*08*/    MSG_FM_PREV_STATION,\
								/*09*/    MSG_FM_NEXT_STATION,\
								/*10*/    MSG_NEXT_WORKMODE,\
								/*11*/    MSG_FM_SCAN_ALL,\
								/*12*/    MSG_FM_SCAN_ALL,\
								/*13*/    MSG_FM_SCAN_ALL,

#define ADKEY1_FM_LONG			\
								/*00*/    NO_MSG,\
                               	 			/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    MSG_NEXT_WORKMODE,\
								/*12*/    NO_MSG,\
								/*13*/    MSG_POWER_DOWN,

#define ADKEY1_FM_HOLD			\
								/*00*/    NO_MSG,\
                                				/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    MSG_VOL_DOWN,\
								/*09*/    MSG_VOL_UP,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    NO_MSG,\
                                				/*01*/    NO_MSG,\
								/*02*/    NO_MSG,\
								/*03*/    NO_MSG,\
								/*04*/    NO_MSG,\
								/*05*/    NO_MSG,\
								/*06*/    NO_MSG,\
								/*07*/    NO_MSG,\
								/*08*/    NO_MSG,\
								/*09*/    NO_MSG,\
								/*10*/    NO_MSG,\
								/*11*/    NO_MSG,\
								/*12*/    NO_MSG,\
								/*13*/    NO_MSG,

const u8 _code adkey1_msg_fm_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_FM_SHORT},
    /*长按*/		{ADKEY1_FM_LONG},
    /*连按*/		{ADKEY1_FM_HOLD},
    /*长按抬起*/	{ADKEY1_FM_LONG_UP},
};


#else

#define TOTAL_KEY_NUM	10

u16 _code adkey1_check_table[] = {ADKEY1_0, ADKEY1_1, ADKEY1_2, ADKEY1_3, ADKEY1_4, ADKEY1_5, ADKEY1_6, ADKEY1_7, ADKEY1_8,};
//
#define ADKEY1_MUSIC_SHORT		\
                                				/*00*/    MUSIC_ADKEY_SHORT_00,\
							    	/*01*/    MUSIC_ADKEY_SHORT_01,\
								/*02*/    MUSIC_ADKEY_SHORT_02,\
								/*03*/    MUSIC_ADKEY_SHORT_03,\
								/*04*/    MUSIC_ADKEY_SHORT_04,\
								/*05*/    MUSIC_ADKEY_SHORT_05,\
								/*06*/    MUSIC_ADKEY_SHORT_06,\
								/*07*/    MUSIC_ADKEY_SHORT_07,\
								/*08*/    MUSIC_ADKEY_SHORT_08,\
								/*09*/    MUSIC_ADKEY_SHORT_09,

#define ADKEY1_MUSIC_LONG		\
                                				/*00*/    MUSIC_ADKEY_LONG_00,\
                                				/*01*/    MUSIC_ADKEY_LONG_01,\
								/*02*/    MUSIC_ADKEY_LONG_02,\
								/*03*/    MUSIC_ADKEY_LONG_03,\
								/*04*/    MUSIC_ADKEY_LONG_04,\
								/*05*/    MUSIC_ADKEY_LONG_05,\
								/*06*/    MUSIC_ADKEY_LONG_06,\
								/*07*/    MUSIC_ADKEY_LONG_07,\
								/*08*/    MUSIC_ADKEY_LONG_08,\
								/*09*/    MUSIC_ADKEY_LONG_09,


#define ADKEY1_MUSIC_HOLD		\
                                				/*00*/    MUSIC_ADKEY_HOLD_00,\
                                				/*01*/    MUSIC_ADKEY_HOLD_01,\
								/*02*/    MUSIC_ADKEY_HOLD_02,\
								/*03*/    MUSIC_ADKEY_HOLD_03,\
								/*04*/    MUSIC_ADKEY_HOLD_04,\
								/*05*/    MUSIC_ADKEY_HOLD_05,\
								/*06*/    MUSIC_ADKEY_HOLD_06,\
								/*07*/    MUSIC_ADKEY_HOLD_07,\
								/*08*/    MUSIC_ADKEY_HOLD_08,\
								/*09*/    MUSIC_ADKEY_HOLD_09,

#define ADKEY1_MUSIC_LONG_UP	\
                                				/*00*/    MUSIC_ADKEY_L_UP_00,\
                                				/*01*/    MUSIC_ADKEY_L_UP_01,\
								/*02*/    MUSIC_ADKEY_L_UP_02,\
								/*03*/    MUSIC_ADKEY_L_UP_03,\
								/*04*/    MUSIC_ADKEY_L_UP_04,\
								/*05*/    MUSIC_ADKEY_L_UP_05,\
								/*06*/    MUSIC_ADKEY_L_UP_06,\
								/*07*/    MUSIC_ADKEY_L_UP_07,\
								/*08*/    MUSIC_ADKEY_L_UP_08,\
								/*09*/    MUSIC_ADKEY_L_UP_09,

const u8 _code adkey1_msg_music_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_MUSIC_SHORT},
    /*长按*/		{ADKEY1_MUSIC_LONG},
    /*连按*/		{ADKEY1_MUSIC_HOLD},
    /*长按抬起*/	{ADKEY1_MUSIC_LONG_UP},
};

//
#define ADKEY1_FM_SHORT			\
								/*00*/    FM_ADKEY_SHORT_00,\
							    	/*01*/    FM_ADKEY_SHORT_01,\
								/*02*/    FM_ADKEY_SHORT_02,\
								/*03*/    FM_ADKEY_SHORT_03,\
								/*04*/    FM_ADKEY_SHORT_04,\
								/*05*/    FM_ADKEY_SHORT_05,\
								/*06*/    FM_ADKEY_SHORT_06,\
								/*07*/    FM_ADKEY_SHORT_07,\
								/*08*/    FM_ADKEY_SHORT_08,\
								/*09*/    FM_ADKEY_SHORT_09,

#define ADKEY1_FM_LONG			\
								/*00*/    FM_ADKEY_LONG_00,\
                               	 			/*01*/    FM_ADKEY_LONG_01,\
								/*02*/    FM_ADKEY_LONG_02,\
								/*03*/    FM_ADKEY_LONG_03,\
								/*04*/    FM_ADKEY_LONG_04,\
								/*05*/    FM_ADKEY_LONG_05,\
								/*06*/    FM_ADKEY_LONG_06,\
								/*07*/    FM_ADKEY_LONG_07,\
								/*08*/    FM_ADKEY_LONG_08,\
								/*09*/    FM_ADKEY_LONG_09,

#define ADKEY1_FM_HOLD			\
								/*00*/    FM_ADKEY_HOLD_00,\
                                				/*01*/    FM_ADKEY_HOLD_01,\
								/*02*/    FM_ADKEY_HOLD_02,\
								/*03*/    FM_ADKEY_HOLD_03,\
								/*04*/    FM_ADKEY_HOLD_04,\
								/*05*/    FM_ADKEY_HOLD_05,\
								/*06*/    FM_ADKEY_HOLD_06,\
								/*07*/    FM_ADKEY_HOLD_07,\
								/*08*/    FM_ADKEY_HOLD_08,\
								/*09*/    FM_ADKEY_HOLD_09,


#define ADKEY1_FM_LONG_UP		\
								/*00*/    FM_ADKEY_L_UP_00,\
                                				/*01*/    FM_ADKEY_L_UP_01,\
								/*02*/    FM_ADKEY_L_UP_02,\
								/*03*/    FM_ADKEY_L_UP_03,\
								/*04*/    FM_ADKEY_L_UP_04,\
								/*05*/    FM_ADKEY_L_UP_05,\
								/*06*/    FM_ADKEY_L_UP_06,\
								/*07*/    FM_ADKEY_L_UP_07,\
								/*08*/    FM_ADKEY_L_UP_08,\
								/*09*/    FM_ADKEY_L_UP_09,

const u8 _code adkey1_msg_fm_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY1_FM_SHORT},
    /*长按*/		{ADKEY1_FM_LONG},
    /*连按*/		{ADKEY1_FM_HOLD},
    /*长按抬起*/	{ADKEY1_FM_LONG_UP},
};

#endif

#ifdef USE_TWO_ADKEY

#if defined(ADKEY_RES_VALUE_2)

#define ADKEY2			(0xff40-0xe840)/2+0xe840
#define ADKEY2_0		(0xe800-0xd1c0)/2+0xd1c0
#define ADKEY2_1		(0xd140-0xb2c0)/2+0xb2c0
#define ADKEY2_2		(0xb2c0-0x99c0)/2+0x99c0
#define ADKEY2_3		(0x9980-0x85c0)/2+0x85c0
#define ADKEY2_4		(0x8540-0x67c0)/2+0x67c0
#define ADKEY2_5		(0x66c0-0x4ac0)/2+0x4ac0
#define ADKEY2_6		(0x49c0-0x3740)/2+0x3740
#define ADKEY2_7		(0x3700-0x1e80)/2+0x1e80
#define ADKEY2_8		(0x1e40-0x0)/2+0x0

#else

#define ADKEY2			(0xf000)
#define ADKEY2_0		(0xf000)
#define ADKEY2_1		(0xf000)
#define ADKEY2_2		0xd400
#define ADKEY2_3		0xb080
#define ADKEY2_4		0x9040
#define ADKEY2_5		0x7000
#define ADKEY2_6		0x4DC0
#define ADKEY2_7		0x2D40
#define ADKEY2_8		(0x1F80)/2

#endif
#define TOTAL_KEY_NUM	10

u16 _code adkey2_check_table[] = {ADKEY2_0, ADKEY2_1, ADKEY2_2, ADKEY2_3, ADKEY2_4, ADKEY2_5, ADKEY2_6, ADKEY2_7, ADKEY2_8,};
//
#define ADKEY2_MUSIC_SHORT		\
                                				/*00*/    MUSIC_ADKEY2_SHORT_00,\
							    	/*01*/    MUSIC_ADKEY2_SHORT_01,\
								/*02*/    MUSIC_ADKEY2_SHORT_02,\
								/*03*/    MUSIC_ADKEY2_SHORT_03,\
								/*04*/    MUSIC_ADKEY2_SHORT_04,\
								/*05*/    MUSIC_ADKEY2_SHORT_05,\
								/*06*/    MUSIC_ADKEY2_SHORT_06,\
								/*07*/    MUSIC_ADKEY2_SHORT_07,\
								/*08*/    MUSIC_ADKEY2_SHORT_08,\
								/*09*/    MUSIC_ADKEY2_SHORT_09,

#define ADKEY2_MUSIC_LONG		\
                                				/*00*/    MUSIC_ADKEY2_LONG_00,\
                                				/*01*/    MUSIC_ADKEY2_LONG_01,\
								/*02*/    MUSIC_ADKEY2_LONG_02,\
								/*03*/    MUSIC_ADKEY2_LONG_03,\
								/*04*/    MUSIC_ADKEY2_LONG_04,\
								/*05*/    MUSIC_ADKEY2_LONG_05,\
								/*06*/    MUSIC_ADKEY2_LONG_06,\
								/*07*/    MUSIC_ADKEY2_LONG_07,\
								/*08*/    MUSIC_ADKEY2_LONG_08,\
								/*09*/    MUSIC_ADKEY2_LONG_09,


#define ADKEY2_MUSIC_HOLD		\
                                				/*00*/    MUSIC_ADKEY2_HOLD_00,\
                                				/*01*/    MUSIC_ADKEY2_HOLD_01,\
								/*02*/    MUSIC_ADKEY2_HOLD_02,\
								/*03*/    MUSIC_ADKEY2_HOLD_03,\
								/*04*/    MUSIC_ADKEY2_HOLD_04,\
								/*05*/    MUSIC_ADKEY2_HOLD_05,\
								/*06*/    MUSIC_ADKEY2_HOLD_06,\
								/*07*/    MUSIC_ADKEY2_HOLD_07,\
								/*08*/    MUSIC_ADKEY2_HOLD_08,\
								/*09*/    MUSIC_ADKEY2_HOLD_09,

#define ADKEY2_MUSIC_LONG_UP	\
                                				/*00*/    MUSIC_ADKEY2_L_UP_00,\
                                				/*01*/    MUSIC_ADKEY2_L_UP_01,\
								/*02*/    MUSIC_ADKEY2_L_UP_02,\
								/*03*/    MUSIC_ADKEY2_L_UP_03,\
								/*04*/    MUSIC_ADKEY2_L_UP_04,\
								/*05*/    MUSIC_ADKEY2_L_UP_05,\
								/*06*/    MUSIC_ADKEY2_L_UP_06,\
								/*07*/    MUSIC_ADKEY2_L_UP_07,\
								/*08*/    MUSIC_ADKEY2_L_UP_08,\
								/*09*/    MUSIC_ADKEY2_L_UP_09,

const u8 _code adkey2_msg_music_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY2_MUSIC_SHORT},
    /*长按*/		{ADKEY2_MUSIC_LONG},
    /*连按*/		{ADKEY2_MUSIC_HOLD},
    /*长按抬起*/	{ADKEY2_MUSIC_LONG_UP},
};

//
#define ADKEY2_FM_SHORT			\
								/*00*/    FM_ADKEY2_SHORT_00,\
							    	/*01*/    FM_ADKEY2_SHORT_01,\
								/*02*/    FM_ADKEY2_SHORT_02,\
								/*03*/    FM_ADKEY2_SHORT_03,\
								/*04*/    FM_ADKEY2_SHORT_04,\
								/*05*/    FM_ADKEY2_SHORT_05,\
								/*06*/    FM_ADKEY2_SHORT_06,\
								/*07*/    FM_ADKEY2_SHORT_07,\
								/*08*/    FM_ADKEY2_SHORT_08,\
								/*09*/    FM_ADKEY2_SHORT_09,

#define ADKEY2_FM_LONG			\
								/*00*/    FM_ADKEY2_LONG_00,\
                               	 			/*01*/    FM_ADKEY2_LONG_01,\
								/*02*/    FM_ADKEY2_LONG_02,\
								/*03*/    FM_ADKEY2_LONG_03,\
								/*04*/    FM_ADKEY2_LONG_04,\
								/*05*/    FM_ADKEY2_LONG_05,\
								/*06*/    FM_ADKEY2_LONG_06,\
								/*07*/    FM_ADKEY2_LONG_07,\
								/*08*/    FM_ADKEY2_LONG_08,\
								/*09*/    FM_ADKEY2_LONG_09,

#define ADKEY2_FM_HOLD			\
								/*00*/    FM_ADKEY2_HOLD_00,\
                                				/*01*/    FM_ADKEY2_HOLD_01,\
								/*02*/    FM_ADKEY2_HOLD_02,\
								/*03*/    FM_ADKEY2_HOLD_03,\
								/*04*/    FM_ADKEY2_HOLD_04,\
								/*05*/    FM_ADKEY2_HOLD_05,\
								/*06*/    FM_ADKEY2_HOLD_06,\
								/*07*/    FM_ADKEY2_HOLD_07,\
								/*08*/    FM_ADKEY2_HOLD_08,\
								/*09*/    FM_ADKEY2_HOLD_09,


#define ADKEY2_FM_LONG_UP		\
								/*00*/    FM_ADKEY2_L_UP_00,\
                                				/*01*/    FM_ADKEY2_L_UP_01,\
								/*02*/    FM_ADKEY2_L_UP_02,\
								/*03*/    FM_ADKEY2_L_UP_03,\
								/*04*/    FM_ADKEY2_L_UP_04,\
								/*05*/    FM_ADKEY2_L_UP_05,\
								/*06*/    FM_ADKEY2_L_UP_06,\
								/*07*/    FM_ADKEY2_L_UP_07,\
								/*08*/    FM_ADKEY2_L_UP_08,\
								/*09*/    FM_ADKEY2_L_UP_09,

const u8 _code adkey2_msg_fm_table[4][TOTAL_KEY_NUM] =				//Music模式下的遥控转换表
{
    /*短按*/	    {ADKEY2_FM_SHORT},
    /*长按*/		{ADKEY2_FM_LONG},
    /*连按*/		{ADKEY2_FM_HOLD},
    /*长按抬起*/	{ADKEY2_FM_LONG_UP},
};

#endif
#endif


