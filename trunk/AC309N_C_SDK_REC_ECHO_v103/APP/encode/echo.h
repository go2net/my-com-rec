#ifndef _ECHO_H_
#define _ECHO_H_

#include "config.h"

#ifdef __C51__


typedef struct __ENCODE_MSG
{
    u16 fileindex;          //�ļ���
    u8 	channle;       //¼��ͨ����ѡ�� 
	u8 	vol;
	u8 	track ;
	u8 	_xdata *bADbuf1;		///<ADC Dual Buffer -1
	u8 	_xdata *bADbuf2;		///<ADC Dual Buffer -2
	u8 	state;				///<ѹ��״̬��
	u8 	gr;					///<���ȼ�����
	u8 	wavparkgenum;		///<һ��AD�������ṩ���������ݰ�32��n
    u8  echo;
}ENCODE_MSG;


void set_echo(u8 strong, u8 deep);
bool app_echo_set(u8 channl, u8 vol);


bool start_encode_echo(u8 IS_MP3);
bool start_encode(u8 IS_MP3);

void echo_enable(void);
void echo_sw(void);
bool echo_deep(u8 ctl);
bool echo_strong(u8 ctl);
void echo_vol_set(u8 vol);

extern ENCODE_MSG _xdata * encode_msg ;

#endif ///< #ifdef __C51__


#endif ///< #ifndef _ECHO_H_