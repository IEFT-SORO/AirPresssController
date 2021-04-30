/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-04-30 17:37:41
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_OLED_IIC\OLED_IIC.h
 */

#ifndef __OLED_IIC_H__
#define __OLED_IIC_H__

#include <CH551.H>
#define OLED_CMD  0	
#define OLED_DATA 1	
#define OLED_MODE 1

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  				   
#define	IIC_ACK		0

#define	IIC_NO_ACK	1

#define _Nop()			_nop_()
#define	Start_I2c()	do{IIC_SDA=1;IIC_SCL=1;_Nop();IIC_SDA=0;_Nop();}while(0)	
#define	Stop_I2c()	do{IIC_SDA=0;IIC_SCL=1;_Nop();IIC_SDA=1;_Nop();}while(0)	
#define	Read_ACK()	do{IIC_SCL=0;_Nop();IIC_SCL=1;_Nop();_Nop();IIC_SCL=0;_Nop();}while(0)				
#define	ACK_0()			do{IIC_SDA=0;IIC_SCL=1;_Nop();IIC_SCL=0;_Nop();}while(0)	
#define	ACK_1()			do{IIC_SDA=1;IIC_SCL=1;_Nop();IIC_SCL=0;_Nop();}while(0)	


void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	  //����OLEDд�ֽں���
void OLED_Display_On(void);	//���� ����ʾ ����
void OLED_Display_Off(void);//���� ����ʾ ����
void OLED_Init(void);	//���� OLED��ʼ�� ����
void OLED_Clear(void);  //���� ���� ����
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char  Char_Size); //���� ��ʾ�ַ� ����
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2); //���� ��ָ����λ�ã���ʾһ��ָ�����ȴ�С���� ����
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p,unsigned char  Char_Size);	 //���� ��ָ��λ�ÿ�ʼ��ʾ�ַ��� ����
void OLED_Set_Pos(unsigned char x, unsigned char y);		//���� ���� ����
void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char len,unsigned char size2);
void OLED_RevShowCHinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no); //���� ��ָ��λ����ʾ���� ����
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //���� ��ʾͼƬ ����
void OLED_Scroll(unsigned char x, unsigned char y);
void OLED_ShowIntegerNumber(unsigned char x,unsigned char y,int num,unsigned char Char_Size);
void OLED_Show_Decimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2);
void OLED_ShowFloatNumber(unsigned char  x,unsigned char  y,float num,unsigned char  Char_Size);
void OLED_CloseScroll();
void OLED_Upmove();

#endif
