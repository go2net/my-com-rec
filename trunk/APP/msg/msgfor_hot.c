/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT 消息处理模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "msgfor_hot.h"
#include "disp.h"
#include "main.h"
#include "device.h"
#include "eq.h"
#include "dac.h"
#include "rtc_api.h"

extern void disk_remove_deal_for_music(void);

extern xd_u8 work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en,hp_online,sys_pwr_off;

extern xd_u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u8 device_active;
u16 input_number;	 ///<输入的数字的实际值
bool vol_change_en;	 ///<音量修改允许位
extern u8 device_online;
bool sys_mute_flag=0;
xd_u8 key_100_flag=0;
#ifdef REC_PLAY_BREAK_POINT
xd_u8 rec_pley_bp_flag=0;
xd_u16 last_play_index=0;
#endif

#ifdef USE_LINE_IN_DETECT_FUNC
extern bool aux_online;					///<AUX在线状态
#endif

/*----------------------------------------------------------------------------*/
/**@brief   几个任务都会用到的消息集中处理的函数
   @param   key： 需要处理的消息
   @return  0：需要切换工作模式;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key)
{
    u8 res;
    switch (key)
    {
#if defined(K000_LYXD_00000_REC_V001)  
    case MSG_CUSTOM_KEY:
		
		if(hp_online){

		        if (AUX_MODE != work_mode)	
        		 {
 				last_work_mode = work_mode;
            			work_mode = AUX_MODE;
            			put_msg_lifo(MSG_CHANGE_WORK_MODE);
        		 
			 	P1DIR &= ~(BIT(7)); P1PU |= BIT(7);
			 	P17 = 1;
		        }
			else {

				if(work_mode == AUX_MODE){
					work_mode =  last_work_mode;
			        	put_msg_lifo(MSG_CHANGE_WORK_MODE);
					P1DIR &= ~(BIT(7)); P1PU |= BIT(7);				
					P17 = 0;				
				}
			}
		}

		break;
#endif

#ifdef MICPHONE_GPIO_DETECTION
    case MSG_MIC_OUT:
#ifdef MUTE_AMP_IN_IDLE_MODE
		if(work_mode == IDLE_MODE){
			ext_amp_mute(EXT_AMP_MUTE);
		}
#else
		if(work_mode == IDLE_MODE){
			work_mode =  last_work_mode;
			put_msg_lifo(MSG_CHANGE_WORK_MODE);
		}			
#endif		
		break;

    case MSG_MIC_IN:
#ifdef MUTE_AMP_IN_IDLE_MODE
		if(work_mode == IDLE_MODE){
			ext_amp_mute(EXT_AMP_UNMUTE);
		}
#else
		if(work_mode != IDLE_MODE){
			last_work_mode = work_mode;
			work_mode = IDLE_MODE;
			put_msg_lifo(MSG_CHANGE_WORK_MODE);
		}
#endif		
		break;
#endif

#ifdef  USE_HPHONE_DETECT
    case MSG_HP_OUT:
		ext_amp_mute(EXT_AMP_UNMUTE);
		break;
    case MSG_HP_IN:
		ext_amp_mute(EXT_AMP_MUTE);
		break;
#endif

    case MSG_POWER_DOWN:
		sys_pwr_off = 1;
		work_mode =  IDLE_MODE;
        	put_msg_lifo(MSG_CHANGE_WORK_MODE);
		//sys_mute_flag =1;
        	//dac_mute_control(sys_mute_flag,1);					//调节音量时，自动UNMUTE
		break;
		
    case MSG_MUTE_UNMUTE:
		sys_mute_flag=~sys_mute_flag;
        	dac_mute_control(sys_mute_flag,1);					//调节音量时，自动UNMUTE
		break;		
		
    case MSG_USB_DISK_OUT:
    case MSG_SDMMC_OUT:

        set_brightness_all_on();
        if(!device_check() && (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }

	    if(MUSIC_MODE != work_mode)
			break;
        put_msg_lifo(MSG_DEVICE_REMOVED);
        disk_remove_deal_for_music();
        break;

#if USB_DEVICE_ENABLE
    case MSG_USB_PC_IN:
        break_encode();
        set_brightness_all_on();
        device_check();
        work_mode = USB_DEVICE_MODE;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_USB_PC_OUT:
        set_brightness_all_on();
        break;
#endif

#ifndef NOT_USE_LINE_IN_FUNC
    case MSG_AUX_IN :
        break_encode();
        set_brightness_all_on();
#if USB_DEVICE_ENABLE
        if ((AUX_MODE != work_mode) && (work_mode != USB_DEVICE_MODE))
#else
        if (AUX_MODE != work_mode)
#endif
        {
            last_work_mode = work_mode;
            work_mode = AUX_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
        }
        break;

    case MSG_AUX_OUT :
	 if(AUX_MODE == work_mode){

		 work_mode =last_work_mode;

		  if(work_mode == IDLE_MODE){
	 	          put_msg_lifo(MSG_NO_DEVICE);
		  }
	         put_msg_lifo(MSG_CHANGE_WORK_MODE);
	 }
        set_brightness_all_on();
        break;
#endif
    case MSG_SDMMC_IN :
        set_brightness_all_on();
		device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
            break;
        } 
        
        break_encode();

#if USB_DEVICE_ENABLE
        if (work_mode == USB_DEVICE_MODE)
            break;
#endif

		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_SDMMC0_REC)
			given_device = DEVICE_SDMMC0_REC;
		else
			given_device = DEVICE_SDMMC0;

        given_file_method = PLAY_BREAK_POINT;
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_USB_DISK_IN  :
        set_brightness_all_on();
		device_check();
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {
            break;
        }
        break_encode();
       
		given_device = read_info(MEM_ACTIVE_DEV);

		if(given_device == DEVICE_UDISK_REC)
			given_device = DEVICE_UDISK_REC;
		else
	    	given_device = DEVICE_UDISK;

        given_file_method = PLAY_BREAK_POINT;      
        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        break;

    case MSG_NEXT_WORKMODE:
		
        break_encode();

	 if(work_mode == MUSIC_MODE){

		device_check();
			
	    	if(((device_active &(~VIRTUAL_DEVICE))== DEVICE_UDISK)&&(device_online&DEVICE_SDMMC0)>0){

		    	given_device = DEVICE_SDMMC0;
		       given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		        	//put_msg_lifo(MSG_CHANGE_WORK_MODE);	
			break;
		}
	 }
	
        work_mode++;
		

	if(work_mode > MAX_WORK_MODE){
		
            work_mode = MUSIC_MODE;

		if(get_device_online_status()&DEVICE_UDISK){
			
	    		given_device = DEVICE_UDISK;
		        given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		}
		else if(get_device_online_status()&DEVICE_SDMMC0){
			
	    		given_device = DEVICE_SDMMC0;
		        given_file_method = PLAY_BREAK_POINT;      
		        put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		}
		else{
        		work_mode++;
		}
	}

#ifdef USE_MANUAL_IDLE_FUNC
	if(work_mode == IDLE_MODE){
		 put_msg_fifo(MSG_NO_DEVICE);
	}
	
#endif
        put_msg_lifo(MSG_CHANGE_WORK_MODE);

        break;

    case MSG_VOL_UP:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_INC));
        disp_port(MENU_MAIN_VOL);
        break;

    case MSG_VOL_DOWN:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//调节音量时，自动UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_DEC));
        disp_port(MENU_MAIN_VOL);
        break;

    case MSG_0:
    case MSG_1:
    case MSG_2:
    case MSG_3:
    case MSG_4:
    case MSG_5:
    case MSG_6:
    case MSG_7:
    case MSG_8:
    case MSG_9:
        if (!input_number_en)
            break;

	     if(key_100_flag ==0xFF){
			input_number += key;
			key_100_flag = 0xFE;
	     }
	     else if(key_100_flag ==0xFE){
		 	
			input_number += (input_number%10)*10-(input_number%10)+key;
			key_100_flag = 0x00;
	     }
	     else 
	     {
	     	     	if((input_number)>6553){
				input_number = 0x0000;			
			}
        		input_number = input_number * 10 + key;
			key_100_flag = 0x00;			
	     }
#if 1
	     if (input_number > 9999)
	     {
		       input_number = 0;			
			input_number = input_number *10 + key;
	    }
#endif
		
        disp_port(MENU_INPUT_NUMBER);
        break;
		
    case MSG_100:
#ifdef USE_10_PLUS_FUNC		
    case MSG_A:
#endif		
        if (!input_number_en)
            break;

	if (input_number > 999)
            input_number = 0;

	      key_100_flag = 0xFF;
#ifdef USE_10_PLUS_FUNC				  
	     input_number = input_number+10;
#else
	     input_number = input_number+100;
#endif
        disp_port(MENU_INPUT_NUMBER);
	break;		
#ifndef NO_ENCODE_FUNC		
//2  REC FSM BEGIN
    case MSG_REC_KEY:	  //录音开始和结束

#ifdef  MICPHONE_REC_ONLY
	 encode_channel = REC_MIC;
#endif

        if(RECODE_PLAY >= encode_status)
        {
	    if((get_device_online_status()&0x03)==0) {
			break;
		}
            put_msg_lifo(MSG_REC_FIND);
#if defined(INDEPENDENT_REC_LED)
    	     flashled(LED_OFF);			
	     rec_flash_led(LED_SPARK_FAST);
#else
    	     flashled(LED_SPARK_FAST);			
#endif
        }
        else
        {
            put_msg_lifo(MSG_REC_STOP);
#if defined(INDEPENDENT_REC_LED)
	     rec_flash_led(LED_OFF);
#elif defined(PLAY_STATUS_SPARK_WHEN_RECORDING)
    	 flashled(LED_SPARK_FAST);	
#else
    	     flashled(LED_ON);						
#endif
        }
        break;

	case MSG_MUSIC_PP:      //录音暂停和继续录音
	case MSG_REC_PP:      //录音暂停和继续录音

        if(RECODE_WORKING == encode_status)
        {
            put_msg_lifo(MSG_REC_PAUSE);
#if defined(INDEPENDENT_REC_LED)
	     rec_flash_led(LED_ON);
#else			
    	     flashled(LED_ON);						
#endif
        }
        else if(RECODE_PAUSE == encode_status)
        {

            put_msg_lifo(MSG_REC_CONTINUE);
#if defined(INDEPENDENT_REC_LED)
	     rec_flash_led(LED_SPARK_FAST);
#else			
    	     flashled(LED_SPARK_FAST);			
#endif
        }
        break;

    case MSG_ENCODE_END:

        api_stop_encode();		//停止录音
#if defined(INDEPENDENT_REC_LED)
	 rec_flash_led(LED_ON);
#else        
    	 flashled(LED_ON);			
#endif

        if(!device_check() && (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
        break_encode();
#ifndef NOT_USE_LINE_IN_FUNC		
        if(AUX_MODE == work_mode)
        {
            main_menu = MENU_AUX;
        }
#endif		
        disp_port(main_menu);
        break;
////////////////录音涉及的各种状态
    case MSG_REC_FIND:
//        if(RECODE_PLAY >= encode_status)
//        {
//            break;
//        }
#if USB_DEVICE_ENABLE
        if(USB_DEVICE_MODE == work_mode)
        {
            break;
        }
#endif
        encode_status = RECODE_INIT;
        if(MUSIC_MODE == work_mode)
        {
            encode_device = device_active;	 //设置录音存储设备
            work_mode = REC_MIC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
        }
	 else if(REC_MIC_MODE == work_mode){
	 	
		given_device = encode_device;
		
	 }
        else //if((MUSIC_MODE != work_mode))
        {
            if (given_device == NO_DEVICE)
            {
                given_device = read_info(MEM_ACTIVE_DEV);
            }
        }
        if(((given_device & (~VIRTUAL_DEVICE))  != DEVICE_SDMMC0) && ((given_device & (~VIRTUAL_DEVICE)) != DEVICE_UDISK))
        {
            given_device = DEVICE_SDMMC0;
        }
        SYSTEM_CLK_DIV2();

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        break;
    case MSG_REC_START:		//开始录音
    
#ifdef REC_GPIO_CTRL
    	REC_GPIO_CTRL_INIT();
	REC_GPIO_HIGH();
#endif

#if defined(INDEPENDENT_REC_LED)
    	     flashled(LED_OFF);			
	     rec_flash_led(LED_SPARK_FAST);
#elif defined(PLAY_STATUS_SPARK_WHEN_RECORDING)
    	 flashled(LED_SPARK_FAST);	
#endif
       //init_rec_name();
        device_active |= VIRTUAL_DEVICE;
        encode_device = device_active;	 //设置录音存储设备
        write_file_info(0);
        SYSTEM_CLK_DIV2();

        set_rec_channel(encode_channel); //设置录音通道
        set_rec_vol(encode_vol);		 //设置录音音量
        if(REC_MIC == encode_channel)
        {
            set_rec_track(TRACK_LEFT);
        }
        else
        {
            set_rec_track(TRACK_ALL);
        }
        /**/
		
        CLKGAT |= MP3CLK;// | SPIURCLK;
        CLKCON0 |= DACCLK;
        if(DEVICE_SDMMC0 == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= USBCLK;
        }
        else if(DEVICE_UDISK == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= SDCLK;
        }
        start_encode(IS_MP3);			 //开始录音
        /*
        if(REC_MIC_MODE == work_mode)
        {
    		while(!((cmd_ctl_rec(REC_NO_OPT,0)) &  FRIST_ADC_PACKET)) //采数据前的处理
    		{
    
    		}
            delay_10ms(50);//抛弃半秒的数据
        }
		cmd_ctl_rec(ENABLE_REC_DATA,ENABLE_REC_BIT);
        */
        encode_status = RECODE_WORKING;
