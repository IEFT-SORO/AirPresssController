/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-12 17:28:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_485\UART_485.H
 */

#include "CH551.H"                                                          
#include "Debug.H"
#ifndef	__UART_485_H__
#define __UART_485_H__

#define UART0_INTERRUPT   0          //定义是否使用接收中断接收数据
#define UART0_PINMAP      0         //定义串口是否开启引脚映射。

UINT8   MsgAnalyze(UINT8 id);
void UART0SendByte(UINT8 SendDat);
UINT8  UART0RcvByte( );

void MsgClear();
#endif