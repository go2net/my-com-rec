/*--------------------------------------------------------------------------*/
/**@file     rtc_operation.c
   @brief    RTC�㷨���ܺ���
   @details
   @author
   @date   2011-4-26
   @note
*/
/*----------------------------------------------------------------------------*/

#include "rtc_operation.h"

/*******************************************************
				CONST
********************************************************/
//const u16 year_tab[]={365,366};
u8 _code month_tab1[] = {31,28,31,30,31,30,31,31,30,31,30,31};		   ///<������ÿ�µ�����
u8 _code month_tab2[] = {31,29,31,30,31,30,31,31,30,31,30,31};		   ///<����ÿ�µ�����

//                         1  2  3  4   5   6   7   8   9   10  11  12
u16 _code smonth_tab1[]={0,31,59,90,120,151,181,212,243,273,304,334,365};	   ///<������ĵ����ۼ�����
u16 _code smonth_tab2[]={0,31,60,91,121,152,182,213,244,274,305,335,366};	   ///<	����ĵ����ۼ�����

//char calendar[][10]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


/*----------------------------------------------------------------------------*/
/**@brief	�ж�����
   @param 	year:���
   @return  ���
   @note	bool leapyear(u16 year)
*/
/*----------------------------------------------------------------------------*/
bool leapyear(u16 year)
{
    if ((year%4==0 && year%100!=0)||(year%400==0))
        return TRUE;
    else
        return FALSE;
}
/*----------------------------------------------------------------------------*/
/**@brief	����������Ϊ���ڵ�����
   @param 	day��������
   @return  ���ڵ�����
   @note	u8 day_to_weekday(u16 day)
*/
/*----------------------------------------------------------------------------*/
u8 day_to_weekday(u16 day)
{
    u16 tmp;
    u8 weekday;

    tmp = day + DATE;
    weekday = tmp % 7;

    if (tmp < 7)
        return tmp;
    else if (weekday)
        return (tmp % 7);
    else
        return 7;
}
/*----------------------------------------------------------------------------*/
/**@brief	��ݻ���Ϊ����
   @param 	day��������
   @return  ���ڵ�����
   @note	u16 year_to_day(u16 year)
*/
/*----------------------------------------------------------------------------*/
u16 year_to_day(u16 year)
{
    if (leapyear(year))
        return 366;
    else
        return 365;
}
/*----------------------------------------------------------------------------*/
/**@brief ���µ�����
   @param 	nmonth�������·ݣ�nyear���������
   @return  ��������
   @note u8 nowmonth(u8 nmonth,u16 nyear)
*/
/*----------------------------------------------------------------------------*/
u8 nowmonth(u8 nmonth,u16 nyear)
{
    if (leapyear(nyear))
        return month_tab2[nmonth-1];
    else
        return month_tab1[nmonth-1];

}
/*----------------------------------------------------------------------------*/
/**@brief	�·ݻ���Ϊ����
   @param 	day��������
   @return  ���ڵ�����
   @note	u8 month_to_day(u8 month)
*/
/*----------------------------------------------------------------------------*/
u16 month_to_day(u16 year,u8 month)
{
    if (leapyear(year))
        return smonth_tab2[month];
    else
        return smonth_tab1[month];
}
/*----------------------------------------------------------------------------*/
/**@brief	����������Ϊ���/�·�/����
   @param 	day����������time:��ǰ����
   @return  ���ڵ�����
   @note	void day_to_ymd(u16 day,RTC_TIME *rtc_time)
*/
/*----------------------------------------------------------------------------*/
void day_to_ymd(u16 day,RTC_TIME *rtc_time)
{
    u8 tmp;

    rtc_time->weekday = day_to_weekday(day);

    tmp = 0;
    while (day >= year_to_day(YEAR+tmp))
    {
        day -= year_to_day(YEAR+tmp);
        tmp++;
    }
    rtc_time->year = YEAR+tmp;

    tmp = 0;
    while (day >= month_to_day(rtc_time->year,MONTH+tmp))
    {
        tmp++;
    }
    day -= month_to_day(rtc_time->year,MONTH+tmp-1);
    rtc_time->month = MONTH+tmp;

    rtc_time->day = DAY+day;
}

/*----------------------------------------------------------------------------*/
/**@brief	��ǰ���/�·�/���ڻ����������
   @param 	time:��ǰ����
   @return  ���ڵ�����
   @note	u16 ymd_to_day(RTC_TIME *time,u16 day)
*/
/*----------------------------------------------------------------------------*/
u16 ymd_to_day(RTC_TIME *time)
{
    u16 _xdata tmp_year;
    u16 _xdata tmp_day = 0;

    for (tmp_year=YEAR;tmp_year<time->year;tmp_year++)			//��->�գ����겻�����ڣ�������<
    {
        tmp_day += year_to_day(tmp_year);
    }

    if (leapyear(time->year))						//��->��
        tmp_day += smonth_tab2[time->month-1];
    else
        tmp_day += smonth_tab1[time->month-1];

    tmp_day += (time->day-1);						//��->��,���ղ������ڣ�������Ӧ�ü�1
    return tmp_day;
}