#if FM_MODULE 
	//	if(FM_RADIO_MODE != work_mode)
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		}
		disp_port(main_menu);
        //disp_port(MENU_REC);
        break;
    case MSG_REC_STOP:      //停止录音
        api_stop_encode();		//停止录音
        put_msg_lifo(MSG_REC_PLAY);
#ifdef REC_PLAY_BREAK_POINT
	rec_pley_bp_flag=0;
#endif
        break;
		
    case MSG_REC_PAUSE:     //暂停录音
		encode_status = RECODE_PAUSE;
	
#if FM_MODULE 
#ifndef DISP_REC_TIME_PAUSE
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif			
#endif
		{
			main_menu = MENU_REC_PAUSE;	
		  	disp_port(MENU_REC_PAUSE);
		}
		 		
        pause_encode();
        break;
    case MSG_REC_CONTINUE:  //暂停录音之后继续录音
		encode_status = RECODE_WORKING;
	
#if FM_MODULE 
#ifndef DISP_REC_TIME_PAUSE
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif			
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		    disp_port(MENU_RECWORKING);
		}
			
        continue_encode();
        break;
    case MSG_REC_PLAY:     //播放最后的录音文件

	    if((get_device_online_status()&0x03)==0) {
			break;
		}	
	if(((encode_filenum)==0)&&(encode_status == RECODE_STOP)&&(work_mode!=REC_MIC_MODE))break;
	
