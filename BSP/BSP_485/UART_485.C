/*
 * @Author: your name
 * @Date: 2021-04-30 09:38:30
 * @LastEditTime: 2021-05-11 11:17:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_485\UART_485.C
 */


#include "CH551.H"                                                          
#include "Debug.H"
#include "UART_485.H"
#include "OLED_IIC.h"
enum MSG_FLG msg_flg;
UINT8 Rx_Buf[BUFMAXSIZE];    
UINT8 Tx_Buf[10];       
UINT16 RxCount;  

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
UINT8  UART0RcvByte( )
{
    while(RI == 0);                                                            //查询接收，中断方式可不用
    RI = 0;
    return SBUF;
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
	SBUF = SendDat;                                                              //查询发送，中断方式可不用下面2条语句,但发送前需TI=0
	while(TI ==0);
	TI = 0;
}
UINT8 RXDAT;
#if UART0_INTERRUPT
/*******************************************************************************
* Function Name  : UART0Interrupt(void)
* Description    : UART0 �жϷ������
*******************************************************************************/
void UART0Interrupt( void ) interrupt INT_NO_UART0 using 1                       //����1�жϷ������,ʹ�üĴ�����1
{
	UINT8 dat;

    
	if(RI)
	{
		dat= SBUF;
		RI = 0;
        UART0SendByte(dat); 
        RXDAT=dat;
	}
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
    UINT8 temp;
    temp=RXDAT;
    if(id==((temp&0X3C)>>2))
    {
        cmd=RXDAT&0x03;
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
    RXDAT=0;
}
