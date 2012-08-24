/*! \page PORT PORTָ��
 *
 * \section intro_sec_port PORT �������
 *
 * - AC309N ��P0��P1��P2��P3
 *
 * \subsection  PORT �Ĵ���-����
 * - Port�Ĵ���Resetֵ��\n
 *   P0DIR 0b1111 1111 (R/W)\n
 *   P1DIR 0b1111 1111 (R/W)\n
 *   P2DIR 0b1111 1111 (R/W)\n
 *   P3DIR 0b1111 1111 (R/W)\n
 *   P0 0b0000 0000 (R/W)\n
 *   P1 0b0000 0000 (R/W)\n
 *   P2 0b0000 0000 (R/W)\n
 *   P3 0b0000 0000 (R/W)\n
 *   P0PU 0b0000 0011 (R/W)\n
 *   P1PU 0b0000 0000 (R/W)\n
 *   P2PU 0b0000 0000 (R/W)\n
 *   P3PU 0b0000 0000 (R/W)\n
 *   P0PD 0b1100 0000 (R/W)\n
 *   P1PD 0b0000 0000 (R/W)\n
 *   P2PD 0b0000 0000 (R/W)\n
 *   P3PD 0b0000 0000 (R/W)\n
 *   P0IE 0b1111 1111 (write only)\n
 *   P1IE 0b1111 1111 (write only)\n
 *   P2IE 0b1111 1111 (write only)\n
 *   P3IE 0b1111 1111 (write only)\n
 *   P0HD 0b0000 0000 (R/W)\n
 *   P1HD 0b0000 0000 (R/W)\n
 *   P2HD 0b0000 0000 (R/W)\n
 *   P3HD 0b0010 0000 (R/W)\n
 * - Port�����롢����Ĵ�����P0��P1��P2��P3\n
 *   ResetֵΪ0
 *
 * - Port�ڷ���Ĵ�����P0DIR��P1DIR��P2DIR��P3DIR\n
 *   1�����룻0�������
 *
 * - Port���������ƼĴ�����P0PU��P1PU��P2PU��P3PU\n
 *   ����Ч��
 *
 * - Port���������ƼĴ�����P0PD��P1PD��P2PD��P3PD\n
 *   ����Ч\n
 *
 * - Port������ģ��ѡ��Ĵ�����P0IE��P1IE��P2IE��P3IE\n
 *   1�����ֹ��ܣ�0��ģ�⹦��\n
 *
 * - Port�ڸ��������ƼĴ�����P3HD\n
 *   ����Ч��ResetֵΪ0�� 0��Ӧ8mA�����1��Ӧ24mA�����\n
 *
 * - ������Ĵ���Ϊ0����Ӧ��IOΪ���������򿪣��������ֵΪ����Ĵ�����д���ֵ����ʱ�����Port�ڣ�ֻ�ܶ�������Ĵ�����ֵ��
 *
 * - ������Ĵ���Ϊ1����Ӧ��IO���������ʱ��IO���Ƿ���Ϊ���룬����������Ĵ������ƣ�����������Ĵ���Ϊ1�����IO����������Port�ڿɶ�����Ӧ�ܽŵ�ֵ�����򣬶�Port��ֻ�ܶ���0��
 *
 * - �������ƼĴ���Ϊ0ʱ������Ĵ���Ϊ0ʱ��������ֹ��������ӦIO����10K������
 *
 * - P36��P37ʵ���Ͼ���USBDP��USBDM��\n
 *
 * \subsection port1 VPP����
 *
 * - P5PU BIT7����VPP���� ����Ч����������500ŷķ��resetֵ��0\n
 * - P5PU BIT6����VPP���� ����Ч����������10Kŷķ��resetֵ��0\n
 * - P5HD BIT7�ܶ�ȡVPP״̬
 * \subsection port2 PORT WakeUp����
 * - ֧��WakeUp�ĽŹ�������������P02��P05��P07��P23��������pin��WakeUp��·��˵�ֱ�ΪWakeUp Pin0~3
 * - P5:\n
 *   P5�ĸ�4λΪWKUPEN������Ч�����ֱ��������pin�Ƿ��ܲ������ѣ����жϣ���\n
 *   ResetֵΪ0
 * - P5DIR:\n
 * - P5DIR�ĸ�4λΪWKUPEDG���ֱ�ѡ������pin���ѵı��أ�0Ϊ�����أ�1Ϊ�½���    \n
 *   ResetֵΪ0
 * - P5PD\n
 *   P5PD�ĸ�4λΪ����Pin��Pending�źţ�0Ϊû��Pending��1Ϊ��Pending��\n
 *   Pending���Ա�CPUд0��1\n
 *   ResetֵΪX��ʹ��ǰ���ʼ��\n
 * - ���ϵļĴ������ǿɶ���д
 * - ��оƬ������������״̬����Ч���س��֣���оƬ������жϣ��ж�����Ҫ�򿪣�����ֻ����Pending����û���жϣ���Port�жϵ��ж�����Ϊ8��
 * - ��оƬ����Stop Clockʱ����Ч���س��֣���оƬ�ᱻ���ѣ���stop clockǰ�ж������Ǵ򿪵ģ��򱻻��ѵ�CPU�����Ͻ����жϣ������ִ��stop clock��һ��ָ�
 * - ��оƬ����Sleepʱ����Ч���س��֣���оƬ�ᱻReset��оƬ������������Զ�PD��power down���Ĵ�����PD�Ĵ���Ϊ1��˵����Sleep���ѡ�
 *
 * \subsection port3 GPIO�ֲ�����
 *   \image html port0.bmp
 * \subsection port4 P36��P37����������ͼ
 *   \image html port1.bmp

 */





