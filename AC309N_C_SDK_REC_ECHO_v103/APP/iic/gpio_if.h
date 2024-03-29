/*--------------------------------------------------------------------------*/
/**@file     gpio_if.h
   @brief    gpio if
   @details
   @author
   @date   2010-12-13
   @note
*/
/*----------------------------------------------------------------------------*/
#include "config.h"

#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_

//#include "Custom_config.h"
#if defined(INDEPENDENT_REC_LED)

#if defined(REC_LED_GPIO_USE_P04)
#define rec_led_gpio_init()				P0DIR &= ~(BIT(4));P0PU |=(BIT(4))//;//P0PD &= ~(BIT(4))
#define REC_LED_GPIO_CTRL_OFF()		P04 = 0
#define REC_LED_GPIO_CTRL_ON()			P04 = 1
#elif defined(REC_LED_GPIO_USE_P07)
#define rec_led_gpio_init()				P0DIR &= ~(BIT(7));P0PU |=(BIT(7))//;//P0PD &= ~(BIT(4))
#define REC_LED_GPIO_CTRL_OFF()		P07 = 0
#define REC_LED_GPIO_CTRL_ON()			P07 = 1
#elif defined(REC_LED_GPIO_USE_P01)
#define rec_led_gpio_init()				P0DIR &= ~(BIT(1));P0PU |=(BIT(1));P0PD &= ~(BIT(1))
#define REC_LED_GPIO_CTRL_OFF()		P01 = 0
#define REC_LED_GPIO_CTRL_ON()			P01 = 1
#endif

#endif 

#if defined(LED_GPIO_USE_P16)
#define led_gpio_init()			P1DIR &= ~(BIT(6));P1PU |= (BIT(6))
#define LED_GPIO_CTRL_OFF()		P16 = 0
#define LED_GPIO_CTRL_ON()		P16 = 1
#elif defined(LED_GPIO_USE_P07)
#define led_gpio_init()			P0DIR &= ~(BIT(7));P0PU |=(BIT(7));P0PD &= ~(BIT(7))
#define LED_GPIO_CTRL_OFF()		P07 = 0
#define LED_GPIO_CTRL_ON()		P07 = 1
#elif defined(LED_GPIO_USE_P17)
#define led_gpio_init()			P1DIR &= ~(BIT(7));P1PU |=(BIT(7));P1PD &= ~(BIT(7))
#define LED_GPIO_CTRL_OFF()		P17 = 0
#define LED_GPIO_CTRL_ON()		P17 = 1
#elif defined(LED_GPIO_USE_P25)
#define led_gpio_init()			P2DIR &= ~(BIT(5));P2PU &= ~(BIT(5));P2PD &= ~(BIT(5))
#define LED_GPIO_CTRL_OFF()		P25 = 0
#define LED_GPIO_CTRL_ON()		P25 = 1 
#elif defined(LED_GPIO_USE_P01)
#define led_gpio_init()			P0DIR &= ~(BIT(1));P0PU |=(BIT(1));P0PD &= ~(BIT(1))
#define LED_GPIO_CTRL_OFF()		P01 = 0
#define LED_GPIO_CTRL_ON()		P01 = 1
#elif defined(LED_GPIO_USE_P04)
#define led_gpio_init()			P0DIR &= ~(BIT(4));P0PU |=(BIT(4));P0PD &= ~(BIT(4))
#define LED_GPIO_CTRL_OFF()		P04 = 0
#define LED_GPIO_CTRL_ON()		P04 = 1
#elif defined(LED_GPIO_USE_P00)
#define led_gpio_init()			P0DIR &= ~(BIT(0));P0PU |=(BIT(0));P0PD &= ~(BIT(0))
#define LED_GPIO_CTRL_OFF()		P00 = 0
#define LED_GPIO_CTRL_ON()		P00 = 1
#else
#define led_gpio_init()			 
#define LED_GPIO_CTRL_OFF()		 
#define LED_GPIO_CTRL_ON()		
#endif

// msgfor_hot.c
#if defined(MUTE_CTRL_LEVEL_NORMAL)
#define MUTE_LEVEL		1
#define UNMUTE_LEVEL	0
#else
#define MUTE_LEVEL		0
#define UNMUTE_LEVEL	1
#endif



