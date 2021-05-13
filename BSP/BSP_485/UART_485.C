/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-13 08:54:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_485\UART_485.C
 */


#include "CH551.H"                                                          
#include "Debug.H"
#include "UART_485.H"
#include "OLED_IIC.h"

void UART0Alter()
{
    PIN_FUNC |= bUART0_PIN_X;                                                  //����ӳ�䵽P1.2��P1.3
}
/*******************************************************************************
* Function Name  : CH554UART0RcvByte()
* Description    : CH554UART0接收一个字节
* Input          : None
* Output         : None
* Return         : SBUF
*******************************************************************************/
UINT8 DATA;
UINT8  UART0RcvByte( )
{
    // while(RI == 0);                                                            //查询接收，中断方式可不用
    // RI = 0;
    // DATA=SBUF;
    // return DATA;
    if(RI)
    {
    DATA=SBUF;
    return DATA;
    RI=0;
    }
    else
    {
    return 0;
    }
}

/*******************************************************************************
* Function Name  : CH554UART0SendByte(UINT8 SendDat)
* Description    : CH554UART0发送一个字节
* Input          : UINT8 SendDat；要发送的数据
* Output         : None
* Return         : None
*******************************************************************************/
void UART0SendByte(UINT8 SendDat)
{
    if(TI)
    {
	SBUF = SendDat;
    TI = 0; 
    }                                                            //查询发送，中断方式可不用下面2条语句,但发送前需TI=0
	// while(TI ==0);
	// TI = 0;
    // SBUF = SendDat;  
}

#if UART0_INTERRUPT
/*******************************************************************************
* Function Name  : UART0Interrupt(void)
* Description    : UART0 �жϷ������
*******************************************************************************/
void UART0Interrupt( void ) interrupt INT_NO_UART0 using 1                      //����1�жϷ������,ʹ�üĴ�����1
{
	UINT8 dat;
    
	if(RI)
	{
		DATA= SBUF;
        RI = 0;
        SBUF=DATA;
        while(!TI);
        TI = 0;
	}
    SBUF=DATA;
}

#endif

/**
 * @description: 
 * @param {UINT8} id
 * @return {*}
 */
UINT8 MsgAnalyze(UINT8 id)
{
    UINT8 cmd;
    RI=0;
    DATA=SBUF;
    if(id==((DATA&0X3C)>>2))
    {
        cmd=DATA&0x03;
        return cmd;
    }
    else
    {
        return 0;
    }
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void MsgClear()
{
    DATA=0;
}
