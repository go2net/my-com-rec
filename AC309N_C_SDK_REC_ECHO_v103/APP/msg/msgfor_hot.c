/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.c
   @brief   HOT ��Ϣ����ģ��
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
#include "echo.h"
extern void disk_remove_deal_for_music(void);

extern u8 work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern u8 device_active;
u16 input_number;	 ///<��������ֵ�ʵ��ֵ
bool vol_change_en;	 ///<�����޸�����λ
extern u8 device_online;
extern u8 music_type;
bool rec_device_out;
bool mic_plugged=0;
u8 key_100_flag=0;

#ifdef REC_PLAY_BREAK_POINT
xd_u8 rec_pley_bp_flag=0;
xd_u16 last_play_index=0;
#endif


/*----------------------------------------------------------------------------*/
/**@brief   �������񶼻��õ�����Ϣ���д���ĺ���
   @param   key�� ��Ҫ�������Ϣ
   @return  0����Ҫ�л�����ģʽ;
   @note    unsigned char I2C_sendbyte(unsigned char I2Cdata)
*/
/*----------------------------------------------------------------------------*/
void ap_handle_hotkey(u8 key)
{
    u8 res;

    switch (key)
    {

    case MSG_MIC_IN:
	if(work_mode != IDLE_MODE){

		last_work_mode = work_mode;
		work_mode =  IDLE_MODE;
		mic_plugged = 1;
	       put_msg_lifo(MSG_CHANGE_WORK_MODE);
	}
	break;

#if ECHO_ENABLE
    case MSG_REV_SW:
        echo_sw();		
        break;
    
	case MSG_REV_STRONG_UP:
	case MSG_REV_STRONG_DOWN:
        if(echo_strong(key))
        {
            disp_port(MENU_REV_STRONG);   
        }
        break;
	
     case MSG_REV_DEEP_UP:
     case MSG_REV_DEEP_DOWN:
        if(echo_deep(key))
        {
            disp_port(MENU_REV_DEEP);
        }
        break;
#endif
     case MSG_POWER_ON:
	 	work_mode= IDLE_MODE;
	       put_msg_lifo(MSG_CHANGE_WORK_MODE);
	 	break;
    case MSG_USB_DISK_OUT:
    case MSG_SDMMC_OUT:
        //deg_str("device out \n");
        set_brightness_all_on();
        if( (!device_check() ) && (encode_status >= RECODE_INIT )) //��¼��ʱ����豸�γ�
        {	
            rec_device_out = 1;
            api_stop_encode();
            if(AUX_MODE == work_mode)
	        {
	            main_menu = MENU_AUX;
				disp_port(MENU_AUX);
	        }
#if FM_MODULE 
			else if(FM_RADIO_MODE == work_mode)
	        {
	            main_menu = MENU_FM_MAIN;
                disp_port(MENU_FM_MAIN);
	        }
#endif
            else
            {
                 put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
                 //break;  
            }
		}
        /*
        if((!device_check()) && (REC_MIC_MODE == work_mode))
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
        */
	    if(MUSIC_MODE != work_mode)
			break;
        put_msg_lifo(MSG_DEVICE_REMOVED);
        disk_remove_deal_for_music();
        break;

#if USB_DEVICE_ENABLE
    case MSG_USB_PC_IN:

    #if ECHO_ENABLE
        if(BUSY == echo_ptr->status)
        {
            close_echo();
        }
    #endif
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
            work_mode = AUX_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
        }
        break;

    case MSG_AUX_OUT :
        set_brightness_all_on();

	 if(work_mode != AUX_MODE)break;
	 
        if((RECODE_WORKING == encode_status)||(RECODE_PAUSE == encode_status))
        {	
            break;
        } 

        break_encode();

	 given_device = DEVICE_UDISK;
        given_file_method = PLAY_BREAK_POINT;      
	 put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
		
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


            if(mic_plugged){	
		break;
		}			
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
		device_check();

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


        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        break;

    case MSG_VOL_UP:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//��������ʱ���Զ�UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_INC));
        disp_port(MENU_MAIN_VOL);
        break;

    case MSG_VOL_DOWN:
        if (vol_change_en==0)
            break;
        dac_mute_control(0,1);					//��������ʱ���Զ�UNMUTE
        write_info(MEM_VOL, main_vol_set(0, CHANGE_VOL_DEC));
        disp_port(MENU_MAIN_VOL);
        break;
		
    case MSG_100:
		
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
////////////////¼��
    case MSG_REC_KEY:	  //¼����ʼ�ͽ���
        if(RECODE_PLAY >= encode_status)
        {

	    if((get_device_online_status()&0x03)==0) {
			break;
	     }		

	     put_msg_lifo(MSG_REC_FIND);
    	    //if(BUSY == echo_ptr->status)
            {
    		    //close_echo();
            }

    	     flashled(LED_FAST);			
			
        }
        else
        {
            put_msg_lifo(MSG_REC_STOP);
    	     flashled(LED_ON);						
        }
        break;

	case MSG_REC_PP:      //¼����ͣ�ͼ���¼��

        if(RECODE_WORKING == encode_status)
        {
            put_msg_lifo(MSG_REC_PAUSE);
        }
        else if(RECODE_PAUSE == encode_status)
        {

            put_msg_lifo(MSG_REC_CONTINUE);
        }
        break;

    case MSG_ENCODE_END:   //�豸дerr  �� �豸��
	//	deg_str("MSG_ENCODE_END \n");
    	     flashled(LED_ON);						

		if(rec_device_out)		//¼��ʱ��豸�γ�,���豸�γ����ﴦ���ڴ˲�������
		{
			rec_device_out =0;
			break;
		}

        api_stop_encode();		//ֹͣ¼��
		put_msg_lifo(MSG_REC_PLAY);
		break;

	 case MSG_ENCODE_FAT_FULL:  //���ļ�ʱ
	 //	deg_str("MSG_ENCODE_FAT_FULL \n");
		api_stop_encode();		//ֹͣ¼��
		if(REC_MIC_MODE == work_mode)		//¼��ʱд�豸�������⡢�豸��
        {
             put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
             break;   
        }
#ifndef NOT_USE_LINE_IN_FUNC		
        if(AUX_MODE == work_mode)
        {
            main_menu = MENU_AUX;
        }
#endif		
#if FM_MODULE 
		else if(FM_RADIO_MODE == work_mode)
        {
            main_menu = MENU_FM_MAIN;
        }
#endif
        disp_port(main_menu);
        break;
////////////////¼���漰�ĸ���״̬
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
            work_mode = REC_MIC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            given_device = read_info(MEM_ACTIVE_DEV);

            break;
        }
        else //if((MUSIC_MODE != work_mode))
        {
            if (given_device == NO_DEVICE)
            {
                
                given_device = read_info(MEM_ACTIVE_DEV);

            }
        }      
        if( (( given_device & (~VIRTUAL_DEVICE ))  != DEVICE_SDMMC0) 
            && ((given_device & (~VIRTUAL_DEVICE)) != DEVICE_UDISK)
          )
        {
            given_device = DEVICE_SDMMC0;
        }
        sys_clk_div(2);//SYSTEM_CLK_DIV2();

        put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        break;
    case MSG_REC_START:		//��ʼ¼��

		rec_device_out = 0;

    	     flashled(LED_FAST);			

