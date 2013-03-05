/*--------------------------------------------------------------------------*/
/**@file   clock.c
   @brief  ʱ������
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

u8 _idata clock_in;

/*----------------------------------------------------------------------------*/
/**@brief  P05��������
   @param  P05_SEL_IO:��ͨIO����, P05_SEL_OSC1:�����RTC���񴦵ľ���ʱ��, P05_SEL_PLL
   @return ��
   @note   void P05_source_select(u8 sel)
*/
/*----------------------------------------------------------------------------*/
void P05_source_select(u8 sel)
{
    if (sel == P05_SEL_IO)								//��ͨIO����
    {
        P0DIR |= BIT(5);
        P5PU &= ~(BIT(4) | BIT(5));
    }
    else if (sel == P05_SEL_OSC1)							//�����RTC���񴦵ľ���ʱ��
    {
        CLKCON1 |= 3;
        P5PU |= BIT(4);
        P0DIR &= ~BIT(5);
    }
    else if (sel == P05_SEL_PLL)
    {
        P5PU |= (BIT(4) | BIT(5));
        P0DIR &= ~BIT(5);
    }
}

/*----------------------------------------------------------------------------*/
/**@brief  timer ��ʼ��
   @param  1:48M, 0:24M
   @return ��
   @note   void timer_init(u8 clk)
*/
/*----------------------------------------------------------------------------*/
#pragma disable
void timer_init(u8 clk)
{
/////rtc timer
    IP1 |= BIT(7);
    IE1 |= BIT(7);

/////timer 0
    PT0 = 1;
	if (clk == MAIN_CLK_12M)
		T0SCA = 9;
    if (clk == MAIN_CLK_24M)
        T0SCA = 10;      // 1/(2^n)��Ƶ
    else if (clk == MAIN_CLK_48M)
        T0SCA = 11;
    T0PRD = 46;
    T0CNT = 0;
    T0CON = 0x21;   //����ΪTIMERģʽ����������Ӧ���жϴ�
    ET0 = 1;
////timer3
    PT3 = 1;
	if (clk == MAIN_CLK_12M)
		T3SCA = 0x25;
    if (clk == MAIN_CLK_24M)
        T3SCA = 0x26;      // 1/(2^n)��Ƶ
    else if (clk == MAIN_CLK_48M)
        T3SCA = 0x27;
    T3CNTL = 0;
    T3CNTH = 0;
    T3PRD = 0xa1;
    T3PRD = 0x22;
    T3CON = 0x32;      //����ΪTIMERģʽ����������Ӧ���жϴ�
    ET3 = 1;
}

