/*--------------------------------------------------------------------------*/
/**@file   key.c
   @brief  按键消息扫描模块
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"
#include "key.h"
#include "uart.h"
#include "led.h"
#include "adkey.h"
#include "irff00.h"
#include "dsp.h"
#include "dac.h"
extern xd_u8 work_mode;
extern u8 _idata last_work_mode;
extern DECODER_MSG _xdata *dec_msg;

extern bit kv_flag;
u16 _xdata kv_rate_tab[6] _at_ 0x011E;
u8 _code lifo_msg_tab[] = 						//高优先级消息，需要后进先出
{
    MSG_MUSIC_FFR_DONE,
};
#include "my_IR_key.h"
extern _code MY_IR_KEY_STRUCT My_IRTab[];       /*user code is 0xFF*/
extern u8 get_my_IR_key_MAX();
static u8 _xdata MAX_IR_KEY = 0;

xd_u8 key_mode=0;			  ///<按键消息的类型
u16 _idata user_code;     ///<红外遥控提取的用户码
u8 _idata irda_state;     ///<IR当前状态
u16 _idata irda_data;     ///<IR读取读取出的数据
u16 _idata adkey_value1;  ///<adkey 采样值
#ifdef USE_TWO_ADKEY
u16 _idata adkey_value2;  ///<adkey 采样值
#endif
u8 _xdata adc_vdd12;	  ///<参考电压VDD1.25v的采样值
u8 _xdata adc_vddio;	  ///<VDDI0的采样值

bool key_voice_en;		  ///<按键音使能位
bool key_sel_table=0;

//u8  (_code * adkey1_table)[10];	   ///<ADKEY 策略表
//u8  (_code * remote_table)[21];	   ///<遥控策略表

u16 _xdata key_voice_tab[3] _at_ 0x0118; ///<按键音音量与按键音与相应长度参数

//u16 _code kv_sample_rate_tab[6] _at_ 0x7fa0;//= {0x4a3,0x4ae,0x493,0x4a2,0x481,0x492};

/**/


const u8 _code event_msg_table[] =
{
    MSG_USB_DISK_IN,
    MSG_USB_DISK_OUT,
    MSG_USB_PC_IN,
    MSG_USB_PC_OUT,
    MSG_SDMMC_IN,
    MSG_SDMMC_OUT,
    MSG_PC_MUTE,
    MSG_PC_UNMUTE,
    MSG_AUX_IN,
    MSG_AUX_OUT,
    MSG_ALM_ON,
    MSG_ENCODE_END
};
/*----------------------------------------------------------------------------*/
/**@brief  按键音初始化函数
   @param  无
   @return 无
   @note   void kv_init(void)
*/
/*----------------------------------------------------------------------------*/
#define KV_441K_ADDR_STR  0x0493
#define KV_441K_ADDR_END  0x04a2
#define KV_48K_ADDR_STR	  0x0481
#define KV_48K_ADDR_END	  0x0492
#define KV_32K_ADDR_STR	  0x04a3
#define KV_32K_ADDR_END	  0x04ae
void kv_init(void)
{
    key_voice_tab[0] = 2000;///<按键音量
    key_voice_tab[1] = 16384;///<闹钟音量
    key_voice_tab[2] = 100;///<按键音响应长度
////////////////
    kv_rate_tab[0] = KV_441K_ADDR_STR;
    kv_rate_tab[1] = KV_441K_ADDR_END;
////////////////
    kv_rate_tab[2] = KV_48K_ADDR_STR;
    kv_rate_tab[3] = KV_48K_ADDR_END;
////////////////
    kv_rate_tab[4] = KV_32K_ADDR_STR;
    kv_rate_tab[5] = KV_32K_ADDR_END;
    bsp_kv_init();
}
/*----------------------------------------------------------------------------*/
/**@brief  闹钟闹铃，在采样率不属于32/44.1/48kHz分组时，采用默认分组
   @param  无
   @return 无
   @note   void alarm_tone(void)
*/
/*----------------------------------------------------------------------------*/
void alarm_tone(void)
{
    send_alm_voice();
}

