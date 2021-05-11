/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-10 16:38:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_KEY\KEY.C
 */

#include "CH551.H"                                                          
#include "Debug.H"
#include "KEY.H"

#pragma  NOAREGS

sbit key1=P1^1;
sbit key2=P1^4;
sbit key3=P1^5;

UINT8 KeyState[3] = {1,1,1};     
unsigned long  KeyDownTime[3]= {0, 0, 0};


UINT8 GetKeyStation(UINT8 i)
{
	return  KeyState[i];
}
UINT8 KeyPressLong(UINT8 i)
{
	UINT8 PressLong;
	if(KeyDownTime[i]>PressTime)
	{
	PressLong=1;
	}
	else
	{
	PressLong=0;
	}
return PressLong;
}


UINT8 T0RH = 0;	
UINT8 T0RL = 0;	

void ConfigT0(UINT8 ms)
{
    unsigned long tmp = 0;

	tmp = 12000000/12;
	tmp = (tmp * ms)/1000;
	tmp = 65536 - tmp;
	tmp = tmp + 1;
    T0RH = (UINT8)(tmp >> 8);
	T0RL = (UINT8)tmp;

	TMOD = ( TMOD & ~( bT0_GATE | bT0_CT | bT0_M1 ) ) | bT0_M0;
	TH0 = T0RH;
	TL0 = T0RL;
	TF0 = 0;
	ET0 = 1;
	TR0 = 1;
}

void KeyScan()
{
	UINT8 i;
	static UINT8 keybuffer[3] = {0xFF,0xFF,0xFF};

	keybuffer[0] = (keybuffer[0] <<1) | key1;
	keybuffer[1] = (keybuffer[1] <<1) | key2;
	keybuffer[2] = (keybuffer[2] <<1) | key3;

	for(i=0;i<3;i++)
	{
		if((keybuffer[i] & 0x0F) == 0x00)
		{
			KeyState[i] = 0;
			if(i>=3)
			    break;
			KeyDownTime[i] += 10;  
		}
		else if((keybuffer[i] & 0x0F) == 0x0F)
		{
			KeyState[i] = 1;
			if(i>=3)
			    break;
			KeyDownTime[i] = 0;  
		}
	} 
}

void InterruptTimer0() interrupt INT_NO_TMR0 using 1
{
	TH0 = T0RH;
	TL0 = T0RL;
	KeyScan(); 
}

void KeyInit()
{
	ConfigT0(200); 
	Port1Cfg(3,1);//key1
	Port1Cfg(3,4);//key2
	Port1Cfg(3,5);//key3
	key1 = 1;
	key2 = 1;
	key3 = 1;
}