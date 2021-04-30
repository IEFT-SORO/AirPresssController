/*
 * @Author: your name
 * @Date: 2021-04-30 09:43:14
 * @LastEditTime: 2021-04-30 14:46:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_IO\IO.h
 */
#include "CH551.H"    
#include "Debug.H"
#ifndef	__IO_H__
#define __IO_H__

void SilenceMode();
void OpenpumpMode();	
void PositivepressMode();	
void NegtivepressMode();
void HoldeMode();
void ExhaustMode();

void ValvePumpInit();
#endif