/*--------------------------------------------------------------------------*/
/**@file   main.c
   @brief  系统主函数
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#include "main.h"
#include "disp.h"
#include "fm_rev.h"
#include "led.h"
#include "music.h"
#include "device.h"
#include "dac.h"
#include "msgfor_usb.h"
#include "clock.h"
#include "disp.h"
#include "rtc_mode.h"
#include "gpio_if.h"


extern u8 _idata clock_in;
extern xd_u8 given_device;
extern u16 given_file_number;

extern u8 eq_mode;
extern u8 play_mode;
extern u8 _bdata device_online;

extern bool pc_connect, udisk_connect, sdmmc_connect;
extern u8 _xdata win_buffer[];
extern u8 _xdata alm_cnt;
u8 _code one_table[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};

bool input_number_en;				///<是否允许数字键输入功能
bool change_eq_en;					///<是否允许改变EQ的设置
xd_u8 work_mode;						///<工作模式变量
u8 _idata last_work_mode;			///<RTC 闹钟前的工作模式
bool kv_flag;						///<按键音的发送标记

u8  main_menu;						///<记录各种不同模式下的主界面
u8  cur_menu;        				///<当前界面
u8  main_menu_conter;				///<离开主界面的时间
bool flash_en,sys_pwr_off=0;						///<显示闪动允许
u8 bright_counter;
extern bool iic_busy,vol_change_en; ///<iic繁忙标记
extern  bool sys_mute_flag;

/*----------------------------------------------------------------------------*/
/**@brief  Line In检测函数
   @param  无
   @return 无
   @note   void aux_check(void)
*/
/*----------------------------------------------------------------------------*/
#ifdef MICPHONE_GPIO_DETECTION
bool mic_online=0;
static void mic_check(void)
{
    static u8 mic_cnt_online;

#if defined(MIC_DETECT_SHARE_WITH_IIC)
    if (iic_busy)
    {
        return;
    }
#endif	

    MICPHONE_GPIO_INIT();
    _nop_();  _nop_();
	
    if (MICPHONE_GPIO_READ)
    {
        mic_cnt_online = 0;

        if (mic_online)
        {
            put_msg_lifo(MSG_MIC_OUT);
            mic_online = 0;
        }
    }
    else
    {
        mic_cnt_online++;
        if (mic_cnt_online > 2)
        {
            if (!mic_online)
            {
                put_msg_lifo(MSG_MIC_IN);
                mic_online = 1;
            }
        }
    }
    MICPHONE_GPIO_RELEASE(); //linein check port
}
#endif

#ifdef USE_LINE_IN_DETECT_FUNC
bool aux_online;					///<AUX在线状态
static void aux_check(void)
{
    static u8 aux_cnt_online;

#if defined(AUX_DETECT_SHARE_WITH_IIC)
    if (iic_busy)
    {
        return;
    }
#endif	
    aux_detect_in();
	
    _nop_();
    _nop_();
    _nop_();
    if (AUX_DETECT_GPIO)
    {
        aux_cnt_online = 0;

        if (aux_online)
        {
            put_msg_lifo(MSG_AUX_OUT);
            aux_online = 0;
        }
    }
    else
    {
        aux_cnt_online++;
        if (aux_cnt_online > 2)
        {
            if (!aux_online)
            {
                put_msg_lifo(MSG_AUX_IN);
                aux_online = 1;
            }
        }
    }
    aux_detect_in_off(); //linein check port
}
#endif

#ifdef USE_HPHONE_DETECT
bool hp_online;
static void hp_check(void)
{
    static u8 hp_cnt_online;
	
#if defined(HP_DETECT_SHARE_WITH_IIC)
    if (iic_busy)
    {
        return;
    }
#endif	
    hp_detect_in();
	
    //DACCON0 |= 0x80;
    _nop_();
    _nop_();
    _nop_();
    if (HP_DETECT_GPIO)
    {
        hp_cnt_online = 0;

        if (hp_online)
        {
            put_msg_lifo(MSG_HP_OUT);
            hp_online = 0;
        }
    }
    else
    {
        hp_cnt_online++;
        if (hp_cnt_online > 2)
        {
            if (!hp_online)
            {
                put_msg_lifo(MSG_HP_IN);
                hp_online = 1;
            }
        }
    }
    hp_detect_in_off(); //linein check port
}
#endif


