#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AHT20-21_DEMO_V1_3.h"
#include <stdio.h>


int main(void)
{
	
		Init_I2C_Sensor_Port();//��ʼ��SDA��SCL��IO�ڵĺ���
		uint32_t CT_data[2];
		volatile int  c1,t1;
		Delay_1ms(500);
		OLED_Init();//��ʼ��OLED
		if((AHT20_Read_Status()&0x18)!=0x18)
		{
			AHT20_Start_Init(); //���³�ʼ���Ĵ���
			Delay_1ms(10);
		}
		
		OLED_ShowCN(1,1,4);
		OLED_ShowCN(1,2,5);
		OLED_ShowCN(1,3,6);


		OLED_ShowCN(2,1,0); 		//��2�е�1�е�����ģ���0���� ��
		OLED_ShowCN(2,2,1); 		//��2�е�2�е�����ģ���1���� ��
		OLED_ShowCN(2,3,2);			//��2�е�3�е�����ģ���1���� ��
		OLED_ShowCN(2,4,3);			//��2�е�4�е�����ģ���1���� ��
		
		
		OLED_ShowCN(3,1,7);
		OLED_ShowCN(3,2,8);
		OLED_ShowCN(4,1,9);
		OLED_ShowCN(4,2,8);
		
		
		
		OLED_ShowString(3,6,":"); 
//		OLED_ShowCN(4,1,2);
//		OLED_ShowCN(4,2,4);
		OLED_ShowString(4,6,":"); 
		OLED_ShowString(3,7,"27.31");
		OLED_ShowString(4,7,"56.72");
		
		
		while(1)
		{
				OLED_WriteCommand(0x2E); //�رչ���
				OLED_WriteCommand(0x26); //���ҹ�����27������
				OLED_WriteCommand(0x00); //�����ֽ�
				OLED_WriteCommand(0x00); //��ʼҳ ����Ϊ0
				OLED_WriteCommand(0x07); //�����ٶ�
				OLED_WriteCommand(0x03); //��ֹҳ ����Ϊ3��Ҳ����֮���������ѧ��
				OLED_WriteCommand(0x00); //�����ֽ�
				OLED_WriteCommand(0xFF); //�����ֽ�
				OLED_WriteCommand(0x2F); //��������

	
				//AHT20_Read_CTdata(CT_data);       
				AHT20_Read_CTdata_crc(CT_data);   
		
				while(CT_data[0]==0x00&&CT_data[1]==0x00) 
				{
					AHT20_Read_CTdata_crc(CT_data);//crcУ��󣬶�ȡAHT20���¶Ⱥ�ʪ������
				}
				c1 = CT_data[0]*100*10/1024/1024;  
				t1 = CT_data[1]*200*10/1024/1024-500;
				
				////��һ���ͻ�������ʾ���ݣ����������������ַ�������ʾ����õ���ֵ
				char str1[5];
				char str2[5];
				sprintf(str1,"%.1f",c1/10.0);
				sprintf(str2,"%.1f",t1/10.0);
				OLED_ShowString(3,7,str1);
				OLED_ShowString(4,7,str2);
				Delay_1ms(2000);

	}

}
