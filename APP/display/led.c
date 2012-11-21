/*--------------------------------------------------------------------------*/
/**@file    led.c
   @brief   4位LED驱动
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"
#include "led.h"
#include "uart.h"
#if(NO_DISP != monitor)


#if defined(LED_USE_NORMAL_4X8)
#define LED_SBUF_IDX		1
#define LED0_STATUS          	 LED_BUFF[1]
#define LED1_STATUS          	 LED_BUFF[2]
#define LED0_FLASH_STATUS    LED_FLASH[1]
#define LED1_FLASH_STATUS    LED_FLASH[2]
#else
#define LED_SBUF_IDX		4
#define LED0_STATUS          LED_BUFF[LED_SBUF_IDX]
#define LED0_FLASH_STATUS    LED_FLASH[LED_SBUF_IDX]
#endif


extern xd_u8 work_mode;
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
    0x73,0x40,0x50,0x6d,0x07,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LED_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x07,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};

#define 	SEG_A	0x01
#define 	SEG_B	0x02
#define 	SEG_C	0x04
#define 	SEG_D	0x08
#define 	SEG_E	0x10
#define 	SEG_F	0x20
#define 	SEG_G	0x40
#define 	SEG_H	0x80

#define 	COM_1	0x01
#define 	COM_2	0x02
#define 	COM_3	0x04
#define 	COM_4	0x08
#define 	COM_5	0x10
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
#if defined(LED_USE_NORMAL_4X8)
	if(work_mode == FM_RADIO_MODE){
    		LED1_STATUS |= id;
	}
	else{
    		LED0_STATUS |= id;
	}
#else
    LED0_STATUS |= id;	
#endif
}
void clr_led_disp_icon(u8 id)
{
    LED0_STATUS &=~id;	
}
/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 id：状态位
   @return	 无
   @note     void led_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
void clr_led_flash_icon(u8 id)
{
    LED0_FLASH_STATUS &=~id;	
}
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
	if(flag!= LED_SBUF_IDX)
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
#ifndef NO_LED_DISPLAY
    clear_led();
    led_com_out();
    led_seg_out();
#endif	
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
#if !defined(LED_GPIO_PORT_CUSTOMERIZED)

    if (br > 16)
        return;
    if (br == 16)
        PWM4CON = 0;
    else
        PWM4CON = br | 0xd0;
#endif	
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
#if defined(USE_BAT_MANAGEMENT)
void custom_buf_update(void);
#endif

#if defined(LED_GPIO_PORT_CUSTOMERIZED)
#if defined(K1153_AJR_LSK8_REC_V001)
void LED_COM_OUT(u8 COM_Data)
{
 	P30 =((COM_Data&0x01)>0)?1:0;
 	P31 =((COM_Data&0x02)>0)?1:0;
 	P33 =((COM_Data&0x04)>0)?1:0;
 	P17 =((COM_Data&0x08)>0)?1:0;
 	P32 =((COM_Data&0x10)>0)?1:0;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x0f;
	LED_SEG &=~0x7F;
 	P14=((SEG_Data&SEG_A)>0)?1:0;
 	P13=((SEG_Data&SEG_B)>0)?1:0;
 	P11=((SEG_Data&SEG_C)>0)?1:0;
 	P10=((SEG_Data&SEG_D)>0)?1:0;
 	P16=((SEG_Data&SEG_E)>0)?1:0;
 	P12=((SEG_Data&SEG_F)>0)?1:0;
 	P15=((SEG_Data&SEG_G)>0)?1:0;
}
#elif defined(K1181_YDT_1181_REC_V001)
void LED_COM_OUT(u8 COM_Data)
{
    LED_COM |=COM_Data;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x1f;
	//LED_SEG &=~0x7F;
 	P16=((SEG_Data&SEG_A)>0)?1:0;
 	P15=((SEG_Data&SEG_B)>0)?1:0;
 	P14=((SEG_Data&SEG_C)>0)?1:0;
 	P13=((SEG_Data&SEG_D)>0)?1:0;
 	P12=((SEG_Data&SEG_E)>0)?1:0;
 	P11=((SEG_Data&SEG_F)>0)?1:0;
 	P10=((SEG_Data&SEG_G)>0)?1:0;
}
#elif defined(K1189_AJR_LSK8_REC_V001)
void LED_COM_OUT(u8 COM_Data)
{
 	P30 =((COM_Data&0x01)>0)?0:1;
 	P31 =((COM_Data&0x02)>0)?0:1;
 	P33 =((COM_Data&0x04)>0)?0:1;
 	P17 =((COM_Data&0x08)>0)?0:1;
 	P32 =((COM_Data&0x10)>0)?0:1;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x0f;
	LED_SEG &=~0x7F;
 	P14=((SEG_Data&SEG_A)>0)?0:1;
 	P13=((SEG_Data&SEG_B)>0)?0:1;
 	P11=((SEG_Data&SEG_C)>0)?0:1;
 	P10=((SEG_Data&SEG_D)>0)?0:1;
 	P16=((SEG_Data&SEG_E)>0)?0:1;
 	P12=((SEG_Data&SEG_F)>0)?0:1;
 	P15=((SEG_Data&SEG_G)>0)?0:1;
}
#elif defined(K0000_BHT_C202_REC_V001)
void LED_COM_OUT(u8 COM_Data)
{
 	P31 =((COM_Data&0x01)>0)?1:0;
 	P32 =((COM_Data&0x02)>0)?1:0;
 	P33 =((COM_Data&0x04)>0)?1:0;
 	P34 =((COM_Data&0x08)>0)?1:0;
 	P30 =((COM_Data&0x10)>0)?1:0;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x0f;
	LED_SEG &=~0x7F;
       LED_SEG |=(SEG_Data&0x7F);
}
#elif defined(K4006_SES_1234_REC_V001)
void LED_COM_OUT(u8 COM_Data)
{
 	P31 =((COM_Data&0x01)>0)?1:0;
 	P32 =((COM_Data&0x02)>0)?1:0;
 	P33 =((COM_Data&0x04)>0)?1:0;
 	P34 =((COM_Data&0x08)>0)?1:0;
 	P30 =((COM_Data&0x10)>0)?1:0;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x0f;
	LED_SEG &=~0x7F;
 	P14=((SEG_Data&SEG_A)>0)?0:1;
 	P13=((SEG_Data&SEG_B)>0)?0:1;
 	P11=((SEG_Data&SEG_C)>0)?0:1;
 	P10=((SEG_Data&SEG_D)>0)?0:1;
 	P16=((SEG_Data&SEG_E)>0)?0:1;
 	P12=((SEG_Data&SEG_F)>0)?0:1;
 	P15=((SEG_Data&SEG_G)>0)?0:1;
}
#else
void LED_COM_OUT(u8 COM_Data)
{
 	P30 =((COM_Data&0x01)>0)?1:0;
 	P31 =((COM_Data&0x02)>0)?1:0;
 	P32 =((COM_Data&0x04)>0)?1:0;
 	P33 =((COM_Data&0x08)>0)?1:0;
 	P17 =((COM_Data&0x10)>0)?1:0;
}
void LED_SEG_OUT(u8 SEG_Data)
{
    	LED_COM &= ~0x0f;
	LED_SEG &=~0x7F;
       LED_SEG |=(SEG_Data&0x7F);
}
#endif
void disp_scan(void)
{
#ifndef NO_LED_DISPLAY
    static u8 cnt;
    static u8 counter;
    static bool flash;

    u8 com, seg;

#if defined(USE_BAT_MANAGEMENT)
    custom_buf_update();
#endif
    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        seg = LED_BUFF[cnt] ^ LED_FLASH[cnt];   
    }
    else
    {
        seg = LED_BUFF[cnt]; 
    }
    com = BIT(cnt); 
    /**/
    LED_SEG_OUT(~seg);
    LED_COM_OUT(com);
    cnt = (cnt >= 4)?( 0 ): (cnt+1);
