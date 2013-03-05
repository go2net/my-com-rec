/*--------------------------------------------------------------------------*/
/**@file     eq.c
   @brief    音效控制模块
   @details
   @author
   @date   2011-3-7
   @note
*/
/*----------------------------------------------------------------------------*/
#include "eq.h"

extern DECODER_MSG _xdata *dec_msg;




u8 _code EQTableCode[][11] =
{
    {0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x00}, //NORMAL
    {0x0f,0x0f,0x0d,0x0b,0x08,0x06,0x06,0x06,0x06,0x06,0x08}, //POP
    {0x04,0x06,0x08,0x0e,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x06}, //POP
    {0x0f,0x0f,0x0a,0x06,0x02,0x06,0x0a,0x0c,0x0f,0x0f,0x0a}, //POP
    {0x06,0x08,0x0a,0x0c,0x0f,0x0f,0x0c,0x06,0x04,0x04,0x0a}, //POP

};    ///<DECODER音效表


u16 _code dsp_eq_table[][10] =
{
    16384,0,0,0,0,0,0,0,0,0,
    16384, 16000, 10000, 6000, 3000, 0, 0, 0, 0, 0,
    16384, 9000, 0, 0, 0, 0, 0, 8000, 12000, 8200,
    16384, 0, 0, 0, 0, 16000, 15000, 0, 0, 0,
    22000, 0, -18000, -12000, -8000, 0, 0, 0, 5000, 13000
};    ///<dsp音效表



/*----------------------------------------------------------------------------*/
/**@brief   设置DSP音效
   @param   * eq_table ： 音效数组指针
   @return  无
   @note    void set_dsp_eq(u8 * eq_table)
*/
/*----------------------------------------------------------------------------*/
void set_dsp_eq(u8 n)
{
    dsp_set_eq_coeff(dsp_eq_table[n]);

    if (n == NORMAL)
    {
        dsp_set_eq_mode(0);
    }
    else
    {	
        dsp_set_eq_mode(2);
    }
}

void amux_dsp_eq(void)
{
    dsp_set_eq_coeff(dsp_eq_table[0]);
    dsp_set_eq_mode(0);
}

/*----------------------------------------------------------------------------*/
/**@brief   设置decode 音效
   @param   n : 音效模式
   @return  无
   @note    void EQ_SET(u8 n)
*/
/*----------------------------------------------------------------------------*/

void set_decode_eq(u8 n)
{
    dec_msg->eq_table = EQTableCode[n];
    decode_eq_switch(1);
}

/*----------------------------------------------------------------------------*/
/**@brief   音效控制接口函数
   @param   n : 音效模式
   @return  无
   @note    void set_eq(u8 n)
*/
/*----------------------------------------------------------------------------*/
void set_eq(u8 n)
{
#if EQ_WORK_USE == DECODE_EQ
    set_dsp_eq(0);
    set_decode_eq(n);
#else
    set_decode_eq(0);
    set_dsp_eq(n);

#endif
}


