/*--------------------------------------------------------------------------*/
/**@file   dac.h
   @brief  dacͷ�ļ�
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef _DAC_H_
#define _DAC_H_

#include "config.h"

#ifdef __C51__
#define AMUX0_IE		0xCF
#define AMUX1_IE        0x3F
#define AMUX_P2IE_SET(x)		P2IE = x			//���� AMUXͨ��


extern _code u16 digital_vol_tab[];
extern _code u8 analog_vol_tab[];


/*----------------------------------------------------------------------------*/
/**@brief    ��ȡ����������������
   @param    mode��ͨ��
   @return   ��
   @note     u8 get_dac_vol(u8 mode)
*/
/*----------------------------------------------------------------------------*/
u8 get_dac_vol(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    ��DAC
   @param    mode: 0 �����裬 1������
   @return   ��
   @note     void dac_off(u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_off(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC mute���ƺ���
   @param    mute��1��enable mute��0��disable mute
   @param    mode��1��������Ч��0���ڵ���dac_out_select()ʱ��ʱ��Ч
   @return   ��
   @note     void dac_mute_control(u8 mute)
*/
/*----------------------------------------------------------------------------*/
void dac_mute_control(u8 mute,u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC mute״̬�л� mute <->unmute
   @param    ��
   @return   ָ��λ��
   @note     bool dac_mute_toggle(void)
*/
/*----------------------------------------------------------------------------*/
bool dac_mute_toggle(void);
/*----------------------------------------------------------------------------*/
/**@brief    DAC ͨ��ѡ��
   @param    sel��ѡ���ͨ��
   @return   ��
   @note     void dac_channel_sel(u8 sel)
*/
/*----------------------------------------------------------------------------*/
void dac_channel_sel(u8 sel);
/*----------------------------------------------------------------------------*/
/**@brief    DAC ���ͨ��ѡ��
   @param    channel��ѡ���ͨ��
   @param    mode���Ƿ�Ϊ����ģʽ
   @return   ��
   @note     void dac_out_select(u8 channle, u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_out_select(u8 channle, u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    DAC ��ʼ��
   @param    m_vol��������
   @param    mode���Ƿ�Ϊ����ģʽ
   @return   ��
   @note     void dac_init(u8 m_vol)
*/
/*----------------------------------------------------------------------------*/
void dac_init(u8 m_vol);
/*----------------------------------------------------------------------------*/
/**@brief    ��DAC
   @param    mode 0:����VCOMO�� 1����VCOMO
   @return   ��
   @note     void dac_on1(u8 mode)
*/
/*----------------------------------------------------------------------------*/
void dac_on1(u8 mode);
/*----------------------------------------------------------------------------*/
/**@brief    ����������
   @param    vol��������
   @param    mode������ģʽ
   @return   ��
   @note     u8 main_vol_set(u8 vol, u8 mode)
*/
/*----------------------------------------------------------------------------*/
u8 main_vol_set(u8 vol, u8 mode);

/*----------------------------------------------------------------------------*/
/**@brief    ����Mute
   @param    �Ƿ�򿪹���mute
   @return   ��
   @note     void amp_mute(bool mute)
*/
/*----------------------------------------------------------------------------*/
void amp_mute(bool mute);

void one_wire_ctrl_if(u8 pulse_num);

#endif


////u8 main_vol_set(u8 vol, u8 mode)�У�mode˵��
#define CHANGE_VOL_NO_MEM   0
#define CHANGE_VOL_MEM   	1
#define SET_USE_CURRENT_VOL 2
#define CHANGE_VOL_INC      3
#define CHANGE_VOL_DEC      4

#define CHANGE_VOL_PEND     0x10
#define CHANGE_VOL_NO_PEND  0x0

#define TRACK_ALL    0 
#define TRACK_RIGHT  1 
#define TRACK_LEFT   2

#define REC_FM     		0x00 
#define REC_LINEIN 		0x01
#define REC_MIC			0x02 
#define REC_DAC			0x03


//////ͨ��ѡ��
#define DAC_AMUX0			0
#define DAC_AMUX1			1
#define DAC_MUSIC			2
#define DAC_KALAOK			0x80
#define ADD_DEC             0x40

///�������
#define MAX_DIGITAL_VOL 	30
#define MAX_ANOLOG_VOL 		30
#define MAX_MAIN_VOL        30

#endif
