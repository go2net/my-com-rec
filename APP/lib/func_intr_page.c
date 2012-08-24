/*! \page ITER interruptʹ��˵��
 *
 * \section intr0 AC309N interrupt����
 *
 * - AC309N�ж�Ϊ4�����ȼ��ж�\n
 *	 IE0��IE1�ж�ʹ�ܣ�reset:0x00;\n
 *	 IP0/IP0H��IP1/IP1H�ж����ȼ�����,reset:0x00(eg:TIMER0�жϺ�Ϊ0,��ôIP0.0/IP0H.0Ϊ����TMERR0�ж����ȼ�)\n
 *   ��һ���ȼ���IP0H.0 = 1��IP0.0 = 1��  (������ȼ�)\n
 *   �ڶ����ȼ���IP0H.0 = 1��IP0.0 = 0��  (�����ȼ�)\n
 *   �������ȼ���IP0H.0 = 0��IP0.0 = 1��  (�����ȼ�)\n
 *   �������ȼ���IP0H.0 = 0��IP0.0 = 0��  (������ȼ�)\n
 * - ��SDK�����У��ͻ������Ҫ�Լ������µ��жϣ�ԭ����ʹ�õ��������ȼ��жϡ�\n
 *
 * \section intr1 �ж�ʹ�÷�������
 *
 * - ��AC309N��SDK���ж����ȫ��������MASKROM�У��ڿ�����ʽ���ܼ�����\n
 * - ��������Ҫ����һ���ж�xxx,��ô��������\n
 * - ��һ����interrupt_init(n,xxx_isr);n�Ǹ��жϵ��жϺţ�xxx_isr�Ǹ��жϵ��жϷ������\n
 * - �ڶ�����xxx_init();��ʼ�����ж�\n
 * - �������������жϷ��������ù�ϵ��\n
 *   ����Ҽ����keil��project���ڵ�app����target options\n
 *   �ڡ�Options for Target 'app'��������ѡ��'LX51 Misc'ҳ��\n
 *   ��'LX51 Misc'ҳ���е��'Edit...'��ť�����app.lin�ļ��ڱ༭������\n
 *   �ҵ���app.lin�ļ���5������overlay(* !(lcd_dma_isr,rtcisr,timer3isr))����һ�����\n
 *   ��Ҫ���е��жϷ��������ӽ�ȥoverlay(* !(lcd_dma_isr,rtcisr,timer3isr��xxx_isr))������app.lin�ļ�\n
 *   ���\n
 *
 *
 */