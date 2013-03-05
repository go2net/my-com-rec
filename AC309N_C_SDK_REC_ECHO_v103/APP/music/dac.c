/*--------------------------------------------------------------------------*/
/**@file   dac.h
   @brief  dac头文件
   @details
   @author
   @date   2011-5-18
   @note
*/
/*----------------------------------------------------------------------------*/
#include "dac.h"

///<数字音量表 16位的数组
_code u16 digital_vol_tab[] =
{
    0	  ,
    93	  ,
    111	  ,
    132	  ,
    158	  ,
    189	  ,
    226	  ,
    270	  ,
    323	  ,
    386	  ,
    462	  ,
    552	  ,
    660	  ,
    789	  ,
    943	  ,
    1127  ,
    1347  ,
    1610  ,
    1925  ,
    2301  ,
    2751  ,
    3288  ,
    3930  ,
    4698  ,
    5616  ,
    6713  ,
    8025  ,
    9592  ,
    11466 ,
    15200,//13706 ,
    16384
};

///<模拟音量表 8位的数组
_code u8 analog_vol_tab[] =
{
    0x1f,
    0x0e,
    0x1f,
    0x1e,
    0x0d,
    0x0c,
    0x1d,
    0x1c,
    0x0b,
    0x0a,
    0x1b,
    0x1a,
    0x09,
    0x08,
    0x19,
    0x18,
    0x07,
    0x06,
    0x17,
    0x05,
    0x16,
    0x04,
    0x15,

    0x03,
    0x14,

    0x02,
    0x01,
    0x0,
    0x13,
    0x12,
    0x11,
    0x10
};



/*----------------------------------------------------------------------------*/
/**@brief    功放Mute开关函数
   @param	 mute：Mute开关
   @return	 无
   @note     void amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
#define AMP_MUTE_PORT_INIT() 	// P0DIR &= ~BIT(3);P0PU &= ~BIT(3);P0PD &= ~BIT(3)
#define AMP_MUTE_DISABLE()	 	// P03 = 0
#define AMP_MUTE_ENABLE() 	 	//P03 = 1

#define ONE_WIRE_CTRL_PORT_HIGH()		//P03  =1
#define ONE_WIRE_CTRL_PORT_LOW()		//P03  =0

void one_wire_delay(u16 d_t)
{
	while(d_t-->0);
}
void one_wire_ctrl_if(u8 pulse_num)
{
	AMP_MUTE_PORT_INIT();

	//printf("one_wire_ctrl_if \r\n");
	
	do{
		ONE_WIRE_CTRL_PORT_LOW();
		one_wire_delay(30);
		ONE_WIRE_CTRL_PORT_HIGH();
		one_wire_delay(30);
	}
	while(pulse_num-->0);

	ONE_WIRE_CTRL_PORT_HIGH();
	one_wire_delay(20);	
}

void amp_mute(bool mute)
{
    AMP_MUTE_PORT_INIT();
    if (mute)
    {
        AMP_MUTE_ENABLE();
    }
    else
    {
        AMP_MUTE_DISABLE();
    }
}


