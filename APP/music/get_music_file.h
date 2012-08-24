/*--------------------------------------------------------------------------*/
/**@file   get_music_file.h
   @brief  ��ȡ�ļ�ͷ�ļ�
   @details
   @author
   @date   2011-9-8
   @note
*/
/*----------------------------------------------------------------------------*/

#ifndef  _MSGFOR_MP3_
#define  _MSGFOR_MP3_

#ifdef __C51__
#include "config.h"

enum
{
    GET_FILE_OK = 0,			        //�ҵ��ļ����
    GET_DEVICE_END,						//�Ѿ����ŵ��豸����
    GET_DEVICE_HEAD						//�Ѿ����ŵ��豸��ͷ
};

u8 fs_get_filenum(u8 playmode, u8 searchMode);
#endif

#define GET_NEXT_FILE       0
#define GET_PREV_FILE       1
#define GET_PLAY_FILE       2


#endif