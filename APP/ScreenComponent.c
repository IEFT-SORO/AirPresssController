/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-14 12:01:19
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\APP\ScreenComponent.c
 */
#include <OLED_IIC.h>
#include "Debug.H"
#include "ScreenComponent.h"
#include "KEY.H"
#include "ADC.H"
#include "UART_485.H"


void StartScreen()
{
	OLED_ShowCHinese(8,1,0);
	OLED_ShowCHinese(24,1,1);
	OLED_ShowCHinese(40,1,2); 
	OLED_ShowCHinese(56,1,3);
	OLED_ShowCHinese(72,1,4);
	OLED_ShowCHinese(88,1,5);
	OLED_ShowCHinese(104,1,6);
	OLED_Clear();
}

enum  SCREENID screen_id;
UINT8 CurPos=0;
UINT8 deviceID=0;
enum MODE temp_mode;
int press;

void MainScreen(enum MODE mode)
{
		OLED_ShowCHinese(8,0,0);
		OLED_ShowCHinese(24,0,1);
		OLED_ShowCHinese(40,0,2);
		OLED_ShowCHinese(56,0,3);
		OLED_ShowCHinese(72,0,4);
		OLED_ShowCHinese(88,0,5);
		OLED_ShowCHinese(104,0,6);
		switch(mode)
			{
			case POSITIVEPRESS:
			OLED_ShowCHinese(17,4,23);
			OLED_ShowCHinese(33,4,12);
			OLED_ShowString(49,4,":",16);
			press= FilterPress()-PRESSZERO;//TODO ADD calibration
			if(press<0)press=0;
			OLED_ShowString(90,4,"kpa",16);
			OLED_ShowString(65,4,"   ",16);
			OLED_ShowIntegerNumber(65,4,press,16);
			break;
			case NEGTIVEPRESS:
			OLED_ShowCHinese(17,4,24);
			OLED_ShowCHinese(33,4,12);
			OLED_ShowString(49,4,":",16);
			press= FilterPress()-PRESSZERO;//TODO ADD calibration
			OLED_ShowString(90,4,"kpa",16);
			OLED_ShowString(65,4,"   ",16);
			OLED_ShowIntegerNumber(65,4,press,16);
			break;
			case CLOSE:
			OLED_ShowCHinese(17,4,15);
			OLED_ShowCHinese(33,4,16);
			OLED_ShowString(49,4,":",16);
			press= FilterPress()-PRESSZERO;//TODO ADD calibration
			OLED_ShowString(90,4,"kpa",16);
			OLED_ShowString(65,4,"   ",16);
			OLED_ShowIntegerNumber(65,4,press,16);
			break;
			}
}
void MenueScreen()
{
	OLED_ShowCHinese(8,0,0);
	OLED_ShowCHinese(24,0,1);
	OLED_ShowCHinese(40,0,2);
	OLED_ShowCHinese(56,0,3);
	OLED_ShowCHinese(72,0,4);
	OLED_ShowCHinese(88,0,5);
	OLED_ShowCHinese(104,0,6);
switch(CurPos)
	{
	case 0:
	OLED_RevShowCHinese(32,2,17);
	OLED_RevShowCHinese(48,2,18);
	OLED_RevShowCHinese(64,2,21);
	OLED_RevShowCHinese(80,2,22);

	OLED_ShowCHinese(48,4,19);
	OLED_ShowCHinese(64,4,20);
	break;
	case 1:
	OLED_ShowCHinese(32,2,17);
	OLED_ShowCHinese(48,2,18);
	OLED_ShowCHinese(64,2,21);
	OLED_ShowCHinese(80,2,22);

	OLED_RevShowCHinese(48,4,19);
	OLED_RevShowCHinese(64,4,20);
	break;
	}

	OLED_ShowCHinese(8,6,9);
	OLED_ShowCHinese(24,6,10);

	OLED_ShowCHinese(88,6,7);
	OLED_ShowCHinese(104,6,8);

}
void DeviceNumScreen()
{
	OLED_ShowCHinese(8,0,0);
	OLED_ShowCHinese(24,0,1);
	OLED_ShowCHinese(40,0,2);
	OLED_ShowCHinese(56,0,3);
	OLED_ShowCHinese(72,0,4);
	OLED_ShowCHinese(88,0,5);
	OLED_ShowCHinese(104,0,6);

	OLED_ShowCHinese(32,3,17);
	OLED_ShowCHinese(48,3,18);
	OLED_ShowCHinese(64,3,21);
	OLED_ShowCHinese(80,3,22);

	OLED_ShowString(96,3,":",16);
	OLED_ShowString(104,3,"   ",16);
	OLED_ShowIntegerNumber(104,3,deviceID,16);

	OLED_ShowCHinese(8,6,9);
	OLED_ShowCHinese(24,6,10);
}


