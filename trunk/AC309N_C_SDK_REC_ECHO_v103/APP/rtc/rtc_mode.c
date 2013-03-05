/*--------------------------------------------------------------------------*/
/**@file    rtc_mode.c
   @brief   RTC����ģ��
   @details
   @author
   @date   2011-7-4
   @note
*/
/*----------------------------------------------------------------------------*/
#include "rtc_mode.h"
#include "eq.h"
#if RTC_ENABLE
extern u8 _xdata all_alm_sw;

extern bool input_number_en;
extern  u8 main_menu, cur_menu, main_menu_conter;
extern u16 input_number;
extern u8 work_mode;
extern u8 _idata last_work_mode;
extern u8 _xdata alm_cnt;

extern RTC_TIME _xdata curr_time;
extern ALM_TIME _xdata alarm;
extern bool vol_change_en;
extern bool key_voice_en;

//extern DECODER_MSG _xdata *dec_msg;
//extern u8 eq_mode;

u8 _xdata rtc_mode_setting;				 ///<RTC ʱ��/���� ����ģʽ���
u8 _xdata rtc_coordinate;				 ///<RTC ʱ����淴ɫ����
u8 _xdata alm_coordinate;				 ///<RTC ���ӽ��淴ɫ����
bool alm_on_flag;		    			 ///<RTC ���ӱ��λ
/*----------------------------------------------------------------------------*/
/**@brief RTCģʽ��ѭ��
   @param 	void
   @return  void
   @note  void deal_rtc(void)
*/
/*----------------------------------------------------------------------------*/
void deal_rtc(void)
{
    u8 key;
    u8 rtc_set_cnt;
    while (1)
    {
        key = app_get_msg();

        //printf("IRTCON %02x",(u16)IRTCON);

        if (alm_on_flag)
        {
            key = alm_msg_convert(key);
        }
        switch (key)
        {
        case MSG_CHANGE_WORK_MODE:
            return;

        case MSG_MUSIC_NEW_DEVICE_IN:							//�����豸����
            work_mode = MUSIC_MODE;
            return;

        case MSG_RTC_SETTING:
            rtc_coordinate = 0;
            alm_coordinate = 0;
            rtc_mode_setting ++;
            if (rtc_mode_setting > ALARM_SETTING)
            {
                rtc_mode_setting = RTC_DISPLAY;
            }
            if ((rtc_mode_setting == RTC_DISPLAY)||(rtc_mode_setting == RTC_SETTING))
            {
                rtc_set_cnt=0;
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                disp_port(MENU_ALM_SET);
            }
            break;

        case MSG_RTC_NEXT:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_coordinate++;
                if (rtc_coordinate > 5)
                {
                    rtc_coordinate = 0;
                }
                rtc_set_cnt=0;
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                alm_coordinate++;
                //if(alarm[0].sw)
                //{
                //	if(alm_coordinate > 9)
                //	{
                //		alm_coordinate = 0;
                //	}
                //}
                //else
                //{
                if (alm_coordinate > 2)
                {
                    alm_coordinate = 0;
                }
                //}
                disp_port(MENU_ALM_SET);
            }
            break;
        case MSG_RTC_PREV:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_coordinate--;
                if (rtc_coordinate == 255)
                {
                    rtc_coordinate = 5;
                }
                rtc_set_cnt=0;
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                alm_coordinate--;
                if (alm_coordinate == 255)
                {
                    //if(alarm[0].sw)
                    //{
                    //	alm_coordinate = 9;
                    //}
                    //else
                    //{
                    alm_coordinate = 2;
                    //}
                }
                disp_port(MENU_ALM_SET);
            }
            break;
        case MSG_RTC_PLUS:
        case MSG_RTC_PLUS_HOLD:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_set_cnt=0;
                curr_time_plus();
                write_rtc(&curr_time);
                write_next_alm_sec();
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                alm_time_plus();
                save_alarm_info();
                write_next_alm_sec();
                disp_port(MENU_ALM_SET);
            }
            break;
        case MSG_RTC_MINUS:
        case MSG_RTC_MINUS_HOLD:
            if (rtc_mode_setting == RTC_SETTING)
            {
                rtc_set_cnt=0;
                curr_time_minus();
                write_rtc(&curr_time);
                write_next_alm_sec();
                disp_port(MENU_RTC);
            }
            if (rtc_mode_setting == ALARM_SETTING)
            {
                alm_time_minus();
                save_alarm_info();
                write_next_alm_sec();
                disp_port(MENU_ALM_SET);
            }
            break;

        case MSG_HALF_SECOND:

            if (main_menu_conter < SUB_MENU_TIME*4)
            {
                main_menu_conter++;
            }
            else if (cur_menu != main_menu)
            {
                rtc_mode_setting = RTC_DISPLAY;
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }

            if (rtc_mode_setting == RTC_SETTING)
                rtc_set_cnt++;

            if ((rtc_set_cnt==8)&&(rtc_mode_setting == RTC_SETTING))
            {
                rtc_set_cnt=0;
                rtc_mode_setting = RTC_DISPLAY;
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }

            if (cur_menu == MENU_RTC)
            {
                read_rtc(&curr_time);
                chk_date_err();
                disp_port(MENU_RTC);
            }
            break;

        case MSG_ALM_ON:
            write_next_alm_sec();
            alm_on_flag = 1;
            alarm_on_mode();
            break;

        default:
            ap_handle_hotkey(key);
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief RTCģʽ���
   @param 	void
   @return  void
   @note  void rtc_fun(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_fun(void)
{

    input_number_en = 0;
    vol_change_en=0;
    key_voice_en=1;
    main_menu = MENU_RTC;

    dsp_set_eq_mode(0);			  //ϵͳʱ��divǰ��ر�eq
    sys_clk_div(4);//SYSTEM_CLK_DIV4();
    key_table_sel(0);
    flush_all_msg();
	set_max_vol(MAX_ANOLOG_VOL,MAX_DIGITAL_VOL);///�����������
    dac_out_select(DAC_MUSIC, 0);
//	curr_time_setting();
//	rtc_init();
    rtc_mode_setting = RTC_DISPLAY;
    rtc_coordinate = 0;
    alm_coordinate = 0;
    if (alm_cnt)
    {
        put_msg_lifo(MSG_ALM_ON);
    }
    else
    {
        read_rtc(&curr_time);
        chk_date_err();
        disp_port(MENU_RTC);
    }

    deal_rtc();
    delay_10ms(3);
    key_voice_en=0;
    main_vol_set(0, CHANGE_VOL_NO_MEM);
}
#endif