#if 0
		 rec_sys_set(0);  //0:24M   1:48M
		 sys_clk_div(2);//SYSTEM_CLK_DIV2();  //24 M
#else
		 rec_sys_set(1);
		 sys_clk_div(1);//SYSTEM_CLK_DIV1();	  //48 M

#endif
        //init_rec_name();

               
        device_active |= VIRTUAL_DEVICE;
        encode_device = device_active;	 //����¼���洢�豸

        write_file_info(0);

        set_rec_channel(encode_channel); //����¼��ͨ��  

        set_rec_vol(encode_vol);		 //����¼������

		

		if(REC_MIC_MODE == work_mode)
		{	
			kala_dac_off();
//			dac_mute_control(1,1);
#if KALAOK_FUNCTION
			dsp_set_adc_con(0);
			P3HD &=~(1<<6);
#endif
		}

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

		
 //     CLKCON0 |= DACCLK;
 //		P3HD &=~(1<<6);
	   
        if(DEVICE_SDMMC0 == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= USBCLK;
        }
        else if(DEVICE_UDISK == (device_active & (~VIRTUAL_DEVICE)))
        {
            CLKGAT |= SDCLK;
        }
#if ECHO_ENABLE
        if(BUSY == echo_ptr->status)
        {
            close_echo();
        }
#endif
        ///0x
        //my_memset(0x4000,0,0x787f-0x4000);
        //my_memset(0x8000,0,0x9c3f-0x8000);

//����ǿ�� 0x400c ȡֵ��Χ 0-255
//������� 0x4015 0x4014   ȡֵ��Χ 0-2048

