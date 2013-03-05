/*--------------------------------------------------------------------------*/
/**@file     rtc_api.c
   @brief    RTC�ӿں���
   @details
   @author
   @date   2011-4-27
   @note
*/
/*----------------------------------------------------------------------------*/
#include "uart.h"
#include "msgfor_usb.h"
#include "dac.h"
#include "eq.h"
#if RTC_ENABLE

#include "rtc_api.h"

RTC_TIME _xdata curr_time;
ALM_TIME _xdata alarm;
u8 _xdata alm_cnt;

extern u8 work_mode;
extern u8 _idata last_work_mode;
extern bool input_number_en;
extern bool eq_change_en;
extern bool key_voice_en;
extern bool play_mode_change_en;

extern u8 given_device;
extern u16 given_file_number;
extern u8 given_file_method;
extern u8 eq_mode;
extern u8 play_mode;
extern u8  main_menu, cur_menu, main_menu_conter;
extern bool alm_on_flag;
extern void write_next_alm_sec(void);

/*----------------------------------------------------------------------------*/
/**@brief дIRTC
   @param 	cmd��дָ�� w_time:д������
   @return  void
   @note  void write_irtc(u8 cmd,RTC_TIME *w_time)
*/
/*----------------------------------------------------------------------------*/
void write_irtc(u8 cmd,RTC_TIME *w_time)
{
    u8 _xdata buf;
    u16 _xdata w_day;
    IRTC_CSEN;
    irtc_sr_byte(cmd);

    w_day = ymd_to_day(w_time);
    buf = ((u8 *)(&w_day))[0];
    irtc_sr_byte(buf);
    buf = ((u8 *)(&w_day))[1];
    irtc_sr_byte(buf);

    buf = w_time->hour;
    irtc_sr_byte(buf);

    buf = w_time->min;
    irtc_sr_byte(buf);

    buf = w_time->sec;
    irtc_sr_byte(buf);

    IRTC_CSDIS;
}
/*----------------------------------------------------------------------------*/
/**@brief ��IRTC
   @param 	cmd����ָ�� r_time������������
   @return  void
   @note  void read_irtc(u8 cmd,RTC_TIME *r_time)
*/
/*----------------------------------------------------------------------------*/
void read_irtc(u8 cmd,RTC_TIME *r_time)
{
    u16 r_day;

    IRTC_CSEN;
    irtc_sr_byte(cmd);

    ((u8 *)(&r_day))[0] = irtc_sr_byte(0x0);
    ((u8 *)(&r_day))[1] = irtc_sr_byte(0x0);

    day_to_ymd(r_day,r_time);
    r_time->hour = irtc_sr_byte(0x0);
    r_time->min = irtc_sr_byte(0x0);
    r_time->sec = irtc_sr_byte(0x0);


    IRTC_CSDIS;
}
/*----------------------------------------------------------------------------*/
/**@brief дRTC
   @param 	void
   @return  void
   @note  void write_rtc(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void write_rtc(RTC_TIME *curr_time)
{
    write_irtc(WRITE_RTC_SEC,curr_time);
}
/*----------------------------------------------------------------------------*/
/**@brief ��RTC
   @param 	void
   @return  void
   @note  void read_rtc(RTC_TIME *curr_time)
*/
/*----------------------------------------------------------------------------*/
void read_rtc(RTC_TIME *curr_time)
{
    read_irtc(READ_RTC_SEC,curr_time);
}
/*----------------------------------------------------------------------------*/
/**@brief дALM
   @param 	void
   @return  void
   @note  void write_alm(RTC_TIME *w_alm)
*/
/*----------------------------------------------------------------------------*/
void write_alm(RTC_TIME *curr_time_alm)
{
    write_irtc(WRITE_RTC_ALM,curr_time_alm);
}
/*----------------------------------------------------------------------------*/
/**@brief �����RTC RAM���
   @param 	void
   @return  void
   @note  void reset_rtc_ram(void)
*/
/*----------------------------------------------------------------------------*/
void reset_rtc_ram(void)
{
    u8 i;
    for (i = 0; i < 64; i++)
    {
        write_rtc_ram(i, 0);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief ��ALM
   @param 	void
   @return  void
   @note  void read_alm(RTC_TIME *r_alm)
*/
/*----------------------------------------------------------------------------*/
void read_alm(RTC_TIME *curr_time_alm)
{
    read_irtc(READ_RTC_ALM,curr_time_alm);
}
/*----------------------------------------------------------------------------*/
/**@brief	����ALM
   @param 	flag��1�������ӣ�0���ر�����
   @return  void
   @note  void alm_sw(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void alm_sw(u8 flag)
{
    u8 rtc_reg;
    rtc_reg = read_rtc_reg();
    if (flag)
    {
        write_rtc_reg(rtc_reg|BIT(2));
    }
    else
    {
        write_rtc_reg(rtc_reg&~BIT(2));
    }
}
/*----------------------------------------------------------------------------*/
/**@brief ���ALM
   @param 	void
   @return  void
   @note  void alm_check(void)
*/
/*----------------------------------------------------------------------------*/
void alm_check(void)
{
    if (IRTCON & BIT(7))
    {
        //printf("RTC CON:%u\n",(u16)read_rtc_reg());
        alm_cnt = 1;
        put_msg_lifo(MSG_ALM_ON);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief ����RTC Power On
   @param 	sw ��Դ����
   @return  void
   @note  void set_rtc_power(u8 sw)
*/
/*----------------------------------------------------------------------------*/
void set_rtc_power(u8 sw)
{
    u8 rtc_reg;
    rtc_reg = read_rtc_reg();
    if (sw)
    {
        write_rtc_reg(rtc_reg|BIT(3));
    }
    else
    {
        write_rtc_reg(rtc_reg&~BIT(3));
    }
}

/*----------------------------------------------------------------------------*/
/**@brief ������һ�����ӣ���д��IRTC
   @param 	void
   @return  void
   @note  void set_next_alm_sec(void)
*/
/*----------------------------------------------------------------------------*/
void write_next_alm_sec(void)
{
    u8 i;
    RTC_TIME alm_sec;

    if (alarm.sw)
    {
        read_rtc(&curr_time);
        for (i = 0;i < sizeof(RTC_TIME);i++)
        {
            ((u8 *)(&alm_sec))[i] = ((u8 *)(&curr_time))[i];
        }
        alm_sec.sec = 0;

        alm_sec.hour = alarm.hour;
        alm_sec.min = alarm.min;
        if ((alarm.hour < curr_time.hour)||((alarm.hour == curr_time.hour)&&(alarm.min <= curr_time.min)))
            alm_sec.day += 1;
        //Attention��������û����Ч��������ʱ��д���������ʱ��
        write_alm(&alm_sec);
//		read_alm(&alm_sec);
//		printf("Next alarm:%u/%u/%u %u:%u\n",alm_sec.year,(u16)alm_sec.month,(u16)alm_sec.day,(u16)alm_sec.hour,(u16)alm_sec.min);
    }
}
/*----------------------------------------------------------------------------*/
/**@brief ��ǰʱ�临λ��2000/1/1 0:0:0
   @param 	void
   @return  void
   @note  void rtc_reset(void)
*/
/*----------------------------------------------------------------------------*/
void rtc_reset(void)
{
    curr_time.year	= 2000;
    curr_time.month = 1;
    curr_time.day = 1;
    curr_time.hour = 0;
    curr_time.min = 0;
    curr_time.sec = 0;

    write_rtc(&curr_time);
    write_next_alm_sec();
}
/*----------------------------------------------------------------------------*/
/**@brief ���ڳ���У��
   @param 	void
   @return  void
   @note void chk_date_err(void)
*/
/*----------------------------------------------------------------------------*/
void chk_date_err(void)
{
    if (curr_time.year>2178)
    {
        rtc_reset();
    }
}
/*----------------------------------------------------------------------------*/
/**@brief �������������Ϣ���洢����EEPROM/RAM��
   @param 	void
   @return  void
   @note  void save_alarm_info(void)
*/
/*----------------------------------------------------------------------------*/
void save_alarm_info(void)
{
    write_info(MEM_ALARM_0_HOUR , alarm.hour);
    write_info(MEM_ALARM_0_MIN , alarm.min);

    alm_sw(alarm.sw);//alm_sw(all_alm_sw);
}
/*----------------------------------------------------------------------------*/
/**@brief ��ȡ����������Ϣ���洢����EEPROM/RAM��
   @param 	void
   @return  void
   @note  void load_alarm_info(void)
*/
/*----------------------------------------------------------------------------*/
void load_alarm_info(void)
{
    alarm.hour = read_info(MEM_ALARM_0_HOUR );
    if (alarm.hour>23)
    {
        alarm.hour = 12;
    }
    alarm.min = read_info(MEM_ALARM_0_MIN );
    if (alarm.min>59)
    {
        alarm.min = 0;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief �ر�����
   @param 	void
   @return  void
   @note  void close_alarm(void)
*/
/*----------------------------------------------------------------------------*/
void close_alarm(void)
{
    alm_cnt = 0;
    alm_on_flag = 0;
    //set_eq(0);
    key_voice_en = 1;
    //disp_port(main_menu);
}
/*----------------------------------------------------------------------------*/
/**@brief ��������
   @param 	void
   @return  ����30��������־λ
   @note  bool alarm_on(void)
*/
/*----------------------------------------------------------------------------*/
bool alarm_on(void)
{
    if (alm_cnt >= 60)
    {
        return 0;
    }
    else if (alm_cnt)
    {
        alm_cnt++;
        alarm_tone();
        disp_port(MENU_ALM_UP);
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/**@brief ��������ģʽѭ��
   @param 	void
   @return  void
   @note  void alarm_on_mode(void)
*/
/*----------------------------------------------------------------------------*/
void alarm_on_mode(void)
{
    //write_next_alm_sec();
    key_voice_en = 0;

    main_vol_set(0, SET_USE_CURRENT_VOL | CHANGE_VOL_NO_PEND);
}
/*----------------------------------------------------------------------------*/
/**@brief ��������ʱ����Ϣ����
   @param 	key��ϵͳ��Ϣ
   @return  ת����������Ӧ����Ϣ
   @note  u8 alm_msg_convert(u8 key)
*/
/*----------------------------------------------------------------------------*/
u8 alm_msg_convert(u8 key)
{
    switch (key)
    {
    case MSG_HALF_SECOND:
        if (alarm_on())
        {
            break;
        }
    case MSG_MUSIC_PP:
        work_mode = last_work_mode;
        put_msg_lifo(MSG_CHANGE_WORK_MODE);
        close_alarm();
        break;


    case MSG_USB_PC_IN:
    case MSG_AUX_IN :
    case MSG_SDMMC_IN :
    case MSG_USB_DISK_IN  :
        close_alarm();
        return key;

    default:
        return NO_MSG;
    }
    return NO_MSG;
}
/*----------------------------------------------------------------------------*/
/**@brief RTC��ʼ��
   @param 	void
   @return  void
   @note  void rtc_init(void)
*/
/*----------------------------------------------------------------------------*/
bool rtc_init(void)
{
    u8 rtc_reg;
    u8 alm_wkup = 0;


    alarm.sw = 0;

    rtc_reg = read_rtc_reg();
    if (rtc_reg & BIT(7))					//����Ƿ����
    {
        rtc_reg &= ~BIT(7); 				//����PDFLAG
        rtc_reset();
#if USE_RTC_RAM
        reset_rtc_ram();
#endif
    }
    else
    {
        if (rtc_reg & BIT(2))
        {
            alarm.sw	= 1;
        }
        if (IRTCON & BIT(7))
        {
            alm_wkup = 1;
            alm_cnt = 1;
            last_work_mode = RTC_MODE;
        }
    }
    load_alarm_info();
    alm_sw(alarm.sw);		//alm_sw(all_alm_sw);				 //���ӿ���
    read_rtc(&curr_time);
    chk_date_err();
    write_next_alm_sec();
    write_rtc_reg(rtc_reg);
    return alm_wkup;
}
#endif