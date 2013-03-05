/*--------------------------------------------------------------------------*/
/**@file    fm_receive.c
   @brief   FM接收任务模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/

#include "fm_rev.h"

#if (FM_MODULE == 1)
#include "disp.h"
#include "key.h"
#include "msgfor_hot.h"
#include "main.h"
#include "fm_api.h"
#include "dac.h"
#include "rtc_api.h"
#include "eq.h"


extern bool input_number_en;
extern u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;

extern u8 fm_addr;
extern u8 _code one_table[];
u16 frequency;                          ///<当前频点
u8 fre_channel; 			///<总台数
u8 total_channel;///<当前频道
extern  bool vol_change_en;
extern u8 eq_mode;
extern u8 _xdata decode_buffer[];


/*----------------------------------------------------------------------------*/
/**@brief 获取全部记录的频道
   @param 	无
   @return  频道总数
   @note  u8 get_total_mem_channel(void)
*/
/*----------------------------------------------------------------------------*/
u8 get_total_mem_channel(void)
{
    u8 i,j;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = read_info(MEM_CHANNL + i);
        total += one_table[j & 0x0f];
        total += one_table[(j >> 4) & 0x0f];
    }

    if (total > MAX_CHANNL)
        total = MAX_CHANNL;

    return total;
}
/*----------------------------------------------------------------------------*/
/**@brief 通过频道获取频点
   @param 	channel：频道
   @return  有效的频点偏移量
   @note  u8 get_fre_via_channle(u8 channel)
*/
/*----------------------------------------------------------------------------*/
u8 get_fre_via_channle(u8 channel)
{
    u8 i,j, k;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = read_info(MEM_CHANNL + i);
        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (total == channel)
                {
                    return i * 8 + k;		 //fre = MIN_FRE + return val
                }
            }
        }

    }
    return 0xff;							//find none
}
/*----------------------------------------------------------------------------*/
/**@brief 根据频点偏移量获取频道
   @param 	channel：频道
   @return  频道
   @note  u8 get_channel_via_fre(u8 fre)
*/
/*----------------------------------------------------------------------------*/
u8 get_channel_via_fre(u8 fre)
{
    u8 i,j, k;
    u8 total;

    total = 0;
    for (i = 0; i < MEM_FM_LEN; i++)
    {
        j = read_info(MEM_CHANNL + i);
        for (k = 0; k < 8; k++)
        {
            if (j & (BIT(k)))
            {
                total++;
                if (fre == (i * 8 + k))
                {
                    return total;		 //return fre index
                }
            }
        }
    }
    return fre_channel;						    //find none
}
/*----------------------------------------------------------------------------*/
/**@brief 根据频点偏移量保存到相应的频点位变量到EEPROM
   @param 	fre：频点偏移量
   @return  无
   @note  void save_fm_point(u8 fre)
*/
/*----------------------------------------------------------------------------*/
void save_fm_point(u8 fre)
{
    u8 i,j, k;

    i = fre / 8;
    k = fre % 8;

    j = read_info(MEM_CHANNL + i) | BIT(k);
    write_info(MEM_CHANNL + i, j);
}
/*----------------------------------------------------------------------------*/
/**@brief 从EEPROM清除所有频点信息
   @param 	无
   @return  无
   @note  void clear_all_fm_point(void)
*/
/*----------------------------------------------------------------------------*/
void clear_all_fm_point(void)
{
    u8 i;

    for (i = MEM_CHANNL; i <= (MEM_CHANNL + MEM_FM_LEN); i++)
    {
        write_info(i ,0);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief 保存频道
   @param 	无
   @return  无
   @note  u8 ch_save(void)
*/
/*----------------------------------------------------------------------------*/
u8 ch_save(void)
{
    u8 i;
    u16 check_frequency;

    for (i = 0; i < total_channel; i++)
    {
        check_frequency = get_fre_via_channle(i) + MIN_FRE;
        if (frequency == check_frequency)
        {
            return 1;
        }
    }
    save_fm_point(frequency - MIN_FRE);
    fre_channel = get_channel_via_fre(frequency - MIN_FRE);
    total_channel = get_total_mem_channel();
    disp_port(main_menu);

    return 0;
}

/*----------------------------------------------------------------------------*/
/**@brief  fm_scan 状态标志
   @param  flag=1 标志了进入搜台状态   flag=0；跳出搜台状态
   @return 无
   @note   void enter_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
void fm_scan_flag(bool flag)
{
    if (flag)
    {
        write_info(MEM_CHAN,fre_channel|0x80);
    }
    else
    {
        write_info(MEM_CHAN,fre_channel&0x7f);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  获取FM任务的信息
   @param  无
   @return 无
   @note   void enter_fm_rev(void)
*/
/*----------------------------------------------------------------------------*/
void enter_fm_rev(void)
{
    frequency = read_info(MEM_FRE);
    if (frequency > (1085-875))
    {
        frequency = MIN_FRE;
    }
    else
    {
        frequency += MIN_FRE;
    }

    total_channel = get_total_mem_channel();
    if (!total_channel)
    {
        total_channel = 1;
    }

    fre_channel=read_info(MEM_CHAN);
    if (fre_channel > 206)					//判断eeprom是否第一次用，是则台号为1;总台数为1
    {
        fre_channel=1;
        total_channel=1;
    }
    else if (!fre_channel)
    {
        fre_channel=1;
    }

    fre_channel = get_channel_via_fre(frequency - MIN_FRE);
    if (0xff == fre_channel)
    {
        fre_channel = 1;
    }
    set_fre(FM_CUR_FRE);
}

/*----------------------------------------------------------------------------*/
/**@brief    全频段搜索
   @param    mode: 0全频段, 1:上一个有效频点， 2:下一个有效频点
   @return   0:未找到频点，1:搜索完成,2:退出FM模式
   @note     u8 scan_fre(u8)
*/
/*----------------------------------------------------------------------------*/
u8 fm_scan(u8 mode)
{
    u8 i;
    u8 key;
    u8 result = 0;
    vol_change_en=0;
    input_number_en = 0;
    amp_mute(1);

    if (mode == 0)
    {
        write_info(MEM_CHAN,0);
        write_info(MEM_FRE,0);
        clear_all_fm_point();
        total_channel = 0;
        fre_channel = 0;
        frequency = MIN_FRE - 1;					//自动搜索从最低的频点开始
    }
    fm_set_ch(4);

   flashled(LED_FAST);

    for (i = 0;i <= (MAX_FRE-MIN_FRE);i++)
    {

        while (1)
        {
            key = app_get_msg();
            if (key == NO_MSG)
                break;

            switch (key)
            {
            case MSG_HALF_SECOND:
		 bmt_hdlr();		
		break;
	     case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
                work_mode = MUSIC_MODE;
                result = 2;
                goto _fm_scan_ret;
            case MSG_AUX_IN :
                work_mode = AUX_MODE;
                result = 2;
                goto _fm_scan_ret;
#if USB_DEVICE_ENABLE
            case MSG_USB_PC_IN:
                work_mode = USB_DEVICE_MODE;
                result = 2;
                goto _fm_scan_ret;
#endif
            case MSG_FM_SCAN_ALL:
                result = 0;
                goto _fm_scan_ret;
            case MSG_ALM_ON:
                result = 3;
                goto _fm_scan_ret;

            default:
                ap_handle_hotkey(key);
                break;
            }
        }

        if (mode ==1)
        {
            frequency--;
        }
        else
        {
            frequency++;
        }
        fm_module_mute(1);
        disp_port(MENU_FM_DISP_FRE);
        if (set_fre(FM_CUR_FRE))							//找到一个台
        {
            fm_module_mute(0);
            if (mode == 0)								//搜索所有电台
            {

                save_fm_point(frequency - MIN_FRE);
                fre_channel = get_channel_via_fre(frequency - MIN_FRE);
                total_channel = get_total_mem_channel();
                disp_port(MENU_FM_FIND_STATION);
                delay_10ms(100);
            }
            else
            {
                save_fm_point(frequency - MIN_FRE);
                fre_channel = get_channel_via_fre(frequency - MIN_FRE);
                total_channel = get_total_mem_channel();

                disp_port(MENU_FM_DISP_FRE);
                result = 1;
                goto _fm_scan_ret;
            }
        }

    }
_fm_scan_ret:
    fm_module_mute(0);
    input_number_en = 1;
    vol_change_en = 1;

    flashled(LED_ON);

    one_wire_ctrl_if(1);	
    amp_mute(0);
	
    return result;
}

/*----------------------------------------------------------------------------*/
/**@brief  FM任务函数
   @param  无
   @return 无
   @note   void fm_rev( void )
*/
/*----------------------------------------------------------------------------*/
void fm_rev( void )
{
    u8 key;

    amp_mute(0);

    while (1)
    {
#if ECHO_ENABLE
        dac_out_select(DAC_AMUX1 | ADD_DEC, 0);  
#else
        dac_out_select(DAC_AMUX1, 0);  
#endif
        key = app_get_msg();

        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//有新设备接入
            work_mode = MUSIC_MODE;
            return;

        case MSG_FM_SCAN_ALL:								//play 长按自动全频搜索

            key = fm_scan(0);
            if (key == 3)
            {
                put_msg_lifo(MSG_ALM_ON);
                break;
            }
            if (key == 2)
                return;
            put_msg_lifo(MSG_FM_NEXT_STATION);
            break;

        case  MSG_FM_SCAN_ALL_DOWN :
            key = fm_scan(1);
            if (key == 3)
            {
                put_msg_lifo(MSG_ALM_ON);
                break;
            }
            if (key == 2)
                return;
            break;

        case  MSG_FM_SCAN_ALL_UP:
            key =fm_scan(2);
            if (key == 3)
            {
                put_msg_lifo(MSG_ALM_ON);
                break;
            }
            if (key == 2)
                return;
            break;

        case MSG_MUSIC_PP:									//play 短按静音
            put_msg_lifo(MSG_MUTE);
            break;

        case MSG_MUTE:
            break;

        case MSG_MUSIC_FR:									//搜索上一个台
            flush_all_msg();
            break;

        case MSG_MUSIC_FF:									//搜索下一个台
            flush_all_msg();
            break;

        case MSG_FM_PREV_STEP:
            set_fre(FM_FRE_DEC);
            fre_channel = get_channel_via_fre(frequency - MIN_FRE);						//查找该频点是否有记忆过
            disp_port(MENU_FM_MAIN);
            write_info(MEM_FRE, frequency-MIN_FRE);
            write_info(MEM_CHAN, fre_channel);
            break;

        case MSG_FM_NEXT_STEP:
            set_fre(FM_FRE_INC);
            fre_channel = get_channel_via_fre(frequency - MIN_FRE);						//查找该频点是否有记忆过
            disp_port(MENU_FM_MAIN);
            write_info(MEM_FRE, frequency-MIN_FRE);
            write_info(MEM_CHAN, fre_channel);
            break;

        case MSG_FM_PREV_STATION:
            if (total_channel == 0)
                break;
            fre_channel -= 2;
        case MSG_FM_NEXT_STATION:
            if (total_channel == 0)
                break;
            fre_channel++;

            if ((fre_channel == 0) || (fre_channel == 0xff))
            {
                fre_channel = total_channel;
            }
            else if (fre_channel > total_channel)
            {
                fre_channel = 1;
            }
            frequency = get_fre_via_channle(fre_channel) + MIN_FRE;				//根据台号找频点
            main_vol_set(0, CHANGE_VOL_NO_MEM);
            set_fre(FM_CUR_FRE);
            main_vol_set(0, SET_USE_CURRENT_VOL);
            disp_port(MENU_FM_CHANNEL);
            write_info(MEM_FRE, frequency-MIN_FRE);
            write_info(MEM_CHAN, fre_channel);
            break;

        case MSG_CH_SET:
            if (cur_menu == MENU_INPUT_NUMBER)			//数字输入模式
            {
                if (input_number <= MAX_CHANNL)							//输入的是台号
                {
                    key = get_fre_via_channle(input_number);
                    if (key != 0xff)
                    {
                        frequency = key + MIN_FRE;
                        fre_channel = input_number;
                        main_vol_set(0, CHANGE_VOL_NO_MEM);
                        set_fre(FM_CUR_FRE);
                        main_vol_set(0, SET_USE_CURRENT_VOL);
                        disp_port(MENU_FM_CHANNEL);
                        //break;
                    }

                }
                else if ((input_number >= MIN_FRE) && (input_number <= MAX_FRE)) //输入的是频点
                {
                    frequency = input_number;
                    fre_channel = get_channel_via_fre(frequency - MIN_FRE);
                    main_vol_set(0, CHANGE_VOL_NO_MEM);
                    set_fre(FM_CUR_FRE);
                    main_vol_set(0, SET_USE_CURRENT_VOL);
                }
            }
            write_info(MEM_FRE, frequency-MIN_FRE);
            write_info(MEM_CHAN, fre_channel);
            disp_port(main_menu);

            break;

        case MSG_CH_SAVE:
            ch_save();
            break;


        case MSG_HALF_SECOND:

		bmt_hdlr();			 

            set_brightness_fade_out();
            if (main_menu_conter < SUB_MENU_TIME)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                put_msg_lifo(MSG_CH_SET);				//跳转至CH_SET消息处理
            }

	     if(cur_menu == main_menu)
	     {
		   disp_port(main_menu);
	     }
            break;


#if RTC_ENABLE
        case MSG_ALM_ON:
            write_next_alm_sec();
            work_mode = RTC_MODE;
            put_msg_lifo(MSG_CHANGE_WORK_MODE);
            break;
#endif

#if KALAOK_FUNCTION
		case MSG_KALAOK:
			work_mode = REC_MIC_MODE;
			return ;
#endif

        default :
            ap_handle_hotkey(key);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief FM模式入口函数
   @param 	无
   @return  无
   @note  void fm_radio(void)
*/
/*----------------------------------------------------------------------------*/
void fm_radio(void)
{
//    printf("enter fm\n");
    one_wire_ctrl_if(1);
    P05_source_select(P05_SEL_OSC1);
    amux_dsp_eq();

    sys_clk_div(2);//SYSTEM_CLK_DIV2();
    if (init_fm_rev())
    {
    }
    else					// no fm module
    {
        work_mode++;
        return;
    }

    input_number_en = 1;
    vol_change_en=1;
    main_menu = MENU_FM_MAIN;
    key_table_sel(1);
    flush_all_msg();
    enter_fm_rev();
    disp_port(MENU_FM_MAIN);
	sys_clk_div(4);//SYSTEM_CLK_DIV4();
    set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///设置最大音量
	dac_out_select(DAC_AMUX1, 0);
    encode_channel = REC_FM; 
#if ECHO_ENABLE
    encode_channel = REC_MIC ;
#endif 
	encode_vol = REC_AMUX_GAIN;
    fm_rev();
    main_vol_set(0, CHANGE_VOL_NO_MEM);
    amp_mute(1);

    fm_rev_powerdown();
    P05_source_select(P05_SEL_IO);
    break_encode();

}

#endif
