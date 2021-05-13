/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-12 13:27:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\USER\main.c
 */
#include <CH551.H>
#include "Debug.H"
#include "ScreenComponent.h"
#include "UART_485.H"
#pragma  NOAREGS

void main()
{
	
	CfgFsys(); 
	mDelaymS(5); 
	EA = 1;  
	TaskInit();
	
	while(1)
	{
	TaskRun();
	}
}
