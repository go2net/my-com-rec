/*lcd segment*/
#include "lcdsegment.h"

#if(LCD_DISP == monitor)

u16 lcd_buff[4]={0};

#define LCD_BACKLIGHT_LOW()		P02 =0;
#define LCD_BACKLIGHT_HIGH()		P02 =1;

u8 _code LCD_NUMBER[10] =
{
    0x3f,0x06,0x5b,0x4f,0x66,  ///<0~4
    0x6d,0x7d,0x07,0x7f,0x6f   ///<5~9
};

u8 _code LCD_LARGE_LETTER[26] =
{
    0x77,0x40,0x39,0x3f,0x79,///<ABCDE
    0x71,0x40,0x76,0x06,0x40,///<FGHIJ
    0x40,0x38,0x40,0x37,0x3f,///<KLMNO
    0x73,0x40,0x50,0x6d,0x40,///<PQRST
    0x3e,0x3e,0x40,0x76,0x40,///<UVWXY
    0x40///<Z
};

u8 _code LCD_SMALL_LETTER[26] =
{
    0x77,0x7c,0x58,0x5e,0x79,///<abcde
    0x71,0x40,0x40,0x40,0x40,///<fghij
    0x40,0x38,0x40,0x54,0x5c,///<klmno
    0x73,0x67,0x50,0x40,0x40,///<pqrst
    0x3e,0x3e,0x40,0x40,0x40,///<uvwxy
    0x40///<z
};
void clear_seg_lcd(void)
{

	lcd_buff[0] =0x0000;
	lcd_buff[1] =0x0000;
	lcd_buff[2] =0x0000;
	lcd_buff[3] =0x0000;
}
#if 0
void lcd_backlight_ctrl(bool on)
{
	if(!on){
		P0DIR |= (BIT(2));P0PU|= (BIT(2)); 
    		LCD_BACKLIGHT_HIGH();
	}
	else{

		P0DIR |= (BIT(2));P0PD|= (BIT(2)); 
    		LCD_BACKLIGHT_LOW();
	}

}
#endif
/*----------------------------------------------------------------------------*/
/**@brief    数码管状态位显示
   @param	 id：要显示的状态位
   @return	 无
   @note     void led_disp_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/

void seg_lcd_disp_icon(u8 id)
{
    switch(id)
    {
	case USB_ICON:
		F_USB_DEV |=USB_DEV_MASK;
		break;
	case SD_ICON:
		F_SD_DEV |=SD_DEV_MASK;
		break;
	case AUX_ICON:
		F_AUX_DEV |=AUX_DEV_MASK;
		break;
	case FM_ICON:
		F_FM_DEV |=FM_DEV_MASK;
		break;
	case REP_1_ICON:
		F_REP_ONE|=REP_ONE_MASK;
		break;
	case REP_ALL_ICON:
		F_REP_ALL |=REP_ALL_MASK;
		break;
	case COL_ICON:
		F_POINTS |=POINTS_MASK;
		break;		
	case F1BC_ICON:
		F_NUM_1BC |=NUM_1BC_MASK;
		break;				
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 id：状态位
   @return	 无
   @note     void led_flash_icon(u8 id)
*/
/*----------------------------------------------------------------------------*/
u8  xdata lcd_flash_icon=NONE_ICON;
u8 xdata lcd_flash_timer=0;
void seg_lcd_flash_icon(u8 id)
{
    lcd_flash_icon = id;	
}