#if defined(MUTE_PORT_USE_DUMP)
#define AMP_MUTE_PORT_INIT() 			
#define AMP_MUTE_DISABLE()		
#define AMP_MUTE_ENABLE() 
#elif defined( MUTE_PORT_USE_P01)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(1));P0PU |= (BIT(1));P0PD &= ~(BIT(1))
#define AMP_MUTE_DISABLE() 	 	 P01 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P01 = MUTE_LEVEL
#elif defined( MUTE_PORT_USE_P02)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(2));P0PU |=(BIT(2))//;P0PD &= ~(BIT(3))
#define AMP_MUTE_DISABLE() 	 	 P02 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P02 = MUTE_LEVEL
#elif defined( MUTE_PORT_USE_P03)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(3));P0PU |=(BIT(3))//;P0PD &= ~(BIT(3))
#define AMP_MUTE_DISABLE() 	 	 P03 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P03 = MUTE_LEVEL
#elif defined(MUTE_PORT_USE_P07)
#define AMP_MUTE_PORT_INIT() 	 P0DIR &= ~(BIT(7));P0PU |=(BIT(7))//;P0PD &= ~(BIT(3))
#define AMP_MUTE_DISABLE() 	 	 P07 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P07 = MUTE_LEVEL
#elif defined(MUTE_PORT_USE_WKUP)
//dummy
#elif defined(MUTE_PORT_USE_P25)
#define AMP_MUTE_PORT_INIT() 	 DACCON0|=0x80;P2DIR &= ~(BIT(5));P2PU |= (BIT(5));P2PD &= ~(BIT(5))
#define AMP_MUTE_DISABLE() 	 	 P25 = UNMUTE_LEVEL
#define AMP_MUTE_ENABLE() 	 	 P25 = MUTE_LEVEL
#else
#define AMP_MUTE_PORT_INIT() 	
#define AMP_MUTE_DISABLE() 	 	 
#define AMP_MUTE_ENABLE() 	 	 
#endif

#ifdef MUTE_PORT_FOR_2_AMP
#if defined(AMP_2_MUTE_PORT_USE_P07)
#define AMP_MUTE_PORT_INIT_2() 	 P0DIR &= ~(BIT(7));P0PU |=(BIT(7))//;P0PD &= ~(BIT(3))
#define AMP_MUTE_DISABLE_2() 	 	 P07 = MUTE_LEVEL
#define AMP_MUTE_ENABLE_2() 	 	 P07 = UNMUTE_LEVEL
#endif
#endif

#if 1
//4 ----- IIC ��H
#if defined(IIC_GPIO_USE_P00_P01)
#define iic_data_out()    P0DIR &= ~(BIT(1));P0PU |= BIT(1) 	
#define iic_data_in()     P0DIR |= (BIT(1));P0PU |= BIT(1)	
#define iic_data_r()      P01
#define iic_data_h()      P01 = 1
#define iic_data_l()      P01 = 0

#define iic_clk_out()    P0DIR &= ~(BIT(0));P0PU |= (BIT(0))
#define iic_clk_h()      P00 = 1
#define iic_clk_l()      P00 = 0
#elif defined(IIC_GPIO_USE_P05_P17)
#define iic_data_out()    P1DIR &= ~(BIT(7));P1PU |= (BIT(7))
#define iic_data_in()      P1DIR |= (BIT(7));P1PU |= (BIT(7))
#define iic_data_r()       P17
#define iic_data_h()       P17 = 1
#define iic_data_l()        P17 = 0

#define iic_clk_out()     P0DIR &= ~(BIT(5));P0PU |= (BIT(5))
#define iic_clk_h()        P05 = 1
#define iic_clk_l()         P05 = 0
#elif defined(IIC_GPIO_USE_P16_P17)
#define iic_data_out()    P1DIR &= ~(BIT(7));P1PU |= (BIT(7))
#define iic_data_in()      P1DIR |= (BIT(7));P1PU |= (BIT(7))
#define iic_data_r()       P17
#define iic_data_h()       P17 = 1
#define iic_data_l()        P17 = 0

