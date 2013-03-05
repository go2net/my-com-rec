/*--------------------------------------------------------------------------*/
/**@file     echo_ctl.c
   @brief    混响控制文件
   @details
   @author
   @date   2012-10-09
   @note
*/
/*----------------------------------------------------------------------------*/
#include "echo.h"
#include "msgfor_hot.h"
#include "dac.h"
#include "main.h"



REVERB_CTL _xdata * echo_ptr;		///<混响结构体指针
APP_REVERB _xdata app_echo;

extern u8 work_mode;
extern u8 music_type;

/*----------------------------------------------------------------------------*/
/**@brief   各个模式下混响功能使能函数
   @param   void
   @return  void
   @note    void echo_enable(void)
*/
/*----------------------------------------------------------------------------*/
void echo_enable(void)
{

    //16k  (0x4<<13) | (0xb<<9) | (0 & 0x1ff)
    //24k  (0x4<<13) | (0x7<<9) | (0 & 0x1ff) 
    //32k  (0x4<<13) | (0x5<<9) | (0 & 0x1ff) 
//    app_echo.strong = ECHO_STRONG;
    echo_ptr->sample_rate = (0x4<<13) | (0xb<<9) | (0 & 0x1ff);
	switch (work_mode)
	{
	case REC_MIC_MODE:
    case MUSIC_MODE:
		app_echo_set(DAC_MUSIC, ECHO_MIC_GAIN);
		break;
#if FM_MODULE 
	case FM_RADIO_MODE:
#endif	
    case AUX_MODE:		
		app_echo_set(DAC_AMUX0, 7);
		break;
	
	default:
		break;
	}
    
    set_echo(app_echo.strong, app_echo.deep);
    echo_vol_set(ECHO_MIC_VOL);
    
}
/*----------------------------------------------------------------------------*/
/**@brief   各个模式下混响功能开关函数
   @param   void
   @return  void
   @note    void echo_sw(void)
*/
/*----------------------------------------------------------------------------*/
void echo_sw(void)
{

    if ((music_type != IS_MP3)&&(MUSIC_MODE == work_mode))
    {
        return;
    }
#if USB_DEVICE_ENABLE	 
	if (USB_DEVICE_MODE == work_mode)
		return;
#endif

	if(IDLE == echo_ptr->status)
	{
		sys_clk_div(1);
        echo_enable();
	}
	else
	{
		close_echo();
		if (
#if FM_MODULE 
        (work_mode == FM_RADIO_MODE) ||
#endif
        (work_mode == AUX_MODE))
		{
			sys_clk_div(4);
		}
	
	}
}


/*----------------------------------------------------------------------------*/
/**@brief   混响深度控制
   @param   ctl： '+' :混响深度++;'-'混响深度--;
   @return  改变之后的混响深度
   @note    u8 echo_deep(u8 ctl)
*/
/*----------------------------------------------------------------------------*/
bool echo_deep(u8 ctl)
{ 
    if( (BUSY == echo_ptr->status) || 
        ( BUSY == encode_msg->echo )
       )
    {
        if(MSG_REV_DEEP_UP == ctl)
        {
            app_echo.deep += 2;
        }
        if(app_echo.deep)
        {
            app_echo.deep--;
        }
        if (app_echo.deep > MAX_REV_DEEP)
        {
            app_echo.deep = MAX_REV_DEEP;
        }
        set_echo(app_echo.strong, app_echo.deep);//
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/**@brief   混响强度控制
   @param   ctl： '+' :混响强度++;'-'混响强度--;
   @return  改变之后的混响强度
   @note    u8 echo_strong(u8 ctl)
*/
/*----------------------------------------------------------------------------*/
bool echo_strong(u8 ctl)
{
    if( (BUSY == echo_ptr->status) || 
        ( BUSY == encode_msg->echo )
       )
    {
        if(MSG_REV_STRONG_UP == ctl)
        {
            app_echo.strong += 2;
        }
        if(app_echo.strong)
        {
            app_echo.strong--;
        }
        if (app_echo.strong > MAX_REV_STRONG)
        {
            app_echo.strong = MAX_REV_STRONG;
        }
        set_echo(app_echo.strong, app_echo.deep);
        return 1;
    }
    return 0;
}