/*----------------------------------------------------------------------------*/
/**@brief  设置DSP参数，产生按键音
   @param  无
   @return 无
   @note   void set_key_tone(void)
*/
/*----------------------------------------------------------------------------*/
void enable_key_tone_flag(bool key_tone)
{
	#if defined(ENABLE_KEY_TONE)
		key_voice_en=key_tone;
	#else
		key_tone =0;
		key_voice_en=key_tone;
	#endif
}
void set_key_tone(void)
{
    if (!key_voice_en)
    {
        return ;
    }
    fun_send_kv();
}
/*----------------------------------------------------------------------------*/
/**@brief  获取消息池的消息,事件最终转化为消息
   @param  无
   @return 消息
   @note   u8 app_get_msg(void)
*/
/*----------------------------------------------------------------------------*/
u8 app_get_msg(void)
{
    u8 event, msg;

    WDT_CLEAR();

    event = get_event();

    if (event != NO_EVENT)
    {
        clear_one_event(event);
        msg = event_msg_table[event];
    }
    else
        msg = get_msg();

    if (msg == NO_MSG)
    {
        SYS_IDLE();
    }

    return msg;
}

/*----------------------------------------------------------------------------*/
/**@brief  AD按键初始化
   @param  无
   @return 无
   @note   void adckey_init(void)
*/
/*----------------------------------------------------------------------------*/
static void adckey_init(void)
{
#if defined(ADKEY_PORT_P06)
    P0PD &= ~(BIT(6));
    P0IE = ~(BIT(6));
    P0DIR |= BIT(6);
#elif defined(ADKEY_PORT_P02)
    P0PU&= ~(BIT(2));
    P0PD &= ~(BIT(2));
    P0IE = ~(BIT(2));
    P0DIR |= BIT(2);
#else //default  :   ADKEY_PORT_P07
    P0PD &= ~(BIT(7));
    P0IE = ~(BIT(7));
    P0DIR |= BIT(7);
#endif	
    ADCCON = ADC_VDD_12;
//	ADCCON = 0xff;					//select P07 for ADC key

}
/*----------------------------------------------------------------------------*/
/**@brief  按键初始化
   @param  无
   @return 无
   @note   void key_init(void)
*/
/*----------------------------------------------------------------------------*/
void key_init(void)
{
    adckey_init();
     MAX_IR_KEY = get_my_IR_key_MAX();
}
/*----------------------------------------------------------------------------*/
/**@brief  按键功能表选择
   @param  sel:表号
   @return 无
   @note   void key_table_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
#pragma disable
void key_table_sel(u8 sel)
{
    if (sel == 0)
    { 
    	 key_sel_table = 1;
        //adkey1_table = adkey1_msg_music_table;
        //remote_table = irff00_msg_music_table;
    }
    else
    {
        key_sel_table = 0;
        //adkey1_table = adkey1_msg_fm_table;
        //remote_table = irff00_msg_fm_table;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  LDO IN 电量检测
   @param  无
   @return 无
   @note   u8 ldoin_voltage(void)
*/
/*----------------------------------------------------------------------------*/
u8 ldoin_voltage(void)
{
    return ((((u16)adc_vddio*248+5)/10)/adc_vdd12);
}

#if defined(USE_BAT_MANAGEMENT)
xd_u8 LDO_IN_Volt=0;
#define BAT_LOW_VOLT   	32/*LDOIN=3.3V*/ //(1D/*LDOIN=3.5V*/) (43/*LDOIN=3.7V*/) (45/*LDOIN=3.8V*/) (46/*LDOIN=3.9V*/) (47/*LDOIN=4.0V*/) (48/*LDOIN=4.1V*/) (49/*LDOIN=4.1V*/) 
#define BAT_FULL_VOLT   	42
#define BAT_HALF_VOLT   	36

#if defined(CHARGER_DETECT_INDICATOR)

#if defined(CHARGER_IND_TYPE_1)
 static bool charger_flash_icon=0;
#endif

