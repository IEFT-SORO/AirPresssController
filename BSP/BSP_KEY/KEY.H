/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-14 13:06:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_KEY\KEY.H
 */
#include <stdlib.h>		//变量类型,宏,通用工具函数
#ifndef	__KEY_H__
#define __KEY_H__
#define KEY1 0
#define KEY2 1
#define KEY3 2
#define KEYNUM 3
//识别配置
#define Button_Shake_Time	20		//ms去抖时间
#define Button_Long_Time	1000	//ms长按触发时间

typedef enum{
	//保持状态
	Button_Bit_Up = 0,			//状态_弹起
	Button_Bit_Shake,				//状态_抖动
	Button_Bit_Press,				//状态_按下
	Button_Bit_Long,				//状态_长按
	//边沿状态
	Button_Bit_Drop,				//边沿_按下
	Button_Bit_Rise,				//边沿_弹起
	Button_Bit_LongDrop,		//边沿_长按按下
	Button_Bit_LongRise,		//边沿_长按弹起
}Button_State_Typedef;

typedef struct{
	//数据
	UINT8									level;		//按键水平
	Button_State_Typedef	state;		//按键状态
	UINT32							time_ms;	//按下时间
}Button_Typedef;

void ConfigT0(UINT8 ms);
void KeyInit(void);
Button_State_Typedef Button_Inquice_State(UINT8 button_num);
#endif