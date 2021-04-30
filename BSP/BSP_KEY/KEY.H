/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-04-30 11:13:12
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_KEY\KEY.H
 */
#ifndef	__KEY_H__
#define __KEY_H__

void ConfigT0(UINT8 ms);
void KeyInit(void);
UINT8 GetKeyStation(UINT8 i);
unsigned long GetKeyDOWNTim(UINT8 i);

#endif