bool charger_in_flag=0;
bool charger_detect(void)
{
     charge_port_init();

     if(CHARGER_DET_PORT){

		charger_in_flag =1;
		
#if defined(CHARGER_IND_TYPE_1)
		charger_flash_icon =~charger_flash_icon;
#endif		
		return 1;
     }
     charger_in_flag =0;
     return 0;
}
#endif
void Bat_icon_chk(void)
{
#ifndef NO_LED_DISPLAY

#if defined(CHARGER_DETECT_INDICATOR)
	if(charger_in_flag){
		
		if(LDO_IN_Volt>=BAT_FULL_VOLT){
			
			clr_led_flash_icon(LED0_BAT_L);
			led_disp_icon(LED0_BAT_H);
			return;
		}
#if defined(CHARGER_IND_TYPE_1)		
		if(charger_flash_icon){
			clr_led_disp_icon(LED0_BAT_L);
			led_disp_icon(LED0_BAT_H);
		}
		else{
			clr_led_disp_icon(LED0_BAT_H);
			led_disp_icon(LED0_BAT_L);
		}
#else		
		led_flash_icon(LED0_BAT_L);
#endif
		return;
	}
#endif	
	//clr_led_flash_icon(LED0_BAT_L);
	//clr_led_flash_icon(LED0_BAT_H);


	if(LDO_IN_Volt<BAT_HALF_VOLT){
		
		led_disp_icon(LED0_BAT_L);
		clr_led_disp_icon(LED0_BAT_H);
	}
	else{
		
		led_disp_icon(LED0_BAT_H);
		clr_led_disp_icon(LED0_BAT_L);
	}
#endif	

}
void bmt_hdlr(void)
{
	LDO_IN_Volt=ldoin_voltage();
	
#if defined(CHARGER_DETECT_INDICATOR)
	if(charger_detect()){

	}
#endif

	Bat_icon_chk();

}

#endif	

/*----------------------------------------------------------------------------*/
/**@brief  ADC循环扫描程序 2MS被调用一次,分别扫描VDD1.2
   @param  无
   @return 无
   @note   void adc_scan(void)
*/
/*----------------------------------------------------------------------------*/
void adc_scan(void)
{
    static u8 cnt;

    if (cnt == 0)
    {
        adc_vdd12 = ADCDATH;//
        //adc_vdd12l = ADCDATL;
#if defined(VDD_VOLT_CAL_USE_PORT_P02)
    	 P0PD &= ~(BIT(2));
        ADCCON = ADC_KEY_IO2; //
        P0IE = ~(BIT(2));	 
#elif defined(VDD_VOLT_CAL_USE_PORT_P04)
    	 P0PD &= ~(BIT(4));
        ADCCON = ADC_KEY_IO4; //
        P0IE = ~(BIT(4));	 
#else
        ADCCON = ADC_LDOIN;
#endif
    }
    else if (cnt == 1)
    {
        adc_vddio = ADCDATH;//
        //adc_vddiol = ADCDATL;//
#if defined(ADKEY_PORT_P06)
    	 P0PD &= ~(BIT(6));
        ADCCON = ADC_KEY_IO6; //
        P0IE = ~(BIT(6));	 
#elif defined(ADKEY_PORT_P02)
    	 P0PU&= ~(BIT(2));
    	 P0PD &= ~(BIT(2));
        ADCCON = ADC_KEY_IO2; //
        P0IE = ~(BIT(2));	 
#else
    	 P0PD &= ~(BIT(7));
        ADCCON = ADC_KEY_IO7; //
        P0IE = ~(BIT(7));	 
#endif		
    }
    else if (cnt == 2)
    {
        ((u8 *)(&adkey_value1))[0] = ADCDATH;
        ((u8 *)(&adkey_value1))[1] = ADCDATL;
		
#ifdef USE_TWO_ADKEY

#if defined(TWO_ADKEY_PORT_P06)
    	 P0PD &= ~(BIT(6));
        ADCCON = ADC_KEY_IO6; //
        P0IE = ~(BIT(6));	 
#elif defined(TWO_ADKEY_PORT_P02)
    	 P0PD &= ~(BIT(2));
        ADCCON = ADC_KEY_IO2; //
        P0IE = ~(BIT(2));	 
#else        
    	 P0PD &= ~(BIT(7));
        ADCCON = ADC_KEY_IO7; //
        P0IE = ~(BIT(7));	 
#endif

#else		
        ADCCON = ADC_VDD_12;
#endif
    }
#ifdef USE_TWO_ADKEY	
    else if (cnt == 3)
    {
        ((u8 *)(&adkey_value2))[0] = ADCDATH;
        ((u8 *)(&adkey_value2))[1] = ADCDATL;
        ADCCON = ADC_VDD_12;
    }	
#endif
    else
    {
        cnt = 0;
    }
    cnt++;
    if (cnt >= ADC_MAX_USED)
        cnt = 0;
}


