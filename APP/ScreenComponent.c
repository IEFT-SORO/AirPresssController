#include <OLED_IIC.h>
#include "Debug.H"
#include "ScreenComponent.h"
#include "KEY.H"
#include "ADC.H"
#include <stdio.h>
#include <stdlib.h>
void StartScreen()
{
	OLED_ShowCHinese(8,1,0);
	OLED_ShowCHinese(24,1,1);
	OLED_ShowCHinese(40,1,2); 
	OLED_ShowCHinese(56,1,3);
	OLED_ShowCHinese(72,1,4);
	OLED_ShowCHinese(88,1,5);
	OLED_ShowCHinese(104,1,6);
	OLED_ShowString(2,4," Welcome! ",16);
	OLED_Clear();
}
unsigned int last_ConNum;
void ModeSlect(unsigned int Pos)
{
	if(Pos==0)
	{
	OLED_ShowCHinese(96,4,24);
	OLED_ShowCHinese(112,4,25);
	}
	if(Pos==1)
	{
	OLED_ShowCHinese(96,4,23);
	OLED_ShowCHinese(112,4,7);

	}
	if(Pos==2)
	{
	OLED_ShowCHinese(96,4,22);
	OLED_ShowCHinese(112,4,7);

	}
	if(Pos==3)
	{
	OLED_ShowCHinese(96,4,26);
	OLED_ShowCHinese(112,4,27);
	}
	if(Pos==4)
	{
	OLED_ShowCHinese(96,4,28);
	OLED_ShowCHinese(112,4,30);

	}
	
}
void MainScreen()
{
	OLED_ShowCHinese(8,0,0);
  OLED_ShowCHinese(24,0,1);
  OLED_ShowCHinese(40,0,2); 
  OLED_ShowCHinese(56,0,3);
  OLED_ShowCHinese(72,0,4);
 	OLED_ShowCHinese(88,0,5);
	OLED_ShowCHinese(104,0,6);
	OLED_ShowString(0,2," press: ",16);
	OLED_ShowString(100,2,"kPa ",16);
	OLED_ShowString(0,4," air pump:",16);
	OLED_ShowCHinese(0,6,14);
	OLED_ShowCHinese(16,6,15);
	OLED_ShowCHinese(96,6,18);
	OLED_ShowCHinese(112,6,19);
}
void MenuSreenS0()
{
	OLED_ShowCHinese(48,2,16);//���
	OLED_ShowCHinese(64,2,17);
  OLED_ShowString(80,2,":");
	OLED_ShowCHinese(48,4,28);//ģʽ
	OLED_ShowCHinese(64,4,29);

	OLED_ShowCHinese(96,6,10);//ȷ��
	OLED_ShowCHinese(112,6,11);
	OLED_ShowCHinese(0,6,12);//����
	OLED_ShowCHinese(16,6,13);

}



unsigned int deviceNum=0;

unsigned int last_curpos;
unsigned int last_ComfirmKEYvalue;

void DeviceNumShow()
{
	NumScreen();
	OLED_ShowNum(88,2,deviceNum,2,16);
}


void ShowScreen()
{
	if(!ADC_START);
	{
		int press=ADC_DATA-105;
			if(press<0)
			{
				OLED_ShowString(55,2,"-",16);
				press=-press;
			}
			else
			{
				OLED_ShowString(55,2," ",16);
			}
		press=press/2;
		OLED_ShowNum(63,2,press/10,2,16);
		ADC_START = 1;			
	}

}