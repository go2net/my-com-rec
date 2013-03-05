/*--------------------------------------------------------------------------*/
/**@file    msgfor_hot.h
   @brief   HOT 消息处理
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _MSGFOR_HOT_
#define	_MSGFOR_HOT_

#include "config.h"
#include "key.h"


#ifdef __C51__

/*--------混响配置------------*/
typedef enum
{
    IDLE = 0,       /* 0:   */
    BUSY,           /* 1:   */
};

typedef struct
{
    u8 status;
    u8 vol;
    u16 sample_rate;
}REVERB_CTL;

typedef struct
{
    u8 strong;
    u8 deep;		// 每个实际Secotr的 与512的倍数关系
}APP_REVERB;

#define MAX_REV_STRONG	200
#define MAX_REV_DEEP 	86

void ap_handle_hotkey(u8 msg);
extern APP_REVERB _xdata app_echo;

extern REVERB_CTL _xdata * echo_ptr;		///<混响结构体指针

#endif

#endif