/*----------------------------------------------------------------------------*/
/**@brief  读取键值keyDetect
   @param  无
   @return 无
   @note   u8 keyDetect(void)
*/
/*----------------------------------------------------------------------------*/
u8 keyDetect(void)
{
    u8 keyTemp=0;
    u8 key_index=0;

    keyTemp = NO_KEY;
    if (irda_state == 32)
    {
        if (((irda_data & 0xff) + ((irda_data >> 8) & 0xff)) != 0xff)
        {
            irda_state = 0;
            return keyTemp;
        }

        if(IR_FF00 == user_code)
        {
       #if 0
            	keyTemp = IRTabff00[(u8)irda_data];
       #else
		for(key_index = 0;key_index <MAX_IR_KEY;key_index++){
	            if((My_IRTab[key_index].IR_Key_Value)==(irda_data & 0xff)){
				keyTemp = (My_IRTab[key_index].APP_Key);
			        //printf(" IR  00000000keyDetect %d  \r\n",(u16)keyTemp);
				break;
		     }
		}     
	#endif
        }
        else if (0xfd02 == user_code)
        {
       #if 0
            	keyTemp = IRTabff00[(u8)irda_data];
       #else
		for(key_index = 0;key_index <MAX_IR_KEY;key_index++){
	            if((My_IRTab[key_index].IR_Key_Value)==(irda_data & 0xff)){
				keyTemp = (My_IRTab[key_index].APP_Key);
			        //printf(" IR  00000000keyDetect %d  \r\n",(u16)keyTemp);
				break;
		     }
		}     
	#endif
        }

    }

    return keyTemp;
}


/*----------------------------------------------------------------------------*/
/**@brief  AD按键转换
   @param  无
   @return 无
   @note void adkey2(u16 key_value)
   @note   ADkey group2 按键值
   Range：				   voltage:
   @note   0xe900~0xe840   3.037
   @note   0xd200~0xd180   2.739
   @note   0xb380~0xb300   2.346
   @note   0x9980~0x9940   2.012
   @note   0x8600~0x8580   1.755
   @note   0x6800~0x6780   1.362
   @note   0x4ac0~0x4a40   0.982
   @note   0x3800~0x3780   0.737
   @note   0x1e80~0x1e40   0.406
   @note   0
*/
/*----------------------------------------------------------------------------*/

u8 adkey1(u16 key_value)
{
    u8 i;

    if (key_value > ADKEY1)
    {
        return NO_KEY;
    }
    else
    {
        for (i = 0; i < (TOTAL_KEY_NUM-1); i++)
            if (key_value > adkey1_check_table[i])
                break;
    }

    return i;
}
#ifdef USE_TWO_ADKEY
u8 adkey2(u16 key_value)
{
    u8 i;


    if (key_value > ADKEY2)
    {
        return NO_KEY;
    }
    else
    {		
        for (i = 0; i < (TOTAL_KEY_NUM-1); i++)
            if (key_value > adkey2_check_table[i])
                break;
    }
    return i;
}
#endif