/*----------------------------------------------------------------------------*/
/**@brief    LED闪烁设置
   @param	 flag：闪烁的数据位
   @return	 无
   @note     void led_flash_section(u8 flag)
*/
/*----------------------------------------------------------------------------*/
void seg_lcd_flash_section()
{

    switch(lcd_flash_icon)
    {
	case USB_ICON:
		F_USB_DEV &=~USB_DEV_MASK;
		break;
	case SD_ICON:
		F_SD_DEV &=~SD_DEV_MASK;
		break;
	case AUX_ICON:
		F_AUX_DEV &=~AUX_DEV_MASK;
		break;
	case FM_ICON:
		F_FM_DEV &=~FM_DEV_MASK;
		break;
	case REP_1_ICON:
		F_REP_ONE&=~REP_ONE_MASK;
		break;
	case REP_ALL_ICON:
		F_REP_ALL &=~REP_ALL_MASK;
		break;
	case COL_ICON:
		F_POINTS &=~POINTS_MASK;
		break;		
	case F1BC_ICON:
		F_NUM_1BC &=~NUM_1BC_MASK;
		break;				
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 显示初始化
   @param	 无
   @return	 无
   @note     void init_led_disp(void)
*/
/*----------------------------------------------------------------------------*/
void init_seg_lcd_disp(void)
{
    	clear_seg_lcd();
    	seg_init();
    	com_init();
}

/*----------------------------------------------------------------------------*/
/**@brief    LED 亮度设置
   @param	 br:亮度数值
   @return	 无
   @note     void led_set_brightness(u8 br)
*/
/*----------------------------------------------------------------------------*/
void seg_lcd_set_brightness(u8 br)
{
#if 0
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
u8 get_lcd_disbuf_offset(u8 lcd_digit)
{
	switch(lcd_digit)
	{
		case 0:return 0;
		case 1:return 1;
		case 2:return 3;
		case 3:return 5;		
	}
	return 0xFF;
}
void align_lcd_disp_buff(u8 offset,u8 letter_data)
{
	u8 digit_idx=0;
	digit_idx= get_lcd_disbuf_offset(offset);
	if(digit_idx==0)return;
	
	lcd_buff[0] &= ~(0x0003<<digit_idx);
	lcd_buff[1] &= ~(0x0003<<digit_idx);
	lcd_buff[2] &= ~(0x0003<<digit_idx);
	lcd_buff[3] &= ~(0x0001<<digit_idx);

       lcd_buff[0] |= ((letter_data & DIG_A)|(letter_data & DIG_B))<<digit_idx;
       lcd_buff[1] |= (((letter_data & DIG_G)>>5)|((letter_data & DIG_F)>>5))<<digit_idx;
       lcd_buff[2] |= (((letter_data & DIG_C)>>1)|((letter_data & DIG_E)>>4))<<digit_idx;
       lcd_buff[3] |= (((letter_data & DIG_D)>>3))<<digit_idx;   	 
}
void led_putchar(u8 chardata,u8 loc)
{
    loc += 0;
    if ((chardata < ' ') || (chardata > '~'))
    {
        return;
    }
    if((chardata=='1')&&(loc==0))
    {
           seg_lcd_disp_icon(F1BC_ICON);
    }
    else if ((chardata >= '0') && (chardata <= '9'))
    {
          align_lcd_disp_buff(loc,LCD_NUMBER[chardata - '0']);
    }
    else if ((chardata >= 'a') && (chardata <= 'z'))
    {
         align_lcd_disp_buff(loc,LCD_SMALL_LETTER[chardata - 'a']);
    }
    else if ((chardata >= 'A') && (chardata <= 'Z'))
    {
         align_lcd_disp_buff(loc,LCD_LARGE_LETTER[chardata - 'A']);
    }
    else if (chardata == ':')
    {
        seg_lcd_disp_icon(COL_ICON);
    }
    else if (chardata == ' ')
    {
    }
    else if (chardata == '-')
    {
        //lcd_buff[loc] = LED_MINUS;
    }
}
void seg_lcd_disp_scan(void)
{
    static u8 cnt = 0;
    u8 temp;
    static bool flash;
    //seg_lcd_flash_icon(USB_ICON);

    lcd_flash_timer++;
    if (lcd_flash_timer == 220)
    {
        lcd_flash_timer = 0;
        flash = !flash;
    }
    if (flash)
    {
        seg_lcd_flash_section();   
    }
    else
    {
        seg_lcd_disp_icon(lcd_flash_icon); 
    }
	
    temp = cnt>>1;
    close_com(temp);
    if(cnt & 0x01){
	  seg07_port(lcd_buff[temp]);
	  seg8_port( ( ((lcd_buff[temp]&0x0100)>0)?1:0 ) );
	  clr_com(temp);
    }
    else
   {                            
	  seg07_port(~lcd_buff[temp]);
	  seg8_port(( ((lcd_buff[temp]&0x0100)>0)?0:1 ));
	  set_com(temp);
   }

	   cnt++;
  	if(cnt>7)cnt = 0;
}
#endif


