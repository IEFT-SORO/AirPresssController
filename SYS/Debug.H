/*
 * @Author: ZZz
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-11 08:57:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\SYS\Debug.H
 */


#ifndef	__DEBUG_H__
#define __DEBUG_H__

//���庯������ֵ
#ifndef  SUCCESS
#define  SUCCESS  0
#endif
#ifndef  FAIL
#define  FAIL    0xFF
#endif

//���嶨ʱ����ʼ
#ifndef  START
#define  START  1
#endif
#ifndef  STOP
#define  STOP    0
#endif

#define	 FREQ_SYS	   12000000	         //ϵͳ��Ƶ12MHz
#define  OSC_EN_XT     0                 //�ⲿ����ʹ�ܣ�Ĭ�Ͽ����ڲ�����
#ifndef  UART0_BUAD
#define  UART0_BUAD    4800
#define  UART1_BUAD    57600
#endif
#ifndef  DE_PRINTF                      //����Pirntf�������
#define  DE_PRINTF     1
#endif
#define uchar unsigned char
#define uint unsigned int
void	CfgFsys( );                        //CH554ʱ��ѡ�������
void	mDelayuS( UINT16 n );              // ��uSΪ��λ��ʱ
void	mDelaymS( UINT16 n );              // ��mSΪ��λ��ʱ
void	mInitSTDIO( );

void    WDTModeSelect(UINT8 mode);     //CH554���Ź�ģʽ���� 
void    WDTFeed(UINT8 tim);            //CH554���Ź�ι��
void Port1Cfg(UINT8 Mode,UINT8 Pin);
void Port3Cfg(UINT8 Mode,UINT8 Pin);
// void CH554SoftReset( );                  //CH554����λ
// void CH554USBDevWakeup( );               //CH554��USB�豸��������
//  
#endif
