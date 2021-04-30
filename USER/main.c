/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-04-30 17:39:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\USER\main.c
 */
#include <CH551.H>
#include "Debug.H"
#include "KEY.H"
#include <OLED_IIC.h>
#include <intrins.h>
#include "ADC.H"
#include "IO.H"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ScreenComponent.h"
#pragma  NOAREGS
float airpress;
void main()
{
	
	CfgFsys(); 
	mDelaymS(5);
	ConfigT0(8); 
	OLED_Init();	
	OLED_Clear();  
	KeyInit();
	ValvePumpInit();
	ADCInit( 1 );  
	EA = 1; 
	StartScreen();
	ADC_ChannelSelect( 3 );                                         
	ADC_START = 1;

	while(1)
	{
		OLED_RevShowCHinese(2,0,26);
		mDelaymS(1000);
		airpress=ADC_DATA/255*1000;
		OLED_ShowCHinese(2,0,26);
		mDelaymS(1000);
	}
}