#ifdef REC_PLAY_BREAK_POINT
//        if(AUX_MODE == work_mode)break;
	if(rec_pley_bp_flag==0x00){

		rec_pley_bp_flag =0x01;
	       // device_active |=VIRTUAL_DEVICE;

		//if(device_active&VIRTUAL_DEVICE){
		//	rec_pley_bp_flag =0x81;
		//}

		last_play_index =  given_file_number;
	}
	else if(rec_pley_bp_flag ==0x01){
		
		//if(rec_pley_bp_flag&0x80>0){			
	       //       device_active |=VIRTUAL_DEVICE;
		//}
		//else{
	              device_active &=~VIRTUAL_DEVICE;
		//}

		rec_pley_bp_flag =0x00;
		
		given_file_number=last_play_index;
              put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
		break;
	}
	else if(rec_pley_bp_flag ==0xFF){
		rec_pley_bp_flag =0;
	}
#endif
        if(RECODE_PLAY < encode_status){
			
            	put_msg_lifo(MSG_REC_STOP);
#if defined(INDEPENDENT_REC_LED)
	       rec_flash_led(LED_OFF);
#else				
    	       flashled(LED_ON);
#endif
	       break;
    	 }
        encode_status = RECODE_PLAY;
        //given_device = encode_device&(~VIRTUAL_DEVICE);

        if( ((given_device& (~VIRTUAL_DEVICE)) != DEVICE_SDMMC0) && ((given_device& (~VIRTUAL_DEVICE)) != DEVICE_UDISK))
        {
            //given_device = DEVICE_SDMMC0;
        }
        //given_device |= VIRTUAL_DEVICE;
        if((MUSIC_MODE != work_mode))
        {
            put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        }
        else
        {
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        }
        break;