#endif	
}
#elif defined(LED_USE_NORMAL_4X8)
void disp_scan(void)
{
    static u8 cnt;
    static u8 counter;
    static bool flash;

    u8 com, seg;

#if defined(USE_BAT_MANAGEMENT)
    custom_buf_update();
#endif
    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        seg = LED_BUFF[cnt] ^ LED_FLASH[cnt];   
    }
    else
    {
        seg = LED_BUFF[cnt]; 
    }

    com = BIT(cnt); 
    /**/
#if defined(COMMON_CATHODE)
    LED_COM |= 0x0f;
    LED_COM_MASK |= 0x0f;
    P3PD &=~0x0f;
    LED_SEG = 0;			 //清LED COM SEG
    P34 =0;
	
    LED_SEG =seg;
    P34=((seg&0x80)>0)?1:0;
    LED_COM &=~com;
    P3PD |=com;

#else
    LED_COM &= ~0x0f;
    LED_COM_MASK &= ~0x0f;
    LED_SEG |= 0xFf;			 //清LED COM SEG
    
    LED_SEG &= ~seg;
    LED_COM |= com;
    LED_COM_MASK |= com;
#endif
    cnt = (cnt >= 3)?( 0 ): (cnt+1);

}
#else

#ifdef LED_CUSTOM_SCAN_HARDWARE

