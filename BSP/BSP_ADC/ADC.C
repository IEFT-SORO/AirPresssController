
/********************************** (C) COPYRIGHT *******************************
* File Name          : ADC.C
* Author             : WCH
* Version            : V1.0
* Date               : 2019/07/22
* Description        : CH554 ADC����ʱ�����ã�ADCͨ�����ú�������ѹ�Ƚ�ģʽ���� 
*******************************************************************************/

#include "CH551.H"                                                          
#include "Debug.H"
#include "ADC.H"

#pragma  NOAREGS

#define ADC_INTERRUPT  1
UINT16 AdcData;
sbit press_adcpin=P3^2;
/*******************************************************************************
* Function Name  : ADCInit(UINT8 div)
* Description    : ADC����ʱ������,ģ�鿪�����жϿ���
* Input          : UINT8 div ʱ������ 
                   1 ��  384��Fosc                   								
                   0 ��  96��Fosc									 
* Output         : None
* Return         : None
*******************************************************************************/
void ADCInit(UINT8 div)
{
    Port3Cfg(0,2);//P3^2
    ADC_CFG &= ~bADC_CLK | div;
    ADC_CFG |= bADC_EN;                                                        //ADC��Դʹ��
#if ADC_INTERRUPT
    ADC_IF = 0;                                                                //����ж�
    IE_ADC = 1;                                                                //ʹ��ADC�ж�
#endif
    ADC_ChannelSelect(3);
    ADC_START = 1;
}

/*******************************************************************************
* Function Name  : ADC_ChannelSelect(UINT8 ch)
* Description    : ADC��������
* Input          : UINT8 ch ����ͨ��
* Output         : None
* Return         : �ɹ� SUCCESS
                   ʧ�� FAIL
*******************************************************************************/
UINT8 ADC_ChannelSelect(UINT8 ch)
{
    if(ch == 0){ADC_CHAN1 =0;ADC_CHAN0=0;P1_DIR_PU &= ~bAIN0;}                 //AIN0
    else if(ch == 1){ADC_CHAN1 =0;ADC_CHAN0=1;P1_DIR_PU &= ~bAIN1;}            //AIN1
    else if(ch == 2){ADC_CHAN1 =1;ADC_CHAN0=0;P1_DIR_PU &= ~bAIN2;}            //AIN2
    else if(ch == 3){ADC_CHAN1 =1;ADC_CHAN0=1;P3_DIR_PU &= ~bAIN3;}            //AIN3
    else return FAIL;
    return SUCCESS;
}

/*******************************************************************************
* Function Name  : VoltageCMPModeInit()
* Description    : ��ѹ�Ƚ���ģʽ��ʼ��
* Input          : UINT8 fo ����˿� 0\1\2\3
                   UINT8 re ����˿� 1\3
* Output         : None
* Return         : �ɹ� SUCCESS
                   ʧ�� FAIL
*******************************************************************************/
UINT8 VoltageCMPModeInit(UINT8 fo,UINT8 re)
{
    ADC_CFG |= bCMP_EN;                                                        //��ƽ�Ƚϵ�Դʹ��
    if(re == 1){
      if(fo == 0) {ADC_CHAN1 =0;ADC_CHAN0=0;CMP_CHAN =0;}                      //AIN0��AIN1
      else if(fo == 2) {ADC_CHAN1 =1;ADC_CHAN0=0;CMP_CHAN =0;}                 //AIN2��AIN1
      else if(fo == 3) {ADC_CHAN1 =1;ADC_CHAN0=1;CMP_CHAN =0; }                //AIN3��AIN1			
      else return FAIL;
    }			     
    else if(re == 3){
      if(fo == 0) {ADC_CHAN1 =0;ADC_CHAN0=0;CMP_CHAN =0;}                      //AIN0��AIN1
      else if(fo == 1) {ADC_CHAN1 =0;ADC_CHAN0=1;CMP_CHAN =0;}                 //AIN1��AIN1
      else if(fo == 2) {ADC_CHAN1 =1;ADC_CHAN0=0;CMP_CHAN =0;}                 //AIN2��AIN1			
      else return FAIL;
    }
    else return FAIL;
#if ADC_INTERRUPT
    CMP_IF = 0;                                                                //����ж�
    IE_ADC = 1;                                                                //ʹ��ADC�ж�
#endif

     return SUCCESS;
}

#if ADC_INTERRUPT
/*******************************************************************************
* Function Name  : ADCInterrupt(void)
* Description    : ADC �жϷ������
*******************************************************************************/
void	ADCInterrupt( void ) interrupt INT_NO_ADC using 1                       //ADC�жϷ������,ʹ�üĴ�����1
{ 
    if(ADC_IF ==  1)                                                          //ADC����ж�
    { 
      AdcData = ADC_DATA;                                                    //ȡ��ADC��������
      ADC_IF = 0;		                                                          //���ADC�жϱ�־
//	  printf(" %d ",UserData);
    }
    if(CMP_IF ==  1)                                                          //��ѹ�Ƚ�����ж�
    {	
//       UserData = ADC_CTRL&0x80 >> 7);	                                        //����Ƚ������		
      CMP_IF = 0;		                                                          //��ձȽ�������ж�
    }
}
#endif

