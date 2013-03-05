/*! \page0  CPU ���ָ��
*
* -APP memory
*   -# DATA  0x18 ~ 0x7F\n
*   -# IDATA 0x80 ~ 0xFF\n
*   -# XDATA 0x300 ~ 0x307F\n
��ջ   0x3600 ~ 0x36FF(256B)\n
�ļ�ϵͳ����  0X700 ~ 0X8FF(512B)\n
��Ƶ���뻺��  0X2880 ~ 0X30FF(2048B)\n
*   -# PDATA 0x80 ~ 0xFF\n
*   -# CODE  0x3000 ~ 0x7FDF\n
*   -# CONST 0x3000 ~ 0x7FDF\n
*   -# DATA 0x0 ~ 0xFF
*   -# CODE 0x0 ~ 0x57FF for APP
*
* - interrupt
*   -# TIMER0         0
*   -# TIMER1         1
*   -# TIMER2         2
*   -# TIMER3         3
*   -# UART           7
*   -# PORT           8
*   -# SPI_EMI DMA    11
*   -# LVD_RTC_IIC    15

*
* - clock system
* - CLKCON0(reset:0x21)\n
* - CLKCON1(reset:0x01)\n
*
* - PCON(reset:0x00)\n
*   BIT0  :SLEEP������Ч\n
*   BIT1  :SYSD3SEL������ʱ�ӳ�2ѡ�񣬸���Ч\n
*   BIT2  :MP3D2SEL��MP3ʱ�ӳ�2ѡ�񣬸���Ч\n
*   BIT3  :OTPD2SEL��OTPʱ�ӳ�2ѡ�񣬸���Ч\n
*   BIT6  :IDLE������Ч������Ĵ���д1��ʹCPUʱ����ͣ��ֱ�������жϻ���\n
*   BIT7  :HOLD������Ч��ȫ��ʱ����ͣ������Ч\n
��ע����SYSD2SELд1ʱ��MP3D2SEL��OTPD2SELҲ���Զ���Ϊ1����֤MP3��OTPʱ�Ӳ����SYSʱ�ӿ죩\n
*/