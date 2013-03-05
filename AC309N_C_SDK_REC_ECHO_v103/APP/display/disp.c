/*--------------------------------------------------------------------------*/
/**@file   DISP.C
   @brief    显示模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "disp.h"
#include "uart.h"
#if (monitor != NO_DISP)


#include "lcd.h"
#include "led.h"
#include "resource.h"
#include "my_printf.h"
#include "lcd.h"
#include "led.h"
#include "device.h"
#include "dac.h"
#include "rtc_mode.h"

extern u8 LCDPAGE,LCDCOLUMN;
#if FM_MODULE
extern u16 frequency;
extern u8 fre_channel, total_channel;
#endif
extern u16 input_number;
extern u8 _bdata device_online;

extern u16 given_file_number;
extern u8 device_active;
extern u8 eq_mode;
extern u8 play_mode;
extern u8 music_type;
extern DECODER_MSG _xdata *dec_msg;
extern FSAPIMSG _pdata fs_msg;
extern _xdata u8 LCDBuff[8][132];
extern u8 _xdata rtc_coordinate;
extern u8 _xdata alm_coordinate;
extern u8 _code rtc_coordinate_tab[][3];
extern u8 _code alm_coordinate_tab[][3];
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _code alm_request_tab[][3];
extern u8 _xdata alm_request_cnt;

extern u8  main_menu;			///<记录各种不同模式下的主界面
extern u8  cur_menu;        	///<当前界面
extern u8  main_menu_conter;	///<离开主界面的时间
extern bool flash_en;			///<显示闪动允许
extern u8 bright_counter;		///<显示亮度调整延时
extern u8 play_status;	



u8 _code play_mode_const [5][5] = 
{
    {" ALL"},
    {" FOL"},
    {" ONE"},
    {" RAN"},
    {" bAc"}
};

/*----------------------------------------------------------------------------*/
/**@brief  显示在线和闪烁活动设备符号
   @param  无
   @return 无
   @note   void disp_device(void)
*/
/*----------------------------------------------------------------------------*/
void disp_device(void)
{
	if (device_online & DEVICE_SDMMC0)
    {
		//led_disp_icon(LED0_SD);
    }
    if (device_online & DEVICE_UDISK)
    {
	  	//led_disp_icon(LED0_USB);
    }

	if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
	{
		led_disp_icon(LED0_SD);
	}
	else if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
	{
	    	led_disp_icon(LED0_USB);
	}	
}



