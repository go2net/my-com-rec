/*--------------------------------------------------------------------------*/
/**@file    DEVICE.h
   @brief   �豸���ƽӿ�
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __C51__
#include "config.h"

u8 find_device(u8);
u8 device_init(void);
void write_file_info(u8);

/*----------------------------------------------------------------------------*/
/**@brief   ��⵱ǰ����豸
   @param   ��
   @return  0����ǰ����豸�����ߣ���������ǰ����豸
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void);

enum
{
    NO_DEVICE = 0,
    DEVICE_SDMMC0 = 1,
    //DEVICE_SDMMC1,
    DEVICE_UDISK = 2,
    DEVICE_SDMMC0_REC = 0x41,
    DEVICE_UDISK_REC = 0x42,
    DEVICE_AUTO_NEXT = 0x81,
    DEVICE_AUTO_PREV = 0x82,
    MAX_PLAY_DEVICE = 2,

};

enum
{
    FIND_DEV_OK      = 0,				//�ɹ��ҵ��豸
    DEFINE_DEV_WKING,					//ָ���豸�Ѿ���ѡ��,���ڲ���
    ONLY_ONE_DEVICE,  					//ֻ��һ���豸,���Ѿ�ѡ�У��޷�ѡ����һ���豸
    NO_DEFINE_DEV,    					//ָ���豸δ�ҵ�
    DEV_INIT_ERR,     					//�ҵ��豸������ʼ��ʧ��
    NO_EFFECTIVE_DEV,					//����Ч����ʹ�õ��豸
    NO_DEV_ONLINE,    					//�������豸
};
#endif


/////

#define VIRTUAL_DEVICE  (DEVICE_SDMMC0_REC & (~DEVICE_SDMMC0))


#if VIRTUAL_ENABLE
    #define MAX_DEVICE 4
#else
    #define MAX_DEVICE 2
#endif
#endif