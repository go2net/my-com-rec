/*--------------------------------------------------------------------------*/
/**@file    fm_receive.c
   @brief   FM接收任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "aux_fun.h"
#include "dac.h"
#include "clock.h"
#include "rtc_api.h"
#include "eq.h"

extern bool input_number_en;
extern u8  main_menu, cur_menu, main_menu_conter ;
extern u16 input_number;
extern xd_u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata decode_buffer[];
extern u8 eq_mode;
extern bool vol_change_en;
extern u8 play_status;							///<播放状态
#ifdef USE_LINE_IN_DETECT_FUNC
extern bool aux_online;		
#endif

#ifdef EXTENDED_AUX_FUNC
xd_u8 extended_aux_sel=0,aux_sel=0;
void extended_aux_select()
{

	EXTENDED_AUX_FUNC_GPIO_INIT();
	if(extended_aux_sel==0){
		
		EXTENDED_AUX_FUNC_CH0();
		return;
	}
	else if(extended_aux_sel==1){
		EXTENDED_AUX_FUNC_CH1();

	}
	else if(extended_aux_sel==2){
		EXTENDED_AUX_FUNC_CH2();

	}
	else if(extended_aux_sel==3){
		EXTENDED_AUX_FUNC_CH3();
	}	

	disp_port(MENU_AUX);

}
#endif

/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式主循环
   @param   无
   @return  无
   @note    void aux_main(void)
*/
/*----------------------------------------------------------------------------*/
void aux_main(void)
{
    u8 key;
	
    ext_amp_mute(EXT_AMP_UNMUTE);	

    while (1)
    {
#if defined(EXCHANGE_AUX_CHANNEL)
        dac_out_select(DAC_AMUX0, 0);
#else
        dac_out_select(DAC_AMUX1, 0);
#endif
        key = app_get_msg();

        switch (key)
        {
#ifdef AUX_USE_PP_KEY_FOR_MUTE        
	 case MSG_MUSIC_PP:	 	 	
            if (play_status == MAD_PLAY){
			dac_mute_control(1,1);
			play_status = MAD_PAUSE;
	    }
	    else if(play_status == MAD_PAUSE){
			dac_mute_control(0,1);
			play_status = MAD_PLAY;
	    }
		break;
#endif		

#ifdef EXTENDED_AUX_FUNC
    case MSG_NEXT_WORKMODE:
	extended_aux_sel++;
	
	if(extended_aux_sel>3){
		goto __HOT_KEY_HDLR;
	}
	extended_aux_select();

	break;
#endif
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            work_mode = MUSIC_MODE;
            return;

        case MSG_HALF_SECOND:

#if defined(USE_BAT_MANAGEMENT)
		bmt_hdlr();
#endif			
////////////////////////////////////////////////////////////
//显示界面的切换
#if  1
//            if(RECODE_WORKING == encode_status)
//            {
//                main_menu = MENU_RECWORKING;
//            }
//			else if(RECODE_PAUSE == encode_status)
//			{				
//				main_menu = MENU_REC_PAUSE;
//			}
//            else
//            {
//                main_menu = MENU_AUX;
//            }
			if(cur_menu == main_menu)
			{
			   disp_port(main_menu);
			}

            set_brightness_fade_out();
#endif 
            
            set_brightness_fade_out();
            if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                cur_menu = main_menu;
                disp_port(cur_menu);
            }

	     if(RECODE_WORKING == encode_status)
            {
                 //   cur_menu = MENU_RECWORKING;
		   disp_port(MENU_RECWORKING); 			
            }
//            if(MENU_RECWORKING == cur_menu)
//            {
//              // disp_rec_working();   
//			   disp_port(MENU_RECWORKING); 
//            }
            break;

#ifdef INDEPENDENT_AUX_VOL_KEY
        case MSG_MUSIC_FF:
        case MSG_MUSIC_NEXT_FILE:
            put_msg_lifo(MSG_VOL_UP);

		break;
        case MSG_MUSIC_FR:
        case MSG_MUSIC_PREV_FILE:
            put_msg_lifo(MSG_VOL_DOWN);
		break;
#endif
	
#if RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        default:
__HOT_KEY_HDLR:        
            ap_handle_hotkey(key);
            break;
        }
    }

}
/*----------------------------------------------------------------------------*/
/**@brief   Line IN模式入口
   @param   无
   @return  无
   @note    void aux_fun(void)
*/
/*----------------------------------------------------------------------------*/
void aux_fun(void)
{
    flashled(LED_ON);
#ifdef USE_LINE_IN_DETECT_FUNC	
   if(!aux_online){
   	
	work_mode = MUSIC_MODE;
#ifdef USE_MANUAL_IDLE_FUNC
	work_mode = IDLE_MODE;
		 put_msg_fifo(MSG_NO_DEVICE);
#endif
	
	return;
   }
#endif
#ifdef AUX_USE_PP_KEY_FOR_MUTE        
	play_status = MAD_PLAY;
#endif	

#ifdef EXTENDED_AUX_FUNC
	extended_aux_sel=1;
	extended_aux_select();
#endif

//	amp_abd(1);
    //work_mode++;
    //return ;
    input_number_en = 0;
    vol_change_en=1;
    main_menu = MENU_AUX;
    disp_port(MENU_AUX);
    amux_dsp_eq();
    SYSTEM_CLK_DIV4();
    encode_channel = REC_LINEIN;
    encode_vol = 3;
    key_table_sel(0);
    flush_all_msg();

    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量

    aux_main();
    main_vol_set(0, CHANGE_VOL_NO_MEM);

#ifdef EXTENDED_AUX_FUNC
	extended_aux_sel=0;
	extended_aux_select();
#endif

    break_encode();
}
