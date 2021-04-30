#include <OLED_IIC.h>
#include <OledFont.h>
#include <intrins.h>
#include <math.h>
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 

sbit IIC_SCL=P3^4;
sbit IIC_SDA=P3^3;




//����һ���ֽ�
void Send_Byte(unsigned char c)
{
	unsigned char dat;
	unsigned char i=0;
	dat = c;
	for(i=0;i<8;i++)
	{    
    IIC_SCL=0; 
		_Nop();
		if(dat&0x80)
			IIC_SDA=1;
     else  
			IIC_SDA=0;
		 dat <<= 1;
		IIC_SCL=1; 
		_Nop(); 
	}
	IIC_SCL=0; 
}
void Write_IIC_Command(unsigned char IIC_Command)
{
		Start_I2c();
		Send_Byte(0x78);//д��ӻ���ַ��SD0 = 0.
		Read_ACK();
		Send_Byte(0x00);//д������
		Read_ACK();
		Send_Byte(IIC_Command);//����
		Read_ACK();
		Stop_I2c();  //����ֹͣ�ź�
}
//
void Write_IIC_Data(unsigned char IIC_Data)
{
		Start_I2c();
		Send_Byte(0x78);	//д��ӻ���ַ��SD0 = 0
		Read_ACK();
		Send_Byte(0x40);	//д������
		Read_ACK();
		Send_Byte(IIC_Data);//����
		Read_ACK();
		Stop_I2c();		//����ֹͣ�ź�
}

void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{
	if(cmd) 
	  {
       Write_IIC_Data(dat); 
	  }
	else {
       Write_IIC_Command(dat); 
	}
}
//

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);//д��ҳ��ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);//д���е͵�ַ
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);  //д���иߵ�ַ
}   	  



void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //����OLED��ɱ�
	OLED_WR_Byte(0X14,OLED_CMD);  //ʹ�ܣ���
	OLED_WR_Byte(0XAF,OLED_CMD);  //����ʾ
}



void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //����OLED��ɱ�
	OLED_WR_Byte(0X10,OLED_CMD);  //ʧ�ܣ���
	OLED_WR_Byte(0XAE,OLED_CMD);  //����ʾ
}		   			 


  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //�������
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //��0~7ҳ����д��
		OLED_WR_Byte (0x00,OLED_CMD);      //�е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //�иߵ�ַ  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); //д�� 0 ����
	}
}
unsigned int OLED_GRAM[144][8];
//�����Դ浽OLED	
void OLED_Refresh(void)
{
	unsigned int i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}

void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';		
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)// 16 = 8*16
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	// 6 = 6*8
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

unsigned long oled_pow(unsigned char m,unsigned char n)
{
	unsigned long result=1;	 
	while(n--)result*=m;    
	return result;
}				  
	  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;  //�������
	unsigned char enshow=0;		//�������
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;//ȡ����������ÿ��λ���ɸߵ���
		if(enshow==0&&t<(len-1)) //enshow���Ƿ�Ϊ��һ������t<(len-1)���ж��Ƿ�Ϊ���һ����
		{
			if(temp==0) //�������Ϊ0 
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);//��ʾ 0 ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
				continue; //����ʣ����䣬�����ظ�ѭ���������ظ���ʾ��
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); //��ʾһ��λ��x+(size2/2)*t���������Сƫ�Ƶ�������8��
	}
} 

void OLED_ShowIntegerNumber(unsigned char x,unsigned char y,int num,unsigned char Char_Size)
{
	unsigned char len=0;
	int buf=num;
	while(buf)
	{
		len++;
		buf/=10;
	}
	if(num>0)
		OLED_ShowNum(x,y,num,len,Char_Size);
	else
	{
		OLED_ShowChar(x,y,'-',Char_Size);
		num=abs(num);
		if(Char_Size==16)
			OLED_ShowNum(x+8,y,num,len,Char_Size);
		else
			OLED_ShowNum(x+6,y,num,len,Char_Size);
	}
}

void OLED_ShowFloatNumber(unsigned char  x,unsigned char  y,float num,unsigned char  Char_Size)
{
	unsigned char zheng_len=0,xiao_len=0,polarity_flag=0;
	int zheng=0,xiao=0;		//经读者“迷迷惘惘”提醒，为这两行局部变量赋值
	//附注：为防止程序运行过程中程序行为异常，需要对局部变量赋值
	if(num>0)
		polarity_flag=1;
	else
	{
		polarity_flag=0;
		num=-num;
	}
	zheng=(int)num;
	xiao=((num-zheng)*100)/1;	//显示小数点后两位
	while(zheng)	//计算整数部分位数
	{
		zheng_len++;
		zheng/=10;
	}
	xiao_len=2;
	zheng=(int)num;	//在计算整数部分数值时，原赋值被篡改，这里重新赋值
	if(polarity_flag)
	{	
		if(Char_Size==16)
		{
			OLED_ShowNum(x,y,zheng,zheng_len,Char_Size);
			OLED_ShowChar(x+zheng_len*8,y,'.',Char_Size);
			OLED_ShowNum(x+(zheng_len+1)*8,y,xiao,xiao_len,Char_Size);
		}
		else
		{
			OLED_ShowNum(x,y,zheng,zheng_len,Char_Size);
			OLED_ShowChar(x+zheng_len*6,y,'.',Char_Size);
			OLED_ShowNum(x+(zheng_len+1)*6,y,xiao,xiao_len,Char_Size);
		}
	}
	else
	{
		OLED_ShowChar(x,y,'-',Char_Size);
		if(Char_Size==16)
		{
			OLED_ShowNum(x+8,y,zheng,zheng_len,Char_Size);
			OLED_ShowChar(x+(zheng_len+1)*8,y,'.',Char_Size);
			OLED_ShowNum(x+(zheng_len+2)*8,y,xiao,xiao_len,Char_Size);
		}
		else
		{
			OLED_ShowNum(x+6,y,zheng,zheng_len,Char_Size);
			OLED_ShowChar(x+(zheng_len+1)*6,y,'.',Char_Size);
			OLED_ShowNum(x+(zheng_len+2)*6,y,xiao,xiao_len,Char_Size);
		}
	}
}


