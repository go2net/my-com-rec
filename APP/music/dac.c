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

/*----------------------------------------------------------------------------*/
/**@brief    功放Mute开关函数
   @param	 mute：Mute开关
   @return	 无
   @note     void ext_amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
#include "gpio_if.h"
#if 0
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~BIT(1);P0PU &= ~BIT(1);P0PD &= ~BIT(1)
#define AMP_MUTE_DISABLE() 	 P01 = 0
#define AMP_MUTE_ENABLE() 	 P01 = 1
#endif
#ifdef  USE_HPHONE_DETECT   
extern bool hp_online;
#endif
void ext_amp_mute(bool mute)
{
    AMP_MUTE_PORT_INIT();

#ifdef MUTE_PORT_FOR_2_AMP
    AMP_MUTE_PORT_INIT_2();
#endif	
	
    if (mute==EXT_AMP_MUTE)
    {
#ifdef MUTE_PORT_FOR_2_AMP
        AMP_MUTE_ENABLE_2();
#endif
        AMP_MUTE_ENABLE();
    }
    else
    {
#ifdef  USE_HPHONE_DETECT   
  	if(hp_online)return;
#endif			

#ifdef MUTE_PORT_FOR_2_AMP
        AMP_MUTE_DISABLE_2();
#endif
        AMP_MUTE_DISABLE();
    }
}
