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
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata decode_buffer[];
extern u8 eq_mode;
extern bool vol_change_en;



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

    while (1)
    {
        //
#if ECHO_ENABLE            ///录音+混响时候将混响的部分与DAC_AMUC部分的声音一起输出
        dac_out_select(DAC_AMUX0 | ADD_DEC, 0);  
#else
        dac_out_select(DAC_AMUX0, 0);  
#endif
        key = app_get_msg();
        
        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            work_mode = MUSIC_MODE;
            return;

        case MSG_HALF_SECOND:
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

		bmt_hdlr();			 

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

//            if(MENU_RECWORKING == cur_menu)
//            {
//              // disp_rec_working();   
//			   disp_port(MENU_RECWORKING); 
//            }
            break;
#if RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif

#if KALAOK_FUNCTION
//		case MSG_KALAOK:
//			work_mode = REC_MIC_MODE;
//			return ;
#endif
        default:
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

//	amp_abd(1);
    //work_mode++;
    //return ;
    flashled(LED_ON);

    input_number_en = 0;
    vol_change_en=1;
    main_menu = MENU_AUX;
    disp_port(MENU_AUX);
    amux_dsp_eq();
    
    sys_clk_div(4);//SYSTEM_CLK_DIV4();
   
    encode_channel = REC_LINEIN;
     
#if ECHO_ENABLE             ///<当在此模式打开录音时，使用MIC混响，并加入AMUX的声音
    encode_channel = REC_MIC;
    if (echo_ptr->status != BUSY)
#endif
    {
	    dsp_set_adc_con(0x01d0);  ///<卡拉OK负载
    }
	encode_vol = REC_AMUX_GAIN;
    key_table_sel(0);
    flush_all_msg();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量

    one_wire_ctrl_if(2);
    amp_mute(0);
	
    aux_main();

    amp_mute(1);
	
#if ECHO_ENABLE  ///<当混响打开的时候不能关闭MIC，也不要将主音量设置到0
    if (echo_ptr->status != BUSY)
#endif    
    {
        dsp_set_adc_con(0);         ///<卡拉OK负载关闭
        main_vol_set(0, CHANGE_VOL_NO_MEM);
    }
    break_encode();

    //while(1);
}
