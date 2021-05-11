/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-11 10:52:18
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_485\UART_485.H
 */

#include "CH551.H"                                                          
#include "Debug.H"
#ifndef	__UART_485_H__
#define __UART_485_H__

#define UART0_INTERRUPT   1          //定义是否使用接收中断接收数据
#define UART0_PINMAP      0         //定义串口1是否开启引脚映射。不开启选择P16(R)、P17(T)。开启选择P34(R)、P32(T)
#define BUFMAXSIZE        3

enum MSG_FLG
{
	MSGSTAR, 
	MSGEND,
    MSGIDE
};   
                   
UINT8   MsgAnalyze(UINT8 id);
void UART0SendByte(UINT8 SendDat);
void MsgClear();
#endif