#endif

    case MSG_MUSIC_SELECT_NEW_DEVICE:					        //重新选择设备

        res = find_device(given_device);

        if ((res == DEV_INIT_ERR) ||
                (res == NO_DEFINE_DEV))                    //指定的设备不在线，或初始化失败
        {
		
            given_device = DEVICE_AUTO_NEXT;			   //自动选择下一个设备
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
        }
        else if ((res == NO_EFFECTIVE_DEV) ||
                 (res == NO_DEV_ONLINE))                    //无可播放的设备
        {	

#if defined(INDEPENDENT_REC_LED)
    	     rec_flash_led(LED_OFF);			
#else
            flashled(LED_ON);			
#endif
            if(RECODE_STOP != encode_status)
            {
                encode_status = RECODE_STOP;
				if(REC_MIC_MODE == work_mode)
			 	{
					put_msg_lifo(MSG_NEXT_WORKMODE);
				}
                break;
            }
            else
            {	
#ifdef DEFAULT_GOTO_IDLE
		  work_mode =IDLE_MODE;
		  disp_port(MENU_NODEVICE);
                put_msg_lifo(MSG_CHANGE_WORK_MODE);
#elif defined(DEFAULT_GOTO_AUX)
		  work_mode =AUX_MODE;
                put_msg_lifo(MSG_CHANGE_WORK_MODE);

#else
                put_msg_lifo(MSG_NEXT_WORKMODE);
#endif
            }
            break;
        }
        else
        {		
            if(RECODE_PLAY < encode_status)
            {
                put_msg_lifo(MSG_REC_START);
            }
            else
            {
                if(RECODE_PLAY == encode_status)  //4去播刚录好的文件
                {
                	device_active |=VIRTUAL_DEVICE;	
                    encode_status = RECODE_STOP;
                    //device_active |=VIRTUAL_DEVICE;					
			//printf_u16(logic_fileTotal,'L');
			//printf_u16(encode_filenum,'E');
			//printf_u16(encode_fristfile,'F');
#if VIRTUAL_ENABLE
#ifdef CUSTOM_DEFINED_FOLDER
                    given_file_number = logic_fileTotal;
#else
                    given_file_number = encode_filenum;
#endif
#else
                    given_file_number = encode_filenum + encode_fristfile - 1;
#endif
#if 0
		printf_u16(logic_fileTotal,'L');
		printf_u16(encode_fristfile,'A');
		printf_u16(encode_filenum,'N');
		deg_str("MSG_MUSIC_PLAY_NEW_FILE on\n");
#endif
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                {
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//找到可用设备
                }
            }
        }
        break;
//2  REC FSM END

    }
}
