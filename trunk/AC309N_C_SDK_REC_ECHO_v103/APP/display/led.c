/*--------------------------------------------------------------------------*/
/**@file    led.c
   @brief   4位LED驱动
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "led.h"
#include "uart.h"
#if(NO_DISP != monitor)

#define LED0_STATUS          LED_BUFF[4]
#define LED0_FLASH_STATUS    LED_FLASH[4]

extern bool iic_busy;


_idata u8 LED_BUFF[5];   ///<LED显存
_idata u8 LED_FLASH[5];
/*
u8 _code led_icon[] =    ///<LED标志位
{
    LED0_FM,
    LED0_USB,
    LED0_SD,
    LED0_MP3,
    LED0_2POINT,
	LED0_PLAY,
	LED0_PAUSE,
};
*/
#define LED_MINUS     0x40

u8 _code LED_NUMBER[10] =
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

u8 _code LED_LARGE_LETTER[26] =
{
    0x77,0x40,0x39,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
/*----------------------------------------------------------------------------*/
/**@brief    清空LED BUFF函数，LED显示位置设为1
   @param	 无
   @return	 无
   @note     void clear_led(void)
*/
/*----------------------------------------------------------------------------*/
void clear_led(void)
{
    LED_BUFF[0] = 0;	  /* 千位 */
    LED_BUFF[1] = 0;	  /* 百位 */
    LED_BUFF[2] = 0;	  /* 十位 */
    LED_BUFF[3] = 0;	  /* 个位 */
    LED_BUFF[4] = 0;	  /* 状态位 */
    LED_FLASH[0] = 0;
    LED_FLASH[1] = 0;
    LED_FLASH[2] = 0;
    LED_FLASH[3] = 0;
    LED_FLASH[4] = 0;
}

/*----------------------------------------------------------------------------*/
/**@brief    数码管状态位显示
   @param	 id：要显示的状态位
   @return	 无
   @note     void led_disp_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void led_disp_icon(u8 id)
{
    LED0_STATUS |= id;	
}
void led_clr_icon(u8 id)
{
    LED0_STATUS&=~id;	
}
/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 id：状态位
   @return	 无
   @note     void led_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void led_flash_icon(u8 id)
{
    LED0_FLASH_STATUS |= id;	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 flag：闪烁的数据位
   @return	 无
   @note     void led_flash_section(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void led_flash_section(u8 flag)
{
	if((flag >=1)&&(flag <= 4))
	{
	    LED_FLASH[flag]=0xff;
	}	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 显示初始化
   @param	 无
   @return	 无
   @note     void init_led_disp(void)
*/
/*----------------------------------------------------------------------------*/
void init_led_disp(void)
{

    clear_led();
    led_com_out();
    led_seg_out();
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 亮度设置
   @param	 br:亮度数值
   @return	 无
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
void led_set_brightness(u8 br)
{
    if (br > 16)
        return;
    if (br == 16)
        PWM4CON = 0;
    else
        PWM4CON = br | 0xd0;
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 字符显示
   @param	 chardata：字符数据
   @return	 无
   @note     void led_putchar(u8 chardata,u8 loc)
*/
/*----------------------------------------------------------------------------*/
void led_putchar(u8 chardata,u8 loc)
{
    loc += 0;
    if ((chardata < ' ') || (chardata > '~'))
    {
        return;
    }
    if ((chardata >= '0') && (chardata <= '9'))
    {
        LED_BUFF[loc] = LED_NUMBER[chardata - '0'];
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
        LED_BUFF[loc] = LED_SMALL_LETTER[chardata - 'a'];
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
        LED_BUFF[loc] = LED_LARGE_LETTER[chardata - 'A'];
    }
    else if (chardata == ':')
    {
        LED0_STATUS |= LED0_2POINT;
    }
    else if (chardata == ' ')
    {

    }
    else if (chardata == '-')
    {
        LED_BUFF[loc] = LED_MINUS;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    LED扫描函数
   @param
   @return
   @note     void disp_scan(void)
*/
/*----------------------------------------------------------------------------*/
void disp_scan(void)
{
    static u8 cnt;
    static u8 counter;
    static bool flash;

    u8 com, seg;

    if(iic_busy)return;

    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        seg = LED_BUFF[4] ^ LED_FLASH[4];   
    }
    else
    {
        seg = LED_BUFF[4]; 
    }
    com = BIT(cnt); 
    /**/
#if 0
//LED_BUFF[4]=BIT(6);
//led_disp_icon(BIT(0));
	Bat_icon_chk();

    P1DIR |=0x7F; P1PU &=~0x7F; P1PD&=~0x7F;

#if 1
P1HD |=0x7F;
#else
P1HD&=~0x7F;
#endif

#if 0

    switch(cnt){

	case 0:
		P1DIR &=~((( ((LED_BUFF[0]&BIT(LED_C))<<1)|((LED_BUFF[0]&BIT(LED_D))<<1)|((LED_BUFF[0]&BIT(LED_F))>>4)|((LED_BUFF[0]&BIT(LED_G))>>4)|((LED_BUFF[2]&BIT(LED_D))<<2) )|BIT(0)));
		P10 =1;
		P1 &=~((( ((LED_BUFF[0]&BIT(LED_C))<<1)|((LED_BUFF[0]&BIT(LED_D))<<1)|((LED_BUFF[0]&BIT(LED_F))>>4)|((LED_BUFF[0]&BIT(LED_G))>>4)|((LED_BUFF[2]&BIT(LED_D))<<2) )));
		break;
	case 1:
		P1DIR &=~((( ((LED_BUFF[0]&BIT(LED_A)))|((LED_BUFF[1]&BIT(LED_C))<<2)|((LED_BUFF[1]&BIT(LED_F))>>3)|((LED_BUFF[1]&BIT(LED_G))>>3)|((seg&BIT(LED_C))<<3) )|BIT(1)));
		P11 =1;
		P1 &=~((( ((LED_BUFF[0]&BIT(LED_A)))|((LED_BUFF[1]&BIT(LED_C))<<2)|((LED_BUFF[1]&BIT(LED_F))>>3)|((LED_BUFF[1]&BIT(LED_G))>>3)|((seg&BIT(LED_C))<<3) )));
		break;
	case 2:
		P1DIR &=~((( ((LED_BUFF[0]&BIT(LED_B))>>1)|((LED_BUFF[1]&BIT(LED_A))<<1)|((LED_BUFF[2]&BIT(LED_E))<<1)|((LED_BUFF[2]&BIT(LED_F))>>2)|((LED_BUFF[2]&BIT(LED_G))>>2)|((seg&BIT(LED_E))<<2) )|BIT(2)));	
		P12 =1;
		P1 &=~((( ((LED_BUFF[0]&BIT(LED_B))>>1)|((LED_BUFF[1]&BIT(LED_A))<<1)|((LED_BUFF[2]&BIT(LED_E))<<1)|((LED_BUFF[2]&BIT(LED_F))>>2)|((LED_BUFF[2]&BIT(LED_G))>>2)|((seg&BIT(LED_E))<<2) )));
		break;
	case 3:
		P1DIR &=~((( ((LED_BUFF[0]&BIT(LED_E))>>4)|((LED_BUFF[1]&BIT(LED_B)))|((LED_BUFF[2]&BIT(LED_A))<<4)|((LED_BUFF[3]&BIT(LED_D))<<2)|((seg&BIT(LED_G))>>4) )|BIT(3)));
		P13 =1;
		P1 &=~((( ((LED_BUFF[0]&BIT(LED_E))>>4)|((LED_BUFF[1]&BIT(LED_B)))|((LED_BUFF[2]&BIT(LED_A))<<4)|((LED_BUFF[3]&BIT(LED_D))<<2)|((seg&BIT(LED_G))>>4) )));		
		break;
	case 4:
		P1DIR &=~((( ((LED_BUFF[1]&BIT(LED_E))>>3)|((LED_BUFF[2]&BIT(LED_B))<<1)|((LED_BUFF[2]&BIT(LED_C))<<1)|((LED_BUFF[3]&BIT(LED_F)))|((seg&BIT(LED_D))>>3) )|BIT(4)));
		P14 =1;
		P1 &=~((( ((LED_BUFF[1]&BIT(LED_E))>>3)|((LED_BUFF[2]&BIT(LED_B))<<1)|((LED_BUFF[2]&BIT(LED_C))<<1)|((LED_BUFF[3]&BIT(LED_F)))|((seg&BIT(LED_D))>>3) )));			
		break;
	case 5:
		P1DIR &=~((( ((LED_BUFF[1]&BIT(LED_D))>>2)|((LED_BUFF[3]&BIT(LED_A))<<6)|((LED_BUFF[3]&BIT(LED_C))<<2)|((LED_BUFF[3]&BIT(LED_E))>>1)|((seg&BIT(LED_A)))|((seg&BIT(LED_B))<<1) )|BIT(5)));
		P15 =1;
		P1 &=~((( ((LED_BUFF[1]&BIT(LED_D))>>2)|((LED_BUFF[3]&BIT(LED_A))<<6)|((LED_BUFF[3]&BIT(LED_C))<<2)|((LED_BUFF[3]&BIT(LED_E))>>1)|((seg&BIT(LED_A)))|((seg&BIT(LED_B))<<1) )));
		break;
	case 6:
		P1DIR &=~((( ((LED_BUFF[3]&BIT(LED_B))<<4)|((LED_BUFF[3]&BIT(LED_G))>>2)|((seg&BIT(LED_F))>>3) )|BIT(6)));
		P16 =1;
		P1 &=~((( ((LED_BUFF[3]&BIT(LED_B))<<4)|((LED_BUFF[3]&BIT(LED_G))>>2)|((seg&BIT(LED_F))>>3) )));
		break;
	case 7:
		P1DIR &=~((LED_BUFF[3]&0x70)|BIT(3));
		P13 =1;
		P1 &=~((LED_BUFF[3]&0x70));
		break;		
    }

    cnt = (cnt >= 6)?( 0 ): (cnt+1);

#else

    switch(cnt){

	case 0:
		P1DIR &=~(((LED_BUFF[0]<<LED_B)|BIT(0)));
		P10 =0;
		P1 |=(LED_BUFF[0]<<LED_B);
		break;
	case 1:
		P1DIR &=~(((LED_BUFF[1]<<LED_B)|BIT(0)));
		P10 =1;
		P1 &=~(LED_BUFF[1]<<LED_B);
		break;
	case 2:
		P1DIR &=~((seg<<LED_D)|((LED_BUFF[0]&(BIT(LED_G)))>>4)|BIT(1));	
		P11 =0;
		P1 |=((seg<<LED_D)|((LED_BUFF[0]&(BIT(LED_G)))>>4));
		break;
	case 3:
		P1DIR &=~(((seg&0xF0)>>1)|((LED_BUFF[1]&(BIT(LED_G)))>>4)|BIT(1));
		P11 =1;
		P1 &=~(((seg&0xF0)>>1)|((LED_BUFF[1]&(BIT(LED_G)))>>4));		
		break;
	case 4:
		P1DIR &=~(((LED_BUFF[2]&0x0F)<<LED_D)|BIT(2));
		P12 =0;
		P1 |=((LED_BUFF[2]&0x0F)<<LED_D);			
		break;
	case 5:
		P1DIR &=~(((LED_BUFF[3]&0x0F)<<LED_D)|BIT(2));
		P12 =1;
		P1 &=~((LED_BUFF[3]&0x0F)<<LED_D);
		break;
	case 6:
		P1DIR &=~((LED_BUFF[2]&0x70)|BIT(3));
		P13 =0;
		P1 |=(LED_BUFF[2]&0x70);
		break;
	case 7:
		P1DIR &=~((LED_BUFF[3]&0x70)|BIT(3));
		P13 =1;
		P1 &=~((LED_BUFF[3]&0x70));
		break;		
    }

    cnt = (cnt >= 7)?( 0 ): (cnt+1);

#endif


#else

    seg = LED_BUFF[cnt];

#if 1
    LED_COM |= 0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG &=~0x7f;			 //清LED COM SEG	

    LED_SEG |=seg;
    LED_COM &=~com;
    P3PD |= com;

#else	
    LED_COM &= ~0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG |= 0x7f;			 //清LED COM SEG

    LED_SEG &= ~seg;
    LED_COM |= com;
    LED_COM_MASK |= com;
#endif	
    cnt = (cnt >= 4)?( 0 ): (cnt+1);

#endif	
}
#else
//void disp_scan(void)
//{
//}
#endif
