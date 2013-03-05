#ifndef _ENCODE_H_
#define _ENCODE_H_

#include "config.h"



#ifdef __C51__


enum
{
    RECODE_STOP  = 0,    ///<δ¼��״̬
    RECODE_PLAY,         ///<����¼���ļ�״̬
    RECODE_INIT,         ///<¼����ʼ��
    RECODE_WORKING,	     ///<����¼��
    RECODE_PAUSE,        ///<¼����ͣ
};

typedef struct _FSAPIMSGREC
{
	u16  firstfilenum ;      //¼��Ŀ¼�����ļ���ʼ��ţ�
	u16  fileTotalInDir ;     //¼��Ŀ¼�����ļ���Ŀ��
}FSAPIMSGREC;

extern u8 _xdata encode_status;
extern u8 _xdata encode_channel;
extern u8 _xdata encode_vol;
extern u8 _xdata encode_device;
extern FSAPIMSGREC _pdata fs_msg_rec;

extern u16 _xdata encode_fristfile;
extern u16 _xdata encode_filenum;
extern u16 _xdata logic_fileTotal;

extern u8 encode_cnt;
extern u8 mem_addr;

extern u8 play_mode_rec;

#define TRACK_ALL    0 
#define TRACK_RIGHT  1 
#define TRACK_LEFT   2

#define REC_FM     		0x00 
#define REC_LINEIN 		0x01
#define REC_MIC			0x02
#define REC_DAC			0x03 

#define ENABLE_REC_DATA 0x81
#define REC_NO_OPT      0x80

#define ENABLE_REC_BIT  BIT(7)
#define FRIST_ADC_PACKET  BIT(3)

extern void break_encode(void);
extern void rec_mic_fun(void);
extern void get_rec_mem_info(void);
extern  u16 filenum_phy_logic(u16 filenumber);
extern u16 filenum_logic_phy(u16 filenumber);
extern void init_rec_name(void);
extern void api_stop_encode(void);
#endif

#endif