/*----------------------------------------------------------------------------*/
/**@brief   使用独立的GPIO检测SD card在线
   @param   void
   @return  void
   @note    void sdmmc_detect(void)
*/
/*----------------------------------------------------------------------------*/
void sdmmc_detect(void)
{
    static u8 sdmmc_cnt_online;
    P3DIR |= BIT(3); //linein check port
    P3PU |= BIT(3);
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    if (P33)
    {
        sdmmc_cnt_online = 0;
        sdmmc_chk_io(0);
    }
    else
    {
        if (sdmmc_cnt_online<51)
        {
            sdmmc_cnt_online++;
        }
        if (sdmmc_cnt_online > 50)
        {
            sdmmc_chk_io(1);
        }
        else
        {
            sdmmc_chk_io(0xff);
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
void rtcisr(void)
{
    PSW = 0x08;
    DPCON = 0x0;
#if BURST_OUT_POINT_SAVE_ENABLE
    burst_out_break_point_save();
#endif

}
/*----------------------------------------------------------------------------*/
/**@brief  RTC中断服务程序
   @param  无
   @return 无
   @note   void rtcisr(void)
*/
/*----------------------------------------------------------------------------*/
#ifdef JOG_STICK_FUNC	 	
extern void JogDetect(void);
#ifdef JOG_STICK_FUNC_USE_TWO
extern void JogDetect_c(void);
#endif
#endif		
void timer0isr(void)
{
    static u8 counter0, counter1;

    PSW = 0x08;
    DPCON = 0x0;
    T0CON &= ~BIT(7);			//clear pending

    disp_scan();
    adc_scan();
    counter0++;
    usb_polling();
#ifdef JOG_STICK_FUNC	 	
	JogDetect();
#ifdef JOG_STICK_FUNC_USE_TWO
	JogDetect_c();
#endif
#endif		
    if ((counter0 % 5) == 0)			//10ms
    {
        dec_delay_counter();
//#if SDMMC_CMD_MODE
//        sd_online_check();
#if SDMMC_CLK_MODE
        sdmmc_online_chk(1);
#elif SDMMC_GPIO_MODE
        sdmmc_detect();
#endif
        keyScan();
#ifndef NO_PLAY_STATUS_LED
	 disp_dled();
#endif
    }

//    if ((counter0 % 50) == 0)
//    {
//        put_msg_fifo(MSG_100MS);
//    }
    if ((counter0 % 100) == 0)
    {
#ifdef MICPHONE_GPIO_DETECTION
	 mic_check();
#endif    
#ifdef USE_LINE_IN_DETECT_FUNC
	 aux_check();
#endif

#ifdef USE_HPHONE_DETECT
	 hp_check();
#endif

        put_msg_fifo(MSG_200MS);
        counter0 = 0;
    }
    counter1++;
    if ((counter1 % 250) == 0)
    {
        put_msg_fifo(MSG_HALF_SECOND);
        counter1 = 0;
    }
#if RTC_ENABLE
    if (IRTCON & BIT(7))
    {
        alm_cnt = 1;
        last_work_mode = work_mode;
        put_msg_lifo(MSG_ALM_ON);
    }
#endif
}

/*----------------------------------------------------------------------------*/
/**@brief  系统共用信息的初始化
   @param  无
   @return 无
   @note   void sys_info_init(void)
*/
/*----------------------------------------------------------------------------*/
static void sys_info_init(void)
{
    u8 tmp;

#if (DEFAULT_VOL>0)
	tmp = DEFAULT_VOL;
#else
    tmp = read_info(MEM_VOL);

    if ((tmp > MAX_MAIN_VOL) || (tmp == 0))              //每次开机时，不要超过最大音量的一半，以免开机音量过大
    {
       // tmp = MAX_MAIN_VOL/2;
        tmp = 20;
    }
#endif

    dac_init(tmp);
    delay_10ms(50);										//等待,检测USB,SD在线状态
    init_rec_name();
    restore_music_point();
	
#if RTC_ENABLE
    if (work_mode != RTC_MODE)
#endif
    {
    	device_check();
#if USB_DEVICE_ENABLE
        if (pc_connect)
            work_mode = USB_DEVICE_MODE;
        else if (udisk_connect || sdmmc_connect)
            work_mode = MUSIC_MODE;
#else
        if (udisk_connect || sdmmc_connect)
            work_mode = MUSIC_MODE;
#endif
        else
        {
            work_mode = read_info(MEM_SYSMODE);
            if (work_mode > MAX_WORK_MODE)
            {
                work_mode = MUSIC_MODE;
            }
        }
    }
#if defined(POWER_ON_DEFAULT_IN_AUX)
	work_mode = AUX_MODE;
#elif defined(POWER_ON_DEFAULT_IN_IDLE)
	work_mode = IDLE_MODE;
#endif

#if defined(K000_LYXD_00000_REC_V001)  
	P1DIR &= ~(BIT(7)); 
	P1PU |= BIT(7);
	P17 = 0;
#endif	
}
/*----------------------------------------------------------------------------*/
/**@brief  系统主函数
   @param  无
   @return 无
   @note   void main(void)
*/
/*----------------------------------------------------------------------------*/

void sys_init(void)
{
     u8 i;

#if defined(UART_ENABLE)
    uart_init();
    deg_str("power on\n");
#endif

    core_power_on();
    OTP_CLK_DIV2();
    DECODER_DIV2();
    SYSTEM_CLK_DIV4();
#if (NO_DISP != monitor)
    init_display();
#endif
    sd_speed_init(0,100);

//#if SDMMC_CMD_MODE
//    sd_chk_ctl(SET_SD_H_CHK);
//#endif
    init_port_sd();
    kv_init(); ///按键音初始化函数

#if RTC_ENABLE
    if (rtc_init())			//RTC初始化，检测是否闹钟开机
    {
        work_mode = RTC_MODE;
    }
#else
    {
        u8 rtc_reg = read_rtc_reg();
        if (rtc_reg & BIT(7))					//检测是否掉电
        {
            rtc_reg &= ~BIT(7); 				//清零PDFLAG
            write_rtc_reg(rtc_reg);
#if USE_RTC_RAM
	 // reset_rtc_ram();
		   for (i = 0; i < 64; i++)
		    {
		        write_rtc_ram(i, 0);
		    }
#endif
        }
    }
#endif
    key_init();
    bsp_init();
    interrupt_init(15, rtcisr);
#ifndef NO_IR_REMOTE	
    interrupt_init(3, timer3isr);
#endif
    interrupt_init(0, timer0isr);
    enable_interrupt();
    flashled(LED_ON);
}
void idle_mode(void)
{
    u8 key;
    input_number_en = 0;
    vol_change_en=0;
#if defined(POWER_ON_DEFAULT_IN_IDLE)||defined(DEFAULT_GOTO_IDLE)
    disp_port(MENU_NODEVICE);			
#endif

#ifdef IDLE_MODE_FOR_VOICE_AMP
    disp_port(MENU_NODEVICE);			
    ext_amp_mute(EXT_AMP_UNMUTE);
#else
    ext_amp_mute(EXT_AMP_MUTE);	

#ifdef POWER_OFF_IN_IDEL
    if(sys_pwr_off){
	    disp_port(MENU_POWER_OFF);			
    }
   clear_all_event();
   flush_low_msg();
#endif
#endif

#ifdef MICPHONE_GPIO_DETECTION
#ifdef MUTE_AMP_IN_IDLE_MODE
	mic_online=0;
#else
    ext_amp_mute(EXT_AMP_UNMUTE);
    disp_port(MENU_MIC);			
#endif
#endif

   while (1)
    {
        key = app_get_msg();

        switch (key)
        {
        case MSG_POWER_DOWN:

	    if(sys_pwr_off){
			sys_pwr_off =0;
	        	put_msg_lifo(MSG_CHANGE_WORK_MODE);
	    }
	    disp_port(MENU_POWER_OFF);	
		
		break;
        case MSG_NO_DEVICE:
	    clear_all_event();
	    flush_low_msg();
	    disp_port(MENU_NODEVICE);			
		break;
		
        case MSG_CHANGE_WORK_MODE:

#ifdef POWER_OFF_IN_IDEL
	    if(sys_pwr_off){
		break;
	    }
#if (NO_DISP != monitor)
	    	init_display();
#endif
            	work_mode = MUSIC_MODE;
    		//sys_init();
    		AMUX_P2IE_SET(AMUX0_IE&AMUX1_IE);
    		sys_info_init();
	    	clear_all_event();
    	   	flush_all_msg();
		delay_10ms(50);
		sys_mute_flag =0;
       	dac_mute_control(0,1);					//调节音量时，自动UNMUTE
      	       //main_vol_set(0, SET_USE_CURRENT_VOL);

#else
	if(device_online>0){
	            work_mode = MUSIC_MODE;
	}
	else {
#if FM_MODULE 		
            work_mode = FM_RADIO_MODE;
#endif
	}
#endif	
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入

#ifdef DEFAULT_GOTO_IDLE
            work_mode = MUSIC_MODE;
		return;
#endif

            break;

        case MSG_HALF_SECOND:
////////////////////////////////////////////////////////////
//显示界面的切换
#if 0            
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
#endif

            break;
#if RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif
        default:
#ifdef POWER_OFF_IN_IDEL
      	    if(sys_pwr_off)break;
#endif
            ap_handle_hotkey(key);        
            break;
        }
    }

}
void main(void)
{
    ext_amp_mute(EXT_AMP_MUTE);
    clock_in = T0CNT;									//输入时钟,define in clock.h
  //  WDT_EN();
    sys_init();
    AMUX_P2IE_SET(AMUX0_IE&AMUX1_IE);
    sys_info_init();
    clear_all_event();
    flush_all_msg();

#ifdef MICPHONE_GPIO_DETECTION
	mic_online=0;
#endif
    ///*
    while (1)
    {
	
        switch (work_mode)
        {
        case MUSIC_MODE:
            music_decode();
            break;
#if USB_DEVICE_ENABLE
        case USB_DEVICE_MODE:
            usb_audio_massstorage();
            break;
#endif     

#if FM_MODULE                     
        case FM_RADIO_MODE:
            fm_radio();
            break;
#endif

#ifndef NOT_USE_LINE_IN_FUNC
        case AUX_MODE:
            aux_fun();
            break;
#endif

#if RTC_ENABLE
        case RTC_MODE:
            rtc_fun();
            break;        
#endif
        case REC_MIC_MODE:
            rec_mic_fun();
            break;
			
        case IDLE_MODE:
            idle_mode();
            break;		
        default:
            work_mode = MUSIC_MODE;
            break;
        }
        write_info(MEM_SYSMODE ,work_mode);
    }
    //*/
}
