/*


*/
#include "device.h"
#include "uart.h"

extern DECODER_MSG _xdata *dec_msg;
extern u8 _xdata decode_buffer[];
extern u8 given_device;
extern u8 given_file_method;
extern u16 break_point_filenum;
extern u8 _xdata win_buffer[512];
extern u8 _code one_table[];
extern void stop_decode(void);
extern FSAPIMSG _pdata fs_msg;
extern FIL xdata fat_ptr1;

extern DISK_MUSIC_POINT _idata	disk_mus_point[];

u8 _bdata device_online;			    ///<�豸���߱��
sbit sdmmc_connect = device_online^0;   ///<SD������״̬��ǼĴ�����1:���� 0��������
sbit udisk_connect = device_online^1;   ///<USB MASS storage����״̬��ǼĴ�����1:���� 0��������
sbit pc_connect = device_online^4;      ///<PC����״̬��ǼĴ�����1:���� 0��������
u8 device_active;                       ///<��ǰ���߻�豸
u8 const _code file_type[] = "MP1MP2MP3WMAWAV";  ///<�����ļ���ʽ

#if VIRTUAL_ENABLE
u8 _code  device_tab[4] = 
{
    DEVICE_SDMMC0,
    DEVICE_SDMMC0_REC,
    DEVICE_UDISK,
    DEVICE_UDISK_REC,
};
#else
u8 _code  device_tab[2] = 
{
    DEVICE_SDMMC0,
    DEVICE_UDISK,
};
#endif