#define iic_clk_out()     P1DIR &= ~(BIT(6));P1PU |= (BIT(6))
#define iic_clk_h()        P16 = 1
#define iic_clk_l()         P16 = 0
#elif defined(IIC_GPIO_USE_P02_P03)
#define iic_data_out()    P0DIR &= ~(1<<2);P0PU |= (1<<2)
#define iic_data_in()     P0DIR |= (1<<2);P0PU |= (1<<2)
#define iic_data_r()      P02
#define iic_data_h()      P02 = 1
#define iic_data_l()      P02 = 0

#define iic_clk_out()    P0DIR &= ~(1<<3);P0PU |= (1<<3)
#define iic_clk_h()      P03 = 1
#define iic_clk_l()      P03 = 0
#else
#define iic_data_out()   P1DIR &= ~(1<<6);//P0PU |= (1<<2)
#define iic_data_in()    P1DIR |= (1<<6);P1PU |= (1<<6)
#define iic_data_r()     P16
#define iic_data_h()     P16 = 1
#define iic_data_l()     P16 = 0

#define iic_clk_out()    P1DIR &= ~(1<<7);//P0PU |= (1<<3)
#define iic_clk_h()      P17 = 1
#define iic_clk_l()      P17 = 0
#endif
#endif

#ifdef USE_HPHONE_DETECT
#if defined(HP_DETECT_USE_P07)
#define  hp_detect_in()      		P0DIR &= ~(BIT(7)); P07=1; P0DIR |= BIT(7);P0PU |= BIT(7);//linein check port
#define  HP_DETECT_GPIO  		P07
#define  hp_detect_in_off()        	P0DIR &= ~(BIT(7));P07=1;  //linein check port
#elif defined(HP_DETECT_USE_P34)
#define  hp_detect_in()      		P3DIR &= ~(BIT(4)); P34=1; P3DIR |= BIT(4);P3PU |= BIT(4);//linein check port
#define  HP_DETECT_GPIO  		P34
#define  hp_detect_in_off()        	P3DIR &= ~(BIT(4));P34=1;  //linein check port
#elif defined(HP_DETECT_USE_P04)
#define  hp_detect_in()      		P0DIR &= ~(BIT(4)); P04=1; P0DIR |= BIT(4);P0PU |= BIT(4);//linein check port
#define  HP_DETECT_GPIO  		P04
#define  hp_detect_in_off()        	P0DIR &= ~(BIT(4));P04=1;  //linein check port
#elif defined(HP_DETECT_USE_P02)
#define  hp_detect_in()      		P0DIR &= ~(BIT(2)); P02=1; P0DIR |= BIT(2);P0PU |= BIT(2);//linein check port
#define  HP_DETECT_GPIO  		P02
#define  hp_detect_in_off()        	P0DIR &= ~(BIT(2));P02=1;  //linein check port
#elif defined(HP_DETECT_USE_P17)
#define  hp_detect_in()      		P1DIR &= ~(BIT(7)); P17=1; P1DIR |= BIT(7);P1PU |= BIT(7);//linein check port
#define  HP_DETECT_GPIO  		P17
#define  hp_detect_in_off()        	P1DIR &= ~(BIT(7));P17=1;  //linein check port
#elif defined(HP_DETECT_USE_VPP)
#define  hp_detect_in()      		P5PU  |= (BIT(6));  //��VPP������
#define  HP_DETECT_GPIO  		( ((P5HD&(BIT(7)))>0x01)? 1:0 )
#define  hp_detect_in_off()        //P0DIR &= ~(BIT(2));P02=1;  //linein check port
#endif
#endif

#if defined(AUX_DETECT_USE_P02)
#define  aux_detect_in()      			P0DIR &= ~(BIT(2)); P02=1; P0DIR |= BIT(2);P0PU |= BIT(2);//linein check port
#define  AUX_DETECT_GPIO  			P02
#define  aux_detect_in_off()        		P0DIR &= ~(BIT(2));P02=1;  //linein check port
#elif defined(AUX_DETECT_USE_P04)
#define  aux_detect_in()      			P0DIR &= ~(BIT(4)); P04=1; P0DIR |= BIT(4);P0PU |= BIT(4);//linein check port
#define  AUX_DETECT_GPIO  			P04
#define  aux_detect_in_off()        		P0DIR &= ~(BIT(4));P04=1;  //linein check port
#elif defined(AUX_DETECT_USE_P03)
#define  aux_detect_in()      			P0DIR &= ~(BIT(3)); P03=1; P0DIR |= BIT(3);P0PU |= BIT(3);//linein check port
#define  AUX_DETECT_GPIO  			P03
#define  aux_detect_in_off()        		P0DIR &= ~(BIT(3));P03=1;  //linein check port
#elif defined(AUX_DETECT_USE_P17)
#define  aux_detect_in()      			P1DIR |= BIT(7);P0PU |= BIT(7);//linein check port
#define  AUX_DETECT_GPIO  			P17
#define  aux_detect_in_off()        		P1DIR &= ~(BIT(7)); //linein check port
#elif defined(AUX_DETECT_USE_P07)
#define  aux_detect_in()      			P0DIR |= BIT(7);P0PU |= BIT(7);//linein check port
#define  AUX_DETECT_GPIO  			P07
#define  aux_detect_in_off()        		P0DIR &= ~(BIT(7)); //linein check port
#endif

