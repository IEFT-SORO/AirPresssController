/*
 * @Author: your name
 * @Date: 2021-05-08 14:16:40
 * @LastEditTime: 2021-05-10 09:58:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AirPressControl\BSP\BSP_MODBUS\BSP_MODBUS.h
 */
#include "CH551.H"                                                          
#include "Debug.H"
#ifndef __BSP_MODBUS_H__
#define __BSP_MODBUS_H__

typedef struct {
   UINT8  Code ;  	        // 功能码
   UINT8 byteNums; 	        // 字节数
   UINT16 Addr ;            // 操作内存的起始地址
   UINT16 Num; 	            // 寄存器或者线圈的数量
   UINT16 _CRC;       	      // CRC校验码
   UINT8 *ValueReg; 	      // 10H功能码的数据
   UINT16 *PtrHoldingbase;  // HoldingReg内存首地址
   UINT16 *PtrHoldingOffset;// HoldingReg内存首地址
}PDUData_TypeDef;

typedef struct
{
  UINT16 IN1;
	
	/* 01H 05H 读写单个强制线圈 */
	UINT16 D01;
	UINT16 D02;
	UINT16 D03;
	UINT16 D04;

}REG_VALUE;

#define MB_SLAVEADDR            0x0001
#define MB_ALLSLAVEADDR         0x00FF

#define FUN_CODE_01H            0x01  // 功能码01H 
#define FUN_CODE_02H            0x02  // 功能码02H
#define FUN_CODE_03H            0x03  // 功能码03H
#define FUN_CODE_04H            0x04  // 功能码04H
#define FUN_CODE_05H            0x05  // 功能码05H
#define FUN_CODE_06H            0x06  // 功能码06H
#define FUN_CODE_10H            0x10  // 功能码10H

/* 本例程所支持的功能码,需要添加新功能码还需要在.c文件里面添加 */
#define IS_NOT_FUNCODE(code) (!((code == FUN_CODE_01H)||\
                                (code == FUN_CODE_02H)||\
                                (code == FUN_CODE_03H)||\
                                (code == FUN_CODE_04H)||\
                                (code == FUN_CODE_05H)||\
                                (code == FUN_CODE_06H)||\
                                (code == FUN_CODE_10H)))

#define EX_CODE_NONE           0x00  // 异常码 无异常
#define EX_CODE_01H            0x01  // 异常码
#define EX_CODE_02H            0x02  // 异常码
#define EX_CODE_03H            0x03  // 异常码
#define EX_CODE_04H            0x04  // 异常码

#define COIL_D01		0x01
#define COIL_D02		0x02
#define COIL_D03		0x03
#define COIL_D04		0x04
#define COIL_DXX  	COIL_D04

#define REG_IN1		  0x0020
/* 03H 读保持寄存器 */
/* 06H 写保持寄存器 */
/* 10H 写多个保存寄存器 */
#define HOLD_REG_01		0x0010
#define HOLD_REG_02		0x0011
#define HOLD_REG_03		0x0012

/* 扩展变量 ------------------------------------------------------------------*/
extern PDUData_TypeDef PduData;

/* 函数声明 ------------------------------------------------------------------*/
UINT16 MB_CRC16(UINT8 *pushMsg,UINT8 usDataLen);
void MB_Parse_Data(void);
void MB_WriteNumHoldingReg_10H(UINT8 _addr, UINT16 _reg, UINT16 _num,UINT8 *_databuf);
UINT8 MB_Analyze_Execute(void );
UINT8 MB_JudgeNum(UINT16 _Num,UINT8 _FunCode,UINT16 ByteNum);
UINT8 MB_JudgeAddr(UINT16 _Addr,UINT16 _Num);
void MB_Exception_RSP(UINT8 _FunCode,UINT8 _ExCode);
void MB_RSP(UINT8 _FunCode);

#endif /* __BSP_MB_SLAVE_H__ */
/******************* (C) COPYRIGHT 2015-2020  *****END OF FILE****/