u8 get_device_cnt(u8 dev)
{
    u8 i;
    for(i = 0;i < sizeof(device_tab);i++)
    {
        if(dev == device_tab[i])
        {
            return i;
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/**@brief   ��⵱ǰ����豸
   @param   ��
   @return  0����ǰ����豸�����ߣ���������ǰ����豸
   @note    u8 device_check(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_check(void)
{
    device_online = get_device_online_status();
    return device_active & device_online;
}


/*----------------------------------------------------------------------------*/
/**@brief   �豸��ʼ��
   @param   ��
   @return  0���ҵ���Ч˭����������û���ҵ���Ч�豸
   @note    u8 device_init(void)
*/
/*----------------------------------------------------------------------------*/
u8 device_init(void)
{
    u8 sector_sizeof512 = 1;
    device_check();
    if (device_active & device_online)  ///<��ǰ��Ҫ����豸����
    {
        disp_port(MENU_SCAN_DISK);

        stop_decode();
//        deg_str("device init\n");
        fs_fun_init();

        if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
        {
            if (init_sd())                  ///<sd ������
            {
                f_init(win_buffer, (u16)sdmmc_read, 1);//get_usb_device_pkt_size());    ///<�����ɹ��� ��ʼ���ļ�ϵͳ����
            }
            else
            {
				return 0xff;                       ///<����ʧ��
            }

        }

        else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
        {
            if (usb_host_emuerate_devcie(win_buffer,100))     ///<USB MASS STORAGE ö��
            {
                sector_sizeof512 = get_usb_device_pkt_size();
                f_init(win_buffer, (u16)read_usb, sector_sizeof512);      ///<ö�ٳɹ��� ��ʼ���ļ�ϵͳ����
            }
            else
            {
                return 0xff;             ///<ö��ʧ��
            }
        }

    }
    else
    {
        return 0xff;
    }

//    deg_str("fat init\n");
    //if (!f_mount())                                      ///<�ļ�ϵͳ��ʼ��
    if (!f_mount_bsp(sector_sizeof512))
    {
        
        if((RECODE_INIT == encode_status))
        {
             if(0 == f_write_init(device_active & (~VIRTUAL_DEVICE)))  //��ʼ��д�豸������
             {
                 return 0xfd;
             }
             else
             {
                 return 0;
             }
        }
        fs_ext_setting(file_type);
        {
            u16 break_point;
            get_rec_mem_info();
            if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
            {
                break_point = disk_mus_point[0 + encode_cnt].id0;
            }
            else if ((device_active & (~VIRTUAL_DEVICE) ) == DEVICE_UDISK)
            {
                break_point = disk_mus_point[1 + encode_cnt].id0;
            }
            break_point_filenum = fs_scan_disk(break_point);
    		encode_fristfile = fs_msg_rec.firstfilenum;	  //¼���ļ�����
            encode_filenum = fs_msg_rec.fileTotalInDir;	  //¼���ļ��еĵ�һ���ļ���
            if (break_point_filenum)
            {
                break_point_filenum = filenum_phy_logic(break_point_filenum);
            }
        }
		     




#if VIRTUAL_ENABLE
        logic_fileTotal = fs_msg.fileTotal - encode_filenum;          ///�����ļ�����

        if(device_active & VIRTUAL_DEVICE)
        {
            logic_fileTotal = encode_filenum;	//¼���ļ�����
        }
#else
        logic_fileTotal = fs_msg.fileTotal;
#endif
        
		
        if(0 == logic_fileTotal)//if (fs_msg.fileTotal == 0)
        {
            return 0xfe;
        }

        return 0;
    }
    else
    {
        return 0xff;	//����Ч�豸
    }
}
/*----------------------------------------------------------------------------*/
/**@brief    ����ָ�����豸���Զ�������һ����Ч�豸
   @param    select : 1������SD�豸��2������USB mass storage�豸; 0x81:������һ���豸��0x82:������һ���豸;��������Ч
   @return   0���ɹ����ҵ�һ���豸��1:ָ�����豸û���ҵ���2��ֻ��һ���豸��������һ���豸����һ���豸��Ч;3:�ҵ��豸������ʼ�����ɹ�;4���������豸
   @note     u8 find_device(u8 select)
*/
/*----------------------------------------------------------------------------*/


u8 find_device(u8 select)
{
    u8 i;
    u8 cnt;
    device_check();

    i = one_table[device_online & 0x0f];

    if (i == 0)				//���豸
    {
        device_active = 0;
        return NO_DEV_ONLINE;
    }
    if (select == DEVICE_AUTO_PREV)		//������һ���豸
    {
//        if ((i == 1) && (device_active & device_online))			//��ǰ�豸�Ѿ�ѡ��
//            return ONLY_ONE_DEVICE;

        for (i = 0;i < MAX_DEVICE;i++)
        {
            cnt = get_device_cnt(device_active);
            
            if(0 == cnt)
            {
               cnt = (MAX_DEVICE-1);
            }
            else
            {
                cnt--;
            }
            device_active = device_tab[cnt];	   //�ò��ķ���������һ���豸


            if ((device_active & device_online) == 0)
                continue;

            if (!device_init())             //�ҵ���Ч�豸
                return FIND_DEV_OK;
        }
        device_active = 0;
        return NO_EFFECTIVE_DEV;				//����Ч����ʹ�õ��豸

    }
    else if (select == DEVICE_AUTO_NEXT)    //������һ���豸
    {
        
        for (i = 0;i < MAX_DEVICE;i++)
        {
            cnt = get_device_cnt(device_active);  
            cnt++;
            if(cnt > (MAX_DEVICE-1))
            {
               cnt = 0;
            }
            device_active = device_tab[cnt];		//�ò��ķ���������һ���豸
//            if ((device_active > MAX_PLAY_DEVICE) || (device_active == 0))
//                device_active = DEVICE_UDISK;


            if ((device_active  & device_online) == 0)
            {
                continue;
            }
            if (!device_init())             //�ҵ���Ч�豸
            {
                return FIND_DEV_OK;
            }

        }

        device_active = 0;
        return NO_EFFECTIVE_DEV;							//����Ч����ʹ�õ��豸
    }
    else
    {
		 device_active = select;
        if (select & device_online)
        {

           // device_active = select;
            if (!device_init())
                return FIND_DEV_OK;
            else
            {
              //  device_active = 0;
                return DEV_INIT_ERR;
            }
        }
        else
            return NO_DEFINE_DEV;
    }
}
/*----------------------------------------------------------------------------*/
/**@brief   ��¼�ļ�ID0��ID1��Ϣ��EEPROM
   @param   ��
   @return  ��
   @note    void write_file_info(u8)
*/
/*----------------------------------------------------------------------------*/

void write_file_info(u8 cmd)
{
    u16 id;
    u8 i;
//    u8 encode_cnt;
//    u8 mem_addr;
    if(0 == cmd)
    {
        id = 0;
    }
    else
    {
        id = read_file_id(&fat_ptr1);
    }

    write_info(MEM_ACTIVE_DEV, device_active);

    get_rec_mem_info();
    if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_SDMMC0)
    {
        disk_mus_point[0+encode_cnt].id0 = id;
        disk_mus_point[0+encode_cnt].id1 = 0;
        disk_mus_point[0+encode_cnt].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_SD_PLAYPOINT_ID0+i+mem_addr,((u8 *)(&(disk_mus_point[0+encode_cnt].id0)))[i]);
        }
    }
    else if ((device_active & (~VIRTUAL_DEVICE)) == DEVICE_UDISK)
    {
        disk_mus_point[1 + encode_cnt].id0 = id;
        disk_mus_point[1 + encode_cnt].id1 = 0;
        disk_mus_point[1 + encode_cnt].id2 = 0;
        for (i = 9;i != (-1);i--)
        {
            write_info(MEM_USB_PLAYPOINT_ID0+i+mem_addr,((u8 *)(&(disk_mus_point[1 + encode_cnt].id0)))[i]);
        }
    }
}