#ifdef JOG_STICK_FUNC
xd_u8 touchkeyval;
xd_u8 keyval_buf;
xd_u8  JogBuf;
void JogDetect(void)
{
	u8 port_val=0;
	
    touchkeyval = 0;
#if defined(K1081_WK_1081_REC_V001)
    P0DIR &= ~(BIT(2)|(BIT(4)));    //P11, P12
    P0 |=(BIT(2)|(BIT(4)));
    P0PU	|= (BIT(2)|(BIT(4)));
    P0DIR |= (BIT(2)|(BIT(4)));    //P11, P12
    _nop_();
    port_val =(P0&(BIT(2)|(BIT(4))));
    touchkeyval = ((port_val & (BIT(2)))>>2)|((port_val & (BIT(4)))>>3);
#elif defined(K000_LYXD_00000_REC_V001)
    P0DIR &= ~(BIT(2)|(BIT(3)));    //P11, P12
    P0 |=(BIT(2)|(BIT(3)));
    P0PU	|= (BIT(2)|(BIT(3)));
    P0DIR |= (BIT(2)|(BIT(3)));    //P11, P12
    _nop_();
    port_val =(P0&(BIT(2)|(BIT(3))));
    touchkeyval = ((port_val & (BIT(2)))>>2)|((port_val & (BIT(3)))>>2);
#endif

	if((touchkeyval == 0x00) || (touchkeyval == 0x03))
    {										
        if(touchkeyval == keyval_buf)
        {
            JogBuf = 0;
        }
        else
        {
            keyval_buf = touchkeyval;
            if (touchkeyval == 0x00)
            {
                if (JogBuf == 0x02)
                {
                    // Increase
	             put_msg_fifo(MSG_VOL_DOWN);
                    JogBuf = 0;
                }
                if (JogBuf == 0x01)
                {
                    // Decrease
	                 put_msg_fifo(MSG_VOL_UP);
	             //put_msg_fifo(INFO_VOL_MINUS);
                    JogBuf = 0;
                }
            }
            else
            {
                if (JogBuf == 0x02)
                {
                    // Decrease
                    JogBuf = 0;
                }
                if (JogBuf == 0x01)
                {			
                    // Increase 
                    JogBuf = 0;
                }					
            }
        }
    }
	else
	{
		JogBuf = touchkeyval;
    }
}
#ifdef JOG_STICK_FUNC_USE_TWO
xd_u8 touchkeyval_c;
xd_u8 keyval_buf_c;
xd_u8  JogBuf_c;
void JogDetect_c(void)
{
	u8 port_val_c=0;
	
    touchkeyval_c = 0;
	
    P0DIR &= ~(BIT(4)|(BIT(7)));    //P11, P12
    P0 |=(BIT(4)|(BIT(7)));
    P0PU	|= (BIT(4)|(BIT(7)));
    P0DIR |= (BIT(4)|(BIT(7)));    //P11, P12
    _nop_();
    port_val_c =(P0&(BIT(4)|(BIT(7))));
    touchkeyval_c = ((port_val_c & (BIT(4)))>>4)|((port_val_c & (BIT(7)))>>6);

	if((touchkeyval_c == 0x00) || (touchkeyval_c == 0x03))
    {										
        if(touchkeyval_c == keyval_buf_c)
        {
            JogBuf_c = 0;
        }
        else
        {
            keyval_buf_c = touchkeyval_c;
            if (touchkeyval_c == 0x00)
            {
                if (JogBuf_c == 0x02)
                {
                    // Increase
                    if(work_mode == MUSIC_MODE){
						
	             		put_msg_fifo(MSG_MUSIC_PREV_FILE);
                    }
		      else{
	             		put_msg_fifo(MSG_FM_PREV_STATION);
		      }
			  
                    JogBuf_c = 0;
                }
                if (JogBuf_c == 0x01)
                {
                    // Decrease
                    if(work_mode == MUSIC_MODE){
						
                    		put_msg_fifo(MSG_MUSIC_NEXT_FILE);
                    }
			else{
	             		put_msg_fifo(MSG_FM_NEXT_STATION);
			}
                    	JogBuf_c = 0;
                }
            }
            else
            {
                if (JogBuf_c == 0x02)
                {
                    JogBuf_c = 0;
                }
                if (JogBuf_c == 0x01)
                {			
                    JogBuf_c = 0;
                }					
            }
        }
    }
	else
	{
		JogBuf_c = touchkeyval_c;
    }
}
#endif
#endif

