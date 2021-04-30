/*
 * @Author: your name
 * @Date: 2021-04-30 09:42:58
 * @LastEditTime: 2021-04-30 11:14:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_IO\IO.c
 */
#include "CH551.H"    
#include "Debug.H"
#include "IO.h"

#pragma  NOAREGS

sbit valve1 = P1^6;
sbit valve2 = P1^7;
sbit valve3 = P1^0;
sbit pump = P3^5;

void SilenceMode()
{
	valve1=0;
	valve2=0;
	valve3=0;
	pump=0;
}

void OpenpumpMode()
{
	valve1=0;
	valve2=1;
	valve3=0;
	pump=1;
}
void PositivepressMode()
{
	valve1=1;
	valve2=0;
	valve3=1;
	pump=1;
}
void NegtivepressMode()
{
	valve1=0;
	valve2=1;
	valve3=1;
	pump=1;
}
void HoldeMode()
{
	valve1=0;
	valve2=0;
	valve3=1;
	pump=1;
}
void ExhaustMode()
{
	valve1=1;
	valve2=1;
	valve3=1;
	pump=1;
}
void ValvePumpInit()
{
	Port1Cfg(1,6);//valve1
	Port1Cfg(1,7);//valve2
	Port1Cfg(1,0);//valve3
	Port3Cfg(1,5);
	valve1 = 0;
	valve2 = 0;
	valve3 = 0;
	pump = 0;
}
