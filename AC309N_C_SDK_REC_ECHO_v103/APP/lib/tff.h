#ifndef _FATFS
#define _FATFS

#include "config.h"
#include "diskio.h"

#ifdef __C51__

/* File system API info */
typedef struct _FSAPIMSG
{
    u16     fileCounter;		// �ļ�����,�����ļ�ʱ,���������������ܵ��ļ���
    u16	    fileNumber;			// ��ǰ�ļ����
    u16	    fileTotal;			// �ļ�����
    u16     dirTotal;			// �ļ�������
    u16     fileTotalInDir;     // ��ǰĿ¼�ĸ�����Ч�ļ��ĸ���
    u16     fileTotalOutDir;	// ��ǰĿ¼ǰ���ļ�������Ŀ¼ѭ��ģʽ�£���Ҫ�����������ļ����
    u8	    deepth;				// dir deepth for search
    u16     file_index;
    u16     dir_index;
    u8      fname[12];		    //��ǰ�ļ��Ķ���
    u8      dname[12];		    //��ǰĿ¼�Ķ���
} FSAPIMSG;

/* File object structure */
typedef struct _FIL
{
    u8      flag;
    u32		fptr;				// File R/W pointer
    u32 	curr_clust;			// Current cluster
    u32		curr_sect;			// Current sector
    u32 	org_clust;			// File start cluster
    u32		fsize;				// File size
    u32     seek_size;
    u32     start_clust;		// �����ؿ�ʼ
    u32     end_clust;          // �����ؽ���
    u8      _xdata *buf;
} FIL;

typedef struct _FIL_BACKUP
{
    u8      flag;
    u32		fptr;				// File R/W pointer
    u32 	curr_clust;			// Current cluster
    u32		curr_sect;			// Current sector
} FIL_BACKUP;

enum
{
    SEEK_SET = 0x10,
    SEEK_CUR = 0x20
};
#endif


#endif /* _FATFS */