enum MODE keytask(enum SCREENID id)//TODO fix key status
{
switch(id)
	{
		case MAIN:
			MainScreen(temp_mode);
			if(Button_Inquice_State(KEY2)==Button_Bit_Press)
			{
				PositivepressMode();
				temp_mode=POSITIVEPRESS;
			}
			if(Button_Inquice_State(KEY3)==Button_Bit_Press)
			{
				NegtivepressMode();
				temp_mode=NEGTIVEPRESS;
			}
			if(Button_Inquice_State(KEY1)==Button_Bit_Press)
			{
				SilenceMode();
				temp_mode=CLOSE;
			}
			if( Button_Inquice_State(KEY1)==Button_Bit_Long)
			{
				screen_id=MENU;
				OLED_Clear();
			}
		break;
			return temp_mode;
		case MENU:
			
			MenueScreen();
			if(Button_Inquice_State(KEY3)==Button_Bit_Press)
			{
				CurPos++;
				if(CurPos>2)
				{
					CurPos=0;
				}
			}
			if(Button_Inquice_State(KEY1)==Button_Bit_Press)
			{
				screen_id=NUMID;
				OLED_Clear();
			}
			if(Button_Inquice_State(KEY2)==Button_Bit_Press)
			{
				CurPos=0;
				screen_id=MAIN;
				OLED_Clear();
			}
		break;
		case NUMID:
			DeviceNumScreen();
			if(Button_Inquice_State(KEY1)==Button_Bit_Press)
			{
				deviceID--;
			if(deviceID<0)
			{
				deviceID=0;
			}
			}
			if(Button_Inquice_State(KEY3)==Button_Bit_Press)
			{
				deviceID++;
			}
			if(deviceID>16)
			{
				deviceID=0;
			}
			if(Button_Inquice_State(KEY2)==Button_Bit_Press)
			{
				CurPos=0;
				screen_id=MENU;
				OLED_Clear();
			}
		break;
		case ABOUT:
		if(Button_Inquice_State(KEY1)==Button_Bit_Press)
			{
			}
			if(Button_Inquice_State(KEY3)==Button_Bit_Press)
			{
			}
			if(Button_Inquice_State(KEY2)==Button_Bit_Press)
			{
				OLED_Clear();
			}
		break;
	}
}

void TaskInit()
{

	OLED_Init();	
	OLED_Clear();  
	KeyInit();
	ValvePumpInit(); 
	ADCInit( 1 );  
	mInitSTDIO( );
	screen_id=MAIN;
	deviceID=0;
	temp_mode=CLOSE;
}

void CtrlRun(UINT8 cmd)
{
	switch (cmd)
	{
		case 0x01:
		PositivepressMode();
		temp_mode=POSITIVEPRESS;
		break;
		case 0x02:
		NegtivepressMode();
		temp_mode=NEGTIVEPRESS;
		break;
		case 0x03:
		SilenceMode();
		temp_mode=CLOSE;
		break;
	}
}
void Msgprcess()
{
		UINT8 cmd=0;
	if(RI)
	{
		cmd=MsgAnalyze(deviceID);
		CtrlRun(cmd);
	}
	MsgClear();
}
void TaskRun()
{
	keytask(screen_id);
	Msgprcess();
}





