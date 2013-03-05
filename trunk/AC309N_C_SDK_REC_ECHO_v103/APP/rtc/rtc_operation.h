/*--------------------------------------------------------------------------*/
/**@file     rtc_operation.h
   @brief    RTC�㷨���ܺ���
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef	_RTC_OPERATION_H_
#define _RTC_OPERATION_H_

#include "typedef.h"

#ifdef __C51__
/*******************************************************
				TYPEDEF
********************************************************/

typedef struct _RTC_TIME
{
    u16 year;		///<���
    u8 month;		///<�·�
    u8 day;			///<����
    u8 hour;		///<ʱ
    u8 min;			///<��
    u8 sec;			///<��
    u8 weekday;		///<���ڼ�
}
RTC_TIME;

typedef struct _ALM_TIME
{
    u8 hour;		///<ʱ
    u8 min;			///<��
//	u8 days;		///<�����ӵ���Ч���ڣ�һ�������ĳ���죩
    u8 sw;		///<���ӿ���
}
ALM_TIME;
/*******************************************************
				MARCO
********************************************************/
#define TRUE 1
#define FALSE 0

#define	ONEDAY (24*60*60)UL	//86400
#define ONEHOUR (60*60)		//3600
#define ONEMIN	60

#define YEAR 2000
#define MONTH 1
#define DAY 1
#define HOUR 0
#define MINUTES 0
#define SECOND 0

#define DATE 6

u8 nowmonth(u8 nmonth,u16 nyear);
void day_to_ymd(u16 day,RTC_TIME *rtc_time);
u16 ymd_to_day(RTC_TIME *time);
#endif


#endif