/*----------------------------------------------------------------------------*/
/**@brief  处理扫描到的按键，长按、短按、HOLD按键状态等在这里进行 ；按键音也在这里处理
   @param  无
   @return 无
   @note void keyScan(void)
   @note 开发板ADKEY结果：
   @note VOL-(0v): 0
   @note VOL+(0.43v): 0x21
   @note PREV(0.82v): 0x3F
   @note NEXT(1.237v): 0x5F
   @note PLAY(1.616v): 0x7C
   @note FM/MP3(2.05v): 0x9E
   @note EQ(2.50v): 0xC1
   @note PlayMode(2.93v): 0xE2
*/
/*----------------------------------------------------------------------------*/
void keyScan(void)
{
    static u8 last_key;  ///<上一次按键扫描结果
    static u8 key_counter;   ///<连续有效的按键扫描计数

    u8 keyTemp;
    u8 key_style = NO_KEY;

    keyTemp = adkey1(adkey_value1);
    if (keyTemp == NO_KEY)
    {

#ifdef USE_TWO_ADKEY
	   keyTemp = adkey2(adkey_value2);
          if (keyTemp != NO_KEY)
          {
        	key_mode = 1;															//按键为AD按键
          }
	   else
#endif	   	
	   {
#ifndef NO_IR_REMOTE
	        keyTemp = keyDetect();
	        if (keyTemp != NO_KEY)
	        {
	            key_mode = 2;														//按键为遥控按键
	        }	
#endif	 	

	 }
    }
    else{
        key_mode = 0;															//按键为AD按键
    }

    if ( (NO_KEY == keyTemp) /*|| (keyTemp != last_key)*/ )
    {
        if (key_counter >= KEY_LONG_CNT)			 //长按抬起
        {
            key_style = 3;

        }
        else if (key_counter >= KEY_BASE_CNT)		//短按抬起
        {
            key_style = 0;
        }
        key_counter = 0;
    }
    else if (keyTemp != last_key)
    {
        key_counter = 0;
        put_msg_fifo(MSG_KEY_CHANGE);
    }
    else
    {
        key_counter++;
        if (KEY_BASE_CNT == key_counter)			//去抖
        {
            //key_style = 0;
            set_key_tone();
        }
        else if (KEY_LONG_CNT == key_counter)				//长按
        {
            set_key_tone();
            key_style = 1;
        }
        else if ((KEY_LONG_CNT + KEY_HOLD_CNT) == key_counter)			//连按
        {
            set_key_tone();
            key_style = 2;
            key_counter = KEY_LONG_CNT;
        }
    }
    if ((NO_KEY != last_key) && (key_style != NO_KEY))
    {
        u8 key, i;

        set_brightness_all_on();

        if (key_mode == 0)
        {
        	if(key_sel_table)
	            key = adkey1_msg_music_table[key_style][last_key];
		else
	            key = adkey1_msg_fm_table[key_style][last_key];
        }
#ifdef USE_TWO_ADKEY		
        else if (key_mode == 1)
        {
        	if(key_sel_table)
	            key = adkey2_msg_music_table[key_style][last_key];
		else
	            key = adkey2_msg_fm_table[key_style][last_key];
        }		
#endif		
        else if (key_mode == 2)									//遥控
        {
        	if(key_sel_table)        
	            key = irff00_msg_music_table[key_style][last_key];
		else
	            key = irff00_msg_fm_table[key_style][last_key];
        }

#ifdef ADKEY_DETECT_FUNC
	if((key==MSG_MIC_OUT)||(key==MSG_MIC_IN)){
		
		
	}
#endif

        if (key == NO_MSG)										//无效
            goto _exit_keyScan;

        for (i = 0; i < sizeof(lifo_msg_tab); i++)
        {
            if (key == lifo_msg_tab[i])
            {
                put_msg_lifo(key);
                flush_low_msg();
                goto _exit_keyScan;
            }
        }
        put_msg_fifo(key);

    }
_exit_keyScan:
    last_key = keyTemp;
}

/*
5062.5 13.5ms
4218.75 11.25ms
36281.25 96.75ms
421.875  1.125ms
843.75   2.25ms
*/

/*----------------------------------------------------------------------------*/
/**@brief  红外遥控中断处理函数
   @param  无
   @return 无
   @note void timer3isr(void)
*/
/*----------------------------------------------------------------------------*/
#ifdef NO_IR_REMOTE
void timer3isr(void)
{
	return;
}
#else
void timer3isr(void)
{
    u8 counter;
    u16 ircnt;

    PSW = 0x08;
    DPCON = 0;

    if (T3CON & BIT(6))
    {
        T3CON &= ~BIT(6);

        if ((P5PU & 0x80))
            return;

        ircnt = T3PWMH ;
        ircnt <<= 8;
        ircnt |= T3PWML;
        T3CNTL = 0;
        T3CNTH = 0;
        counter = ((ircnt) / 375);

    }
    else
    {
        T3CON &= ~BIT(7);
        irda_state = 0;
        return;
    }


    if (counter == 1)
    {
        irda_data >>= 1;
        irda_state++;
        goto _exit_timer2;
    }
    else if (counter == 2)
    {
        irda_data >>= 1;
        irda_state++;
        irda_data |= 0x8000;
    }
//    else if ((counter == 13) || (counter == 11) || (counter == 96) || ((counter >= 31) && (counter <= 49)))
//    {
//        goto _exit2_timer2;
//    }
    else if ((counter == 13) || (counter < 9) || (counter > 96))
    {
        irda_state = 0;
    }
_exit_timer2:
    if (irda_state == 16)
    {
        user_code = irda_data;
    }
}
#endif