#if ECHO_ENABLE      
        if(1 != start_encode_echo(IS_MP3))			 //��ʼ¼��
#else
        if(1 != start_encode(IS_MP3))			 //��ʼ¼��
#endif
        {
            //deg_str("start err\n");
			put_msg_lifo(MSG_ENCODE_FAT_FULL);
			break;
		}
#if ECHO_ENABLE  ///<������������򿪻�����Ⱥ�ǿ��
        delay_10ms(20);
        if( REC_MIC == ( encode_channel & 0xf ) ) ///<MIC ���л���
        {
            set_echo(app_echo.strong, app_echo.deep);
        }
//        app_echo.strong = REC_ECHO_STRONG;
        echo_vol_set(REC_MIC_VOL);

#endif

        /*
        if(REC_MIC_MODE == work_mode)
        {
    		while(!((cmd_ctl_rec(REC_NO_OPT,0)) &  FRIST_ADC_PACKET)) //������ǰ�Ĵ���
    		{
    
    		}
            delay_10ms(50);//�������������
        }
		cmd_ctl_rec(ENABLE_REC_DATA,ENABLE_REC_BIT);
        */
        encode_status = RECODE_WORKING;
#if 0//FM_MODULE 
		if(FM_RADIO_MODE != work_mode)
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		}
		disp_port(main_menu);
        //disp_port(MENU_REC);
        break;
    case MSG_REC_STOP:      //ֹͣ¼��

#ifdef REC_PLAY_BREAK_POINT
	rec_pley_bp_flag=0;
#endif
      	 flashled(LED_ON);						

        api_stop_encode();		//ֹͣ¼��
        put_msg_lifo(MSG_REC_PLAY);
        break;
    case MSG_REC_PAUSE:     //��ͣ¼��
		encode_status = RECODE_PAUSE;
	
#if  0//FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
			main_menu = MENU_REC_PAUSE;	
		  	disp_port(MENU_REC_PAUSE);
		}
		 		
        pause_encode();
        break;
    case MSG_REC_CONTINUE:  //��ͣ¼��֮�����¼��
		encode_status = RECODE_WORKING;
	
#if FM_MODULE 
		if(FM_RADIO_MODE == work_mode)
			disp_port(MENU_FM_MAIN);
		else
#endif
		{
		 	main_menu = MENU_RECWORKING;//
		    disp_port(MENU_RECWORKING);
		}
			
        continue_encode();
        break;
    case MSG_REC_PLAY:     //��������¼���ļ�


#ifdef REC_PLAY_BREAK_POINT
	if(((encode_filenum)==0)&&(encode_status == RECODE_STOP)&&(work_mode!=REC_MIC_MODE))break;

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

        encode_status = RECODE_PLAY;
        given_device = encode_device & (~VIRTUAL_DEVICE);

        if( (given_device != DEVICE_SDMMC0) && (given_device != DEVICE_UDISK))
        {
            given_device = DEVICE_SDMMC0;
        }
        given_device |= VIRTUAL_DEVICE;
        if((MUSIC_MODE != work_mode))
        {
            put_msg_lifo(MSG_MUSIC_NEW_DEVICE_IN);
        }
        else
        {
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
        }
        break;

    case MSG_MUSIC_SELECT_NEW_DEVICE:					        //����ѡ���豸

        res = find_device(given_device);

        if ((res == DEV_INIT_ERR) ||
                (res == NO_DEFINE_DEV))                    //ָ�����豸�����ߣ����ʼ��ʧ��
        {
		
            given_device = DEVICE_AUTO_NEXT;			   //�Զ�ѡ����һ���豸
            put_msg_lifo(MSG_MUSIC_SELECT_NEW_DEVICE);
            break;
        }
        else if ((res == NO_EFFECTIVE_DEV) ||
                 (res == NO_DEV_ONLINE))                    //�޿ɲ��ŵ��豸
        {		
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
                put_msg_lifo(MSG_NEXT_WORKMODE);
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
                if(RECODE_PLAY == encode_status)  //ȥ����¼�õ��ļ�
                {
                    encode_status = RECODE_STOP;
#if VIRTUAL_ENABLE
                    given_file_number = encode_filenum;
#else
                    given_file_number = encode_filenum + encode_fristfile - 1;
#endif
                    put_msg_lifo(MSG_MUSIC_PLAY_NEW_FILE);
                }
                else
                {
                    put_msg_lifo(MSG_MUSIC_SELECT_NEW_FILE);		//�ҵ������豸
                }
            }
            
        }
        break;



    }
}
