/*--------------------------------------------------------------------------*/
/**@file   my_printf.c
   @brief    ��ʽ�����
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "my_printf.h"
#include "config.h"
#if (NO_DISP != monitor)

extern void led_putchar(u8 chardata,u8 loc);
u8 _xdata aa[4];
/*----------------------------------------------------------------------------*/
/**@brief    ��ʾ�ַ���
   @param	 * str���ַ�����ַ ��loc:����λ��
   @return	 ��
   @note     void printf_str(u8 *str,u8 loc)
*/
/*----------------------------------------------------------------------------*/
void printf_str(u8 *str,u8 loc)
{
    u8 c;
    while (1)
    {
        c = *str++;
        if (c == '\0')
            break;
        led_putchar(c,loc++);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    ����ת��
   @param	 dat��ת������
   @return	 ��
   @note     void number_ascii(u16 dat)
*/
/*----------------------------------------------------------------------------*/
void number_ascii(u16 dat)
{
    aa[0] = dat%10 + '0';
    aa[1] = (dat/10)%10 + '0';
    aa[2] = (dat/100)%10 + '0';
    aa[3] = (dat/1000)%10 + '0';
}

/*----------------------------------------------------------------------------*/
/**@brief    ������ʾ
   @param	 dat��ת�����֣�loc�����ֿ�ʼλ�� ��len�����ֳ���
   @return	 ��
   @note     void number_ascii(u16 dat)
*/
/*----------------------------------------------------------------------------*/
void printf_num(u16 dat,u8 loc,u8 len)
{
    if((!len) || (len>4))
    {
        return;
    }
    number_ascii(dat);
    do
    {
        led_putchar(aa[--len],loc++);
    }
    while(len);
}

#endif
