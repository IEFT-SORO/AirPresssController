/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-14 15:03:41
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

/**
  * @brief  按键读取
  * @param  NULL
  * @retval 1  : 按下
  * @retval 0 : 弹起
***/
UINT8 GetKeyStation(UINT8 i)
{
	if(KeyState[i])
	{
		KeyState[i]=0;
	}
	else{
		KeyState[i]=1;
	}
	return  KeyState[i];
}
Button_Typedef KEY[KEYNUM];

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
	UINT8 i=0;
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
/**
  * @brief  按键定时扫描
  * @param  NULL
  * @retval NULL
***/
void Button_Scan_ms(UINT32 _time)
{
	int i=0;
	for(i=0; i<KEYNUM; i++)
	{
		//提取按键
		KEY[i].level = GetKeyStation(i);

		//按键状态处理
		switch(KEY[i].state)
		{
			//状态_弹起
			case Button_Bit_Up:
				if(KEY[i].level){
					KEY[i].state = Button_Bit_Shake;
					KEY[i].time_ms = 0;
				}
			break;
			//状态_抖动
			case Button_Bit_Shake:
				if(KEY[i].level){
					KEY[i].time_ms += _time;
					if(KEY[i].time_ms > Button_Shake_Time)
					{
						KEY[i].state = Button_Bit_Drop;
						KEY[i].time_ms = 0;
					}
				}
				else{
					KEY[i].state = Button_Bit_Up;
					KEY[i].time_ms = 0;
				}
			break;
			//状态_按下
			case Button_Bit_Press:
				if(KEY[i].level){
					KEY[i].time_ms += _time;
					if(KEY[i].time_ms > Button_Long_Time)
					{
						KEY[i].state = Button_Bit_LongDrop;
						KEY[i].time_ms = 0;
					}
				}
				else{
					KEY[i].state = Button_Bit_Rise;
					KEY[i].time_ms = 0;
				}
			break;
			//状态_长按
			case Button_Bit_Long:
				if(KEY[i].level){
					KEY[i].state = Button_Bit_Long;
				}
				else{
					KEY[i].state = Button_Bit_LongRise;
				}
			break;
			//边沿_按下
			case Button_Bit_Drop:
				if(KEY[i].level){
					KEY[i].state = Button_Bit_Press;
					KEY[i].time_ms = 0;
				}
				else{
					KEY[i].state = Button_Bit_Up;
				}
			break;
			//边沿_弹起
			case Button_Bit_Rise:
				KEY[i].state = Button_Bit_Up;
			break;
			//边沿_长按按下
			case Button_Bit_LongDrop:
				if(KEY[i].level){
					KEY[i].state = Button_Bit_Long;
					KEY[i].time_ms = 0;
				}
				else{
					KEY[i].state = Button_Bit_Up;
				}
			break;
			//边沿_长按弹起
			case Button_Bit_LongRise:
				KEY[i].state = Button_Bit_Up;
			break;
		}	
	}
}
void InterruptTimer0() interrupt INT_NO_TMR0 using 2
{
	TH0 = T0RH;
	TL0 = T0RL;
	KeyScan(); 
	Button_Scan_ms(Button_Shake_Time);
}

void KeyInit()
{
		UINT8 i=0;
	ConfigT0(20); 
	Port1Cfg(1,1);//key1
	Port1Cfg(1,4);//key2
	Port1Cfg(1,5);//key3
	key1 = 1;
	key2 = 1;
	key3 = 1;
	for(i=0; i<KEYNUM; i++)
	{
		//数据
		KEY[i].level = 0;
		KEY[i].state = Button_Bit_Up;
		KEY[i].time_ms = 0;
	}
}

/**
  * @brief  获取按键状态
  * @param  NULL
  * @retval NULL
***/
Button_State_Typedef Button_Inquice_State(UINT8 button_num)
{
	if(button_num < KEYNUM)
	{
		return KEY[button_num].state;
	}
	else
	{
		return Button_Bit_Up;
	}
}