//////////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------*/
/**@brief  设置亮度
   @param  无
   @return 无
   @note   void set_brightness(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness(u8 br)
{
   led_set_brightness(br);
}
/*----------------------------------------------------------------------------*/
/**@brief  设置亮度渐暗
   @param  无
   @return 无
   @note   void set_brightness_fade_out(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness_fade_out(void)
{
    if (bright_counter < 20)
    {
        bright_counter++;
        set_brightness(23 - bright_counter);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  设置亮度全亮
   @param  无
   @return 无
   @note   void set_brightness_all_on(void)
*/
/*----------------------------------------------------------------------------*/
void set_brightness_all_on(void)
{
    set_brightness(16);
    bright_counter = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief  显示初始化
   @param  无
   @return 无
   @note   void init_display(void)
*/
/*----------------------------------------------------------------------------*/
void init_display(void)
{
    init_led_disp();
    disp_power_on();
}


/////////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------*/
/**@brief  显示开机上电的界面
   @param  无
   @return 无
   @note   void disp_power_on(void)
*/
/*----------------------------------------------------------------------------*/
void disp_power_on(void)
{
    {
        printf_str("HI--",0);//my_printf("%X\x0HI--");
    }
}


/*----------------------------------------------------------------------------*/
/**@brief  显示关机界面
   @param  无
   @return 无
   @note   void disp_power_off(void)
*/
/*----------------------------------------------------------------------------*/
void disp_power_off(void)
{
    printf_str("OFF ",0);//my_printf("OFF ");
}

/*----------------------------------------------------------------------------*/
/**@brief  显示FM主界面
   @param  无
   @return 无
   @note   void disp_fm_main(void)
*/
/*----------------------------------------------------------------------------*/
void fm_rec_disp(void)
{
	if(RECODE_WORKING == encode_status)
    {	 
		 disp_device();
		led_disp_icon(LED0_PLAY);
	}
	else if(RECODE_PAUSE == encode_status)
	{
		disp_device();
	 	led_disp_icon(LED0_PAUSE);
	}
}

#if FM_MODULE
void disp_fm_main(void)
{
    if(frequency > 999)
    {
        printf_num(frequency,0,4);
    }
    else
    {
        printf_num(frequency,1,3);
    }

	fm_rec_disp();

	led_disp_icon(LED0_FM);

//	if(RECODE_WORKING == encode_status)
//    {
//        led_disp_icon(LED0_FM);
//    }
//    else if(RECODE_PAUSE == encode_status)
//    {
//        led_flash_icon(LED0_FM);
//    }
//	else
//	{
//	 	led_disp_icon(LED0_FM);
//	}
}
#endif


/*----------------------------------------------------------------------------*/
/**@brief  显示FM频点
   @param  无
   @return 无
   @note   void disp_fm_freq(void)
*/
/*----------------------------------------------------------------------------*/
#if FM_MODULE
void disp_fm_freq(void)
{
    disp_fm_main();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示搜索到的FM频道
   @param  无
   @return 无
   @note   void disp_fm_find_station(void)
*/
/*----------------------------------------------------------------------------*/
#if FM_MODULE
void disp_fm_find_station(void)
{
    led_putchar('P',1);
    printf_num(fre_channel,2,2);//my_printf("%c P%02b%m", fre_channel, LED_FM_ICON);
	fm_rec_disp();
    delay_10ms(50);


}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示FM频道
   @param  无
   @return 无
   @note   void disp_fm_channel(void)
*/
/*----------------------------------------------------------------------------*/
#if FM_MODULE
void disp_fm_channel(void)
{
    led_putchar('P',1);
    printf_num(fre_channel,2,2);
	fm_rec_disp();
}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示输入数字
   @param  num:数值
   @return 无
   @note   void disp_input_number(u16 num)
*/
/*----------------------------------------------------------------------------*/
void disp_input_number(u16 num)
{
    printf_num(num,0,4);      

}

/*----------------------------------------------------------------------------*/
/**@brief  显示主音量
   @param  vol:显示的音量值
   @return 无
   @note   void disp_main_vol(u8 vol)
*/
/*----------------------------------------------------------------------------*/
void disp_main_vol(u8 vol)
{
    led_putchar('U',0);
    printf_num(vol,2,2);

}
#if ECHO_ENABLE
void disp_rev_deep(void)
{

    printf_num(app_echo.deep,1,2);

}
void disp_rev_strong(void)
{
    //led_putchar('5',0);
    printf_num(app_echo.strong,1,3);

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief  显示音频播放时间，总时间
   @param  无
   @return 无
   @note   void disp_music_play_time(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_play_time(void)
{
    u16 play_time;
    u8 min,sec;

    play_time = dec_msg->play_time;
    min = play_time / 60;
    sec = play_time % 60;
#if(monitor == DISP_LED5X7)
    printf_num(sec,2,2);
    printf_num(min,0,2);
    led_putchar(':',0);
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  显示音频文体格式
   @param  无
   @return 无
   @note   void disp_music_format(voids)
*/
/*----------------------------------------------------------------------------*/
void disp_music_format(void)
{
    if (music_type == IS_WAV)
    {
    }
    else if (music_type == IS_WMA)
    {
    }
}
/*----------------------------------------------------------------------------*/
/**@brief  显示 MUSIC主界面
   @param  无
   @return 无
   @note   void diso_music_main(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_main(void)
{
    disp_music_play_time();
	led_disp_icon(LED0_PLAY);
	disp_device();
	led_disp_icon(LED0_MP3);

}
/*----------------------------------------------------------------------------*/
/**@brief  显示 EQ
   @param  无
   @return 无
   @note   void disp_eq(void)
*/
/*----------------------------------------------------------------------------*/
void disp_eq(void)
{
	printf_str("Eq",1);
    printf_num(eq_mode,3,1);
}
/*----------------------------------------------------------------------------*/
/**@brief  显示 播放模式
   @param  无
   @return 无
   @note   void disp_play_mode(void)
*/
/*----------------------------------------------------------------------------*/
void disp_play_mode(void)
{
#if VIRTUAL_ENABLE
    if(device_active & VIRTUAL_DEVICE)
    {
        printf_str(&play_mode_const[play_mode_rec][0],0);
    }
    else
#endif
    {
        printf_str(&play_mode_const[play_mode][0],0);            
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  刷新音乐显示主界面
   @param  无
   @return 无
   @note   无
*/
/*----------------------------------------------------------------------------*/
void disp_main_menu_refresh(void)
{

    if ((cur_menu == MENU_MUSIC_MAIN)||(cur_menu == MENU_REC_MAIN))
    {
        disp_music_main();
    }
    else if (main_menu == MENU_FM_MAIN)
    {
    }

}
/*----------------------------------------------------------------------------*/
/**@brief 显示音乐模式下的暂停界面
   @param 	void
   @return  void
   @note  void disp_music_pause(void)
*/
/*----------------------------------------------------------------------------*/
void disp_music_pause(void)
{

    printf_str("PAUS",0);

   // disp_music_play_time();
	led_disp_icon(LED0_PAUSE);
	disp_device();
    led_disp_icon(LED0_MP3);

}
/*----------------------------------------------------------------------------*/
/**@brief 显示扫描设备界面
   @param 	void
   @return  void
   @note  void disp_scan_disk(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan_disk(void)
{

    printf_str(" Lod",0);

}
/*----------------------------------------------------------------------------*/
/**@brief 显示Line In模式界面
   @param 	void
   @return  void
   @note  void disp_aux(void)
*/
/*----------------------------------------------------------------------------*/
void disp_aux(void)
{

    led_disp_icon(LED0_AUX);
    printf_str(" AUX",0);
}
#if USB_DEVICE_ENABLE

/*----------------------------------------------------------------------------*/
/**@brief 显示从机模式界面
   @param 	void
   @return  void
   @note  void disp_usb_device(void)
*/
/*----------------------------------------------------------------------------*/
void disp_usb_device(void)
{
    printf_str(" PC",0);
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief 清空更新屏幕
   @param 	void
   @return  void
   @note  void disp_nothing(void)
*/
/*----------------------------------------------------------------------------*/
void disp_nothing(void)
{
    clear_led();
}

#if RTC_ENABLE

extern RTC_TIME _xdata curr_time;
extern ALM_TIME _xdata alarm;
extern u8 _xdata rtc_mode_setting;

/*----------------------------------------------------------------------------*/
/**@brief 显示当前时间界面
   @param 	void
   @return  void
   @note  void disp_curr_time(void)

   Coordinate：
   	RTC_YEAR_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 0
	RTC_MONTH_COORDINATE	(RTC_END_COLUMN - 12*8)/2 + 40
	RTC_DAY_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 64
	RTC_HOUR_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 0
	RTC_MIN_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 24
	RTC_SEC_COORDINATE		(RTC_END_COLUMN - 12*8)/2 + 48
*/
/*----------------------------------------------------------------------------*/
void disp_curr_time(void)
{
}


/*----------------------------------------------------------------------------*/
/**@brief 显示当前闹钟信息界面
   @param 	void
   @return  void
   @note  void disp_alarm(void)

   Coordinate：
	ALM_ICON_COORDINATE		1*8
	ALM_SW_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
	ALM_HOUR_COORDINATE		8*8//(RTC_END_COLUMN - 12*8)/2 +
	ALM_MIN_COORDINATE		(8*8+24)//(RTC_END_COLUMN - 12*8)/2 +
	ALM_MON_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_TUE_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_WED_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_THU_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_FRI_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_SAT_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
	ALM_SUN_COORDINATE		(RTC_END_COLUMN - 12*8)/2 +
*/
/*----------------------------------------------------------------------------*/
void disp_alarm(void)
{

}
/*----------------------------------------------------------------------------*/
/**@brief 显示闹钟响闹界面
   @param 	void
   @return  void
   @note  void disp_alarm_up(void)
*/
/*----------------------------------------------------------------------------*/
void disp_alarm_up(void)
{
    //my_printf("%cAUX%m", LED_AUX_ICON);
}

#if USB_DEVICE_ENABLE

/*----------------------------------------------------------------------------*/
/**@brief 显示闹钟响闹请求界面
   @param 	void
   @return  void
   @note  void disp_alarm_up(void)
*/
/*----------------------------------------------------------------------------*/
void disp_alm_request(void)
{

}
#endif
#endif
/*----------------------------------------------------------------------------*/
/**@brief 	录音出错界面显示
   @param 	void
   @return  void
   @note  	void disp_rec_err(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_err(void)
{
    printf_str(" ERR",0);
    delay_10ms(100);
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音时间显示
   @param 	void
   @return  void
   @note  	void disp_rec_time(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_time(void)
{
    u16 encoder_time;
    u8 min,sec;

    encoder_time = encode_time();
    min = encoder_time / 60;
    sec = encoder_time % 60;

    printf_num(sec,2,2);
    printf_num(min,0,2);
    led_putchar(':',0);
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音工作界面显示
   @param 	void
   @return  void
   @note  	void disp_rec_working(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_working(void)
{
	disp_rec_time();
	led_disp_icon(LED0_PLAY);
	//disp_device();

	if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
	{
		led_flash_icon(LED0_SD);
	}
	else if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
	{
	    	led_flash_icon(LED0_USB);
	}	
}
/*----------------------------------------------------------------------------*/
/**@brief 	录音开始界面显示
   @param 	void
   @return  void
   @note  	void disp_rec(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec(void)
{
    printf_str("REC",1);
//	disp_device();

	if (device_online & DEVICE_SDMMC0)
    {
		led_disp_icon(LED0_SD);
    }
    if (device_online & DEVICE_UDISK)
    {
	  	led_disp_icon(LED0_USB);
    }

   if(encode_status >= RECODE_INIT)
   {
	   	if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
		{
			led_flash_icon(LED0_SD);
		}
		else if((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
		{
		    led_flash_icon(LED0_USB);
		}
   }
}

/*----------------------------------------------------------------------------*/
/**@brief 	录音暂停显示
   @param 	void
   @return  void
   @note  	void disp_rec_err(void)
*/
/*----------------------------------------------------------------------------*/
void disp_rec_pause(void)
{
	disp_rec_time();
	led_disp_icon(LED0_PAUSE);
	disp_device();
}

void disp_del(void)
{
	printf_str("dEL",1);
}
/*----------------------------------------------------------------------------*/
/**@brief 显示界面集中处理
   @param 	void
   @return  void
   @note  void disp_port(u8 menu)
*/
/*----------------------------------------------------------------------------*/
void disp_port(u8 menu)
{
   
    if (menu < 0x80)							//显示场景切换，整个显示均会更新
    {
        clear_led();
        cur_menu = menu;
        main_menu_conter = 0;

        if (menu != MENU_INPUT_NUMBER)
            input_number = 0;

        switch (menu)
        {
        case MENU_NULL:
            break;

        case MENU_PAUSE:
            disp_music_pause();
            break;

        case MENU_SCAN_DISK:
            disp_scan_disk();
            break;

        case MENU_MAIN_VOL:
            disp_main_vol(get_dac_vol(0));
            break;

        case MENU_FILENUM:
            disp_input_number(filenum_phy_logic(fs_msg.fileNumber));
            break;

        case MENU_MUSIC_MAIN:
            disp_music_main();
            break;

        case MENU_INPUT_NUMBER:
            disp_input_number(input_number);
            break;

        case MENU_FM_MAIN:
            #if FM_MODULE
            disp_fm_main();
            #endif 
            break;
        
        case MENU_FM_CHANNEL:
            #if FM_MODULE
            disp_fm_channel();
            #endif
            break;

        case MENU_POWER_UP:
            disp_power_on();
            break;

        case MENU_FM_DISP_FRE:
            #if FM_MODULE
            disp_fm_freq();
            #endif
            break;

        case MENU_FM_FIND_STATION:
            #if FM_MODULE
            disp_fm_find_station();
            #endif
            break;

        case MENU_AUX:
            
            disp_aux();
            break;

		case MENU_REC_ERR:
			disp_rec_err();
			break;

		case MENU_REC_MAIN:
			disp_music_main();
			break;

		case MENU_SET_EQ:
            disp_eq();
            break;

        case MENU_SET_PLAY_MODE:
            disp_play_mode();
            break;

        case MENU_RECWORKING:
            disp_rec_working();
            break;

        case MENU_REC:
            disp_rec();
            break;

		case MENU_REC_PAUSE:
			disp_rec_pause();
			break;

		case MENU_REC_DEL:
			disp_del();
			break;
#if ECHO_ENABLE
        case MENU_REV_DEEP:
            disp_rev_deep();
            break;

        case MENU_REV_STRONG:
            disp_rev_strong();
            break;
#endif
#if USB_DEVICE_ENABLE
        case MENU_USBDEV_MAIN:
            disp_usb_device();
            break;
#endif

#if RTC_ENABLE
        case MENU_RTC:
            disp_curr_time();
            break;

        case MENU_ALM_SET:
            disp_alarm();
            break;

        case MENU_ALM_UP:
            disp_alarm_up();
            break;

        case MENU_RTC_PWD:
            disp_power_off();
            break;
       
#if USB_DEVICE_ENABLE
        case MENU_ALM_REQUEST:
            disp_alm_request();
            break;
#endif
#endif
        }
    }
    else												//局部显示替换和更新
    {

        switch (menu)
        {
        case MENU_HALF_SEC_REFRESH:
            disp_main_menu_refresh();
            break;
        case MENU_POWER_DOWN:
            disp_nothing();
            break;
        }
    }

}
//#else



u8 led_flag;
/*----------------------------------------------------------------------------*/
/**@brief  点LED程序
   @param  1:开下拉	 0：开上拉
   @return 无
   @note   void dled_ctl(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void dled_ctl(u8 flag)
{

	P0DIR &= ~(BIT(7));
	P0PU|=(BIT(7));

	if(flag)
	{
		P07= 1;
	    //P5PU |= BIT(7);///500om POWER DOWN ENABLE
		//P5PU &=	~BIT(6);///10k POWER UP DISABLE
	}
	else
	{

		P07= 0;

	   //P5PU &= ~BIT(7);///500om POWER DOWN DISABLE
	//	P5PU |=	BIT(6);///10k POWER UP ENABLE
	}
}

/*----------------------------------------------------------------------------*/
/**@brief  LED闪烁速度
   @param  0:常亮	1：快闪   2：慢闪 
   @return 无
   @note   void flashled(u8 fre) 
*/
/*----------------------------------------------------------------------------*/
void flashled(u8 fre) 
{
    led_flag =fre;
}

/*----------------------------------------------------------------------------*/
/**@brief  LED闪烁函数
   @param  无 
   @return 无
   @note   void disp_dled(void) 
*/                                                                                                                                            
/*----------------------------------------------------------------------------*/
void disp_dled(void)
{
    static u8 cnt_led = 0;

	if(0 == led_flag)
	{
	   dled_ctl(0);
	}
	else if(1 == led_flag)
	{
		cnt_led++;			
		if(cnt_led > 50)
		{
		    cnt_led = 0;
		}
	
		if(cnt_led > 25)
		{
		    dled_ctl(1);
		}
		else
		{
			dled_ctl(0);
		} 
	}
	else if(2 == led_flag)
	{
		cnt_led++;			
		if(cnt_led > 100)
		{
		    cnt_led = 0;
		}
	
		if(cnt_led > 50)
		{
		    dled_ctl(1);
		}
		else
		{
			dled_ctl(0);
		} 
	}
	else if(3 == led_flag){

	   dled_ctl(1);

	}
}




#endif