#if defined(CHARGER_DETECT_INDICATOR)

#if defined(CHARGER_DET_USE_PORT_P07)
#define charge_port_init()		P07 =0;P0PU  &= ~(BIT(7));P0PD|= (BIT(7));P0DIR |= (BIT(7))
#define CHARGER_DET_PORT	P07
#elif defined(CHARGER_DET_USE_PORT_P02)
#define charge_port_init()		P02 =0;P0PU  &= ~(BIT(2));P0PD|= (BIT(2));P0DIR |= (BIT(2))
#define CHARGER_DET_PORT	P02
#elif defined(CHARGER_DET_USE_PORT_P17)
#define charge_port_init()		P17 =0;P1PU  &= ~(BIT(7));P1PD|= (BIT(7));P1DIR |= (BIT(7))
#define CHARGER_DET_PORT	P17
#elif defined(CHARGER_DET_USE_VPP)
#define charge_port_init()		P5PU  |= (BIT(6))
#define CHARGER_DET_PORT	( ((P5HD&(BIT(7)))>0x01)? 1:0 )
#endif
#endif
//4 ----- LCD ��H

#define LCD_BL_INIT()	P1DIR &= ~(BIT(0));P1PU |=BIT(0); P1|=(BIT(0))
#define LCD_BL_GPIO_H()	P1|=(BIT(0))
#define LCD_BL_GPIO_L()	P1&=~(BIT(0))

#define LCDPORT_OUT()  LCD_DATA_OUT;LCD_CLK_OUT;LCD_A0_OUT;LCD_RES_OUT;LCD_CS_OUT;//P1DIR &= ~( BIT(7)|BIT(6) );P3DIR &= ~( BIT(0) | BIT(1) | BIT(2) ) 
#define LCDPORT_H()    P1 |= ( BIT(7)|BIT(6) );LCD_A0_H;  LCD_RES_H;	LCD_CS_H;

#define LCD_DATA_OUT P1DIR &= ~(BIT(7));P1PU |= BIT(7)//7 
#define	LCD_CLK_OUT	 P1DIR &= ~(BIT(6));P1PU |= BIT(6)//6

#define	LCD_A0_OUT	  P1DIR &= ~(BIT(3));P1PU |= BIT(3)
#define	LCD_A0_L	  P13 = 0      //P0 &= ~BIT(5)
#define	LCD_A0_H	  P13 = 1      //P0 |= BIT(5)

#define LCD_RES_OUT	  P1DIR &= ~(BIT(2));
#define LCD_RES_L	  P12 = 0      //P3 &= ~BIT(2)
#define LCD_RES_H	  P12 = 1      //P3 |= BIT(2)

#define LCD_CS_OUT	  P1DIR &= ~(BIT(1));P1PU |= BIT(1)
#define LCD_CS_L	  P11 = 0      //P0 &= ~BIT(4)
#define LCD_CS_H	  P11 = 1      //P0 |= BIT(4)


#define SPIDMAISRDIS()  IE1 &= ~(BIT(3))
#define SPIDMAISREN()	IP1 |= BIT(3), IE1 |= BIT(3)

//4 ----- KEY ��H

#define ADC_KEY_IO6     0xFE
#define ADC_KEY_IO7     0xFF
#define ADC_KEY_IO5     0xFD
#define ADC_KEY_IO4     0xFC
#define ADC_KEY_IO3     0xFB
#define ADC_KEY_IO2     0xFA
#define ADC_VDD_12       0xF8
#define ADC_LDOIN         0xF9
#define ADC_MAX_USED   0x03

