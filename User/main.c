#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AHT20-21_DEMO_V1_3.h"
#include <stdio.h>


int main(void)
{
	
		Init_I2C_Sensor_Port();//初始化SDA，SCL的IO口的函数
		uint32_t CT_data[2];
		volatile int  c1,t1;
		Delay_1ms(500);
		OLED_Init();//初始化OLED
		if((AHT20_Read_Status()&0x18)!=0x18)
		{
			AHT20_Start_Init(); //重新初始化寄存器
			Delay_1ms(10);
		}
		
		OLED_ShowCN(1,1,4);
		OLED_ShowCN(1,2,5);
		OLED_ShowCN(1,3,6);


		OLED_ShowCN(2,1,0); 		//第2行第1列调用字模库第0个字 我
		OLED_ShowCN(2,2,1); 		//第2行第2列调用字模库第1个字 是
		OLED_ShowCN(2,3,2);			//第2行第3列调用字模库第1个字 爱
		OLED_ShowCN(2,4,3);			//第2行第4列调用字模库第1个字 坤
		
		
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
				OLED_WriteCommand(0x2E); //关闭滚动
				OLED_WriteCommand(0x26); //向右滚动，27则向左
				OLED_WriteCommand(0x00); //虚拟字节
				OLED_WriteCommand(0x00); //起始页 这里为0
				OLED_WriteCommand(0x07); //滚动速度
				OLED_WriteCommand(0x03); //终止页 这里为3，也就是之后的姓名，学号
				OLED_WriteCommand(0x00); //虚拟字节
				OLED_WriteCommand(0xFF); //虚拟字节
				OLED_WriteCommand(0x2F); //开启滚动

	
				//AHT20_Read_CTdata(CT_data);       
				AHT20_Read_CTdata_crc(CT_data);   
		
				while(CT_data[0]==0x00&&CT_data[1]==0x00) 
				{
					AHT20_Read_CTdata_crc(CT_data);//crc校验后，读取AHT20的温度和湿度数据
				}
				c1 = CT_data[0]*100*10/1024/1024;  
				t1 = CT_data[1]*200*10/1024/1024-500;
				
				////下一步客户处理显示数据，我们这里用两个字符串来表示计算得到的值
				char str1[5];
				char str2[5];
				sprintf(str1,"%.1f",c1/10.0);
				sprintf(str2,"%.1f",t1/10.0);
				OLED_ShowString(3,7,str1);
				OLED_ShowString(4,7,str2);
				Delay_1ms(2000);

	}

}
