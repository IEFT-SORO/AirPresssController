/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-11 11:05:43
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\APP\ScreenComponent.h
 */
#ifndef	__SCREENCOMPONENT_H__
#define __SCREENCOMPONENT_H__

#define PRESSZERO 125.5

enum MODE
{
	POSITIVEPRESS=1, 
	NEGTIVEPRESS, 
	CLOSE
};
enum SCREENID
{
	MAIN,
	MENU,
	NUMID,
	ABOUT
};


void TaskRun();
void TaskInit();

#endif