u8 _code align_com_gpio[5] ={BIT(1),BIT(2),BIT(3),BIT(4),BIT(0)};
void align_seg_gpio(u8 seg_data)
{
 	P16=((seg_data&0x01)>0)?1:0;
 	P15=((seg_data&0x02)>0)?1:0;
 	P14=((seg_data&0x04)>0)?1:0;
 	P13=((seg_data&0x08)>0)?1:0;
 	P12=((seg_data&0x10)>0)?1:0;
 	P11=((seg_data&0x20)>0)?1:0;
 	P10=((seg_data&0x40)>0)?1:0;
}
#endif
void disp_scan(void)
{
#ifndef NO_LED_DISPLAY
    static u8 cnt;
    static u8 counter;
    static bool flash;

    u8 com, seg;

#if defined(USE_BAT_MANAGEMENT)
    custom_buf_update();
#endif
    counter++;
    if (counter == 250)
    {
        counter = 0;
        flash = !flash;
    }

    if (flash)
    {
        seg = LED_BUFF[cnt] ^ LED_FLASH[cnt];   
    }
    else
    {
        seg = LED_BUFF[cnt]; 
    }
    com = BIT(cnt); 
    /**/
    
#ifdef LED_CUSTOM_SCAN_HARDWARE

    LED_COM &= ~0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG |= 0x7f;			 //清LED COM SEG
	
    align_seg_gpio(~seg);
    LED_COM |= align_com_gpio[cnt];
    LED_COM_MASK |= align_com_gpio[cnt];

#elif defined(COMMON_CATHODE)

#if defined(LED_COMMON_SCAN_COM_USE_P17)
    LED_COM |= 0x0f;
    LED_COM_MASK &= ~0x0f;
    LED_SEG =0x80;			 //清LED COM SEG	
    P1PD &=~(BIT(7));

    LED_SEG |=(seg&0x7F);
    LED_COM &=~com;
    P17=((com&0x10)>0)?0:1;
    P1PD |=((com&0x10)>0)?0:BIT(7);
    LED_COM_PD_MASK |= com;
#else
    LED_COM |= 0x1f;
    LED_COM_MASK &= ~0x1f;
    LED_SEG &=~0x7f;			 //清LED COM SEG	

    LED_SEG |=seg;
    LED_COM &=~com;
    LED_COM_PD_MASK |= com;
#endif	
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
#endif

#else
//void disp_scan(void)
//{
//}
#endif
