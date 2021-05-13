/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-13 09:27:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_KEY\KEY.H
 */
#ifndef	__KEY_H__
#define __KEY_H__
#define KEY1 0
#define KEY2 1
#define KEY3 2
#define PressTime 500
void ConfigT0(UINT8 ms);
void KeyInit(void);
UINT8 GetKeyStation(UINT8 i);
UINT8 KeyPressLong(UINT8 i);
#endif