#ifdef USE_TWO_ADKEY
#undef ADC_MAX_USED
#define ADC_MAX_USED   0x04
#endif

#define OC_SRC_GPIO_INIT()		P0DIR &= ~(BIT(4));P0PU |=BIT(4);
#define SRC_OPT_EN()		P0|=(BIT(4))
#define SRC_COA_EN()		P0&=~(BIT(4))

#define HDMI_SRC_GPIO_INIT()		P3DIR &= ~(BIT(4));P3PU |=BIT(4); 
#define SRC_HDMI_1_EN()		P3|=(BIT(4))
#define SRC_HDMI_2_EN()		P3&=~(BIT(4))

#ifdef REC_GPIO_CTRL
#define REC_GPIO_CTRL_INIT()	P0DIR &= ~(BIT(2));P0PU |=BIT(2);
#define REC_GPIO_HIGH()			P0|=(BIT(2))
#define REC_GPIO_LOW()			P0&=~(BIT(2))
#endif

#ifdef USE_AMP_MODE_SELECT
#if defined(AMP_MODE_SELECT_PORT_USE_P06)
#define D_CLASS_AMP_GPIO_INIT()	P0DIR &= ~(BIT(6));P0PU |=BIT(6);
#define D_CLASS_AMP_HIGH()			P0|=(BIT(6))
#define D_CLASS_AMP_LOW()			P0&=~(BIT(6))
#elif defined(AMP_MODE_SELECT_PORT_USE_P04)
#define D_CLASS_AMP_GPIO_INIT()	P0DIR &= ~(BIT(4));P0PU |=BIT(4);
#define D_CLASS_AMP_HIGH()			P0|=(BIT(4))
#define D_CLASS_AMP_LOW()			P0&=~(BIT(4))
#else
#define D_CLASS_AMP_GPIO_INIT()		P0DIR &= ~(BIT(7));P0PU |=BIT(7);
#define D_CLASS_AMP_HIGH()				P0|=(BIT(7))
#define D_CLASS_AMP_LOW()				P0&=~(BIT(7))
#endif
#elif defined(USE_AMP_MODE_SELECT_FOR_NS4160)
#define NS4160_AMP_GPIO_INIT()			P0DIR &= ~(BIT(7));P0PU |=BIT(7);P07 =1;
#define AB_AMP_SEL()					P07 =0;delay(12);P07 =1;
#define D_CLASS_AMP_SEL()				P07 =0;delay(12);P07 =1;delay(12);P07 =0;delay(12);P07 =1;
#endif

#ifdef MICPHONE_GPIO_DETECTION
#ifdef USE_MIC_INPUT_VOLT_FOR_DETECTION
#define MICPHONE_GPIO_INIT()			P0DIR |=(BIT(4));P0PU &=~(BIT(4))
#define MICPHONE_GPIO_READ			P04
#define MICPHONE_GPIO_RELEASE()		P0PU &=~(BIT(4))
#elif defined(MIC_DETECT_PORT_USE_P17)
#define MICPHONE_GPIO_INIT()			P1DIR |=(BIT(7));P1PU |=BIT(7)
#define MICPHONE_GPIO_READ			P17
#define MICPHONE_GPIO_RELEASE()		//P0DIR &=~(BIT(4))
#else
#define MICPHONE_GPIO_INIT()			P0DIR |=(BIT(4));P0PU |=BIT(4)
#define MICPHONE_GPIO_READ			P04
#define MICPHONE_GPIO_RELEASE()		//P0DIR &=~(BIT(4))
#endif

#endif


#ifdef EXTENDED_AUX_FUNC

#define EXTENDED_AUX_FUNC_GPIO_INIT()		P0DIR &= ~(BIT(2)|BIT(3));P0PU |=(BIT(2)|BIT(3));
#define EXTENDED_AUX_FUNC_CH0()			P02=0;P03=0;
#define EXTENDED_AUX_FUNC_CH1()			P02=1;P03=0;
#define EXTENDED_AUX_FUNC_CH2()			P02=0;P03=1;
#define EXTENDED_AUX_FUNC_CH3()			P02=1;P03=1;
#endif
#endif