void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char  Char_Size)
{
	unsigned char j=0; //�������
	while (chr[j]!='\0') //����������һ���ַ�
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size); //��ʾ�ַ�
			x+=8; //������8 ��һ���ַ�������ռ8
		if(x>128){x=0;y+=2;} //���x����128���л�ҳ���Ӹ�ҳ�ĵ�һ����ʾ
			j++; //��һ���ַ�
	}
}
void OLED_RevShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{
	unsigned char t,adder=0; 
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++) 
		{
				OLED_WR_Byte(~Hzk[2*no][t],OLED_DATA);
				adder+=1; 
     }	
		OLED_Set_Pos(x,y+1); 
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(~Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }
}
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0; 
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++) 
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1; 
     }	
		OLED_Set_Pos(x,y+1); 
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }
				
}

void OLED_Showdecimal(unsigned char x,unsigned char y,float num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp,len1,temp1;
	float temp2;
	unsigned char enshow=0;
    if(num < 0)
	{
		OLED_ShowChar(x,y,'0'- 3,size2);
		num =fabs(num);
	}
    else
	OLED_ShowChar(x,y,' ',size2);//
	temp1 = (int)temp;
	temp2 = num - temp1;
	len1 = len - 6;
	OLED_ShowChar(x + size2/2*4,y,'0'- 2,size2);
	x = x + size2/2;
	for(t=0;t<len1;t++)
	{
		temp=(int)((num/oled_pow(10,len1-t-1)))%10;
		if(enshow==0&&t<(len1-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
	OLED_ShowChar(x+(size2/2)*4,y,((int)(temp2*10)%10) + '0',size2);
	OLED_ShowChar(x+(size2/2)*5,y,((int)(temp2*100)%10) + '0',size2); 
	OLED_ShowChar(x+(size2/2)*6,y,((int)(temp2*1000)%10) + '0',size2); 
	OLED_ShowChar(x+(size2/2)*7,y,((int)(temp2*10000)%10) + '0',size2); 
}
void OLED_Show_Decimal(unsigned char x,unsigned char y,float num,unsigned char z_len,unsigned char f_len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow;
	int z_temp,f_temp;      
	z_temp=(int)num;
	//整数部分
	for(t=0;t<z_len;t++)
	{
		temp=(z_temp/oled_pow(10,z_len-t-1))%10;
		if(enshow==0 && t<(z_len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else
			enshow=1;
		}
		OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
	//小数点
	OLED_ShowChar(x+(size2/2)*(z_len),y,'.',size2); 
	
	f_temp=(int)((num-z_temp)*(oled_pow(10,f_len)));
  //小数部分
	for(t=0;t<f_len;t++)
	{
		temp=(f_temp/oled_pow(10,f_len-t-1))%10;
		OLED_ShowChar(x+(size2/2)*(t+z_len)+5,y,temp+'0',size2); 
	}
}

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0; //�������
 unsigned char x,y; //�������
  
  if(y1%8==0) y=y1/8;   //�ж���ֹҳ�Ƿ�Ϊ8��������
  else y=y1/8+1;
	for(y=y0;y<y1;y++) //����ʼҳ��ʼ��������ֹҳ
	{
		OLED_Set_Pos(x0,y); //��ҳ����ʼ�п�ʼ��
    for(x=x0;x<x1;x++) //��x1 - x0 ��
	    {
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	//��ͼƬ�ĵ�    	
	    }
	}
} 


void OLED_Init(void)
{
	char i;
	for(i = 0; i < 100; i++)
	{
		_Nop();
	}
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_Clear();        //����
	OLED_Set_Pos(0,0); 	 //��������д�����ʼ�С���
}  
//


void OLED_Scroll(unsigned char x, unsigned char y)
{
	OLED_WR_Byte(0x2E,OLED_CMD);	//�رչ���
	OLED_WR_Byte(0x27,OLED_CMD);	//ˮƽ�������
	OLED_WR_Byte(0x00,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(x,OLED_CMD);	//��ʼҳ 0
	OLED_WR_Byte(0x00,OLED_CMD);	//����ʱ����
	OLED_WR_Byte(y,OLED_CMD);	//��ֹҳ 1
	OLED_WR_Byte(0x00,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(0xFF,OLED_CMD);	//�����ֽ�
	OLED_WR_Byte(0x2F,OLED_CMD);	//��������
}

void OLED_CloseScroll()
{
	OLED_WR_Byte(0x2E,OLED_CMD);	//�رչ���
}

void OLED_Upmove()
{
	OLED_WR_Byte(0x2e,OLED_CMD);        //�رչ���
	OLED_WR_Byte(0x29,OLED_CMD);        //ˮƽ��ֱ��ˮƽ��������������� 2a/29
	OLED_WR_Byte(0x00,OLED_CMD);        //�����ֽ�
	OLED_WR_Byte(0x00,OLED_CMD);        //��ʼҳ0
	OLED_WR_Byte(0x07,OLED_CMD);        //����ʱ����
	OLED_WR_Byte(0x07,OLED_CMD);        //��ֹҳ
	OLED_WR_Byte(0x01,OLED_CMD);        //ƫ����
	OLED_WR_Byte(0x2F,OLED_CMD);	      //��������
}


