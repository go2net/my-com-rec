/*--------------------------------------------------------------------------*/
/**@file   my_IR_key.c
   @brief  ���ⰴ����ֵӳ���
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "key.h"
#include "my_IR_key.h"

#if 1//def _MY_IR_KEY_

#if defined(IR_KEYBOARD_TYPE_2)
_code MY_IR_KEY_STRUCT My_IRTab[]=       /*user code is 0xFF*/
{
	{My_IR_KEY_0,			IR_00},
	{My_IR_KEY_1,			IR_01},
	{My_IR_KEY_2,			IR_02},
	{My_IR_KEY_3,			IR_03},
	{My_IR_KEY_4,			IR_04},
	{My_IR_KEY_5,			IR_05},
	{My_IR_KEY_6,			IR_06},
	{My_IR_KEY_7,			IR_07},
	{My_IR_KEY_8,			IR_08},
	{My_IR_KEY_9,			IR_09},
	{My_IR_KEY_100,			IR_10},
	{My_IR_KEY_MODE,		IR_11},
	{My_IR_KEY_PLAY,			IR_12},
	{My_IR_KEY_PLAY_M,		IR_13},
	{My_IR_KEY_VOL_UP,		IR_14},
	{My_IR_KEY_VOL_DN,		IR_15},
	{My_IR_KEY_PREV,		IR_16},
	{My_IR_KEY_NEXT,		IR_17},
	{My_IR_KEY_EQ_UP,		IR_18},
	{My_IR_KEY_CHN_UP,		IR_19},
	{My_IR_KEY_CHN_DN,		IR_20},
};
#elif defined(JINRUI_IR_KEYBOARD_TYPE)
_code MY_IR_KEY_STRUCT My_IRTab[]=       /*user code is 0xFF*/
{
	{My_IR_KEY_0,			IR_00},
	{My_IR_KEY_1,			IR_01},
	{My_IR_KEY_2,			IR_02},
	{My_IR_KEY_3,			IR_03},
	{My_IR_KEY_4,			IR_04},
	{My_IR_KEY_5,			IR_05},
	{My_IR_KEY_6,			IR_06},
	{My_IR_KEY_7,			IR_07},
	{My_IR_KEY_8,			IR_08},
	{My_IR_KEY_9,			IR_09},
	{My_IR_KEY_100,			IR_10},
	{My_IR_KEY_MODE,		IR_11},
	{My_IR_KEY_PLAY,			IR_12},
	{My_IR_KEY_PLAY_M,		IR_13},
	{My_IR_KEY_VOL_UP,		IR_14},
	{My_IR_KEY_VOL_DN,		IR_15},
	{My_IR_KEY_PREV,		IR_16},
	{My_IR_KEY_NEXT,		IR_17},
	{My_IR_KEY_EQ_UP,		IR_18},
	{My_IR_KEY_CHN_UP,		IR_19},
	{My_IR_KEY_CHN_DN,		IR_20},
};
#else
_code MY_IR_KEY_STRUCT My_IRTab[]=       /*user code is 0xFF*/
{
	{My_IR_KEY_0,			IR_00},
	{My_IR_KEY_1,			IR_01},
	{My_IR_KEY_2,			IR_02},
	{My_IR_KEY_3,			IR_03},
	{My_IR_KEY_4,			IR_04},
	{My_IR_KEY_5,			IR_05},
	{My_IR_KEY_6,			IR_06},
	{My_IR_KEY_7,			IR_07},
	{My_IR_KEY_8,			IR_08},
	{My_IR_KEY_9,			IR_09},
	{My_IR_KEY_100,			IR_10},
	{My_IR_KEY_MODE,		IR_11},
	{My_IR_KEY_PLAY,			IR_16},
	{My_IR_KEY_PLAY_M,		IR_13},
	{My_IR_KEY_VOL_UP,		IR_18},
	{My_IR_KEY_VOL_DN,		IR_14},
	{My_IR_KEY_PREV,		IR_12},
	{My_IR_KEY_NEXT,		IR_17},
	{My_IR_KEY_EQ_UP,		IR_15},
	{My_IR_KEY_CHN_UP,		IR_19},
	{My_IR_KEY_CHN_DN,		IR_20},
};
#endif
u8 get_my_IR_key_MAX()
{
	return (u8)((sizeof(My_IRTab))/2);
}
#endif


