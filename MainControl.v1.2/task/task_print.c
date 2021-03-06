#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "cmsis_os.h"
uint8_t Test_Cmd[] = {0x1b,0x40,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x1b,0x4a,0x30}; 

uint8_t title[] =                                                                 
             {  
              0x1B,0x40,                                            
              0x1b,0x33,0x30,//设置行宽
						  0x1b,0x42,0x07,//左边字符 
    					0x1c,0x26,//选择中文打印模式
 				      0x1d,0x21,0x10,//字符宽度设定
              0xBC,0xEC,//0x20,0x20,0x20,
							0xB2,0xE2,//0x20,0x20,0x20,
							0xBD,0xE1,//0x20,0x20,0x20,
							0xB9,0xFB, 
							0x0d,0x0a,0x0d,0x0a
              };
 uint8_t Test_data1[] =                                                                       
             {  
              0x1B,0x40,//初始化命令
							0x1B,0x33,0x30,//设置行间距
							0x1c,0x26,//设置中文模式//0x1B,0x42,0x10,
							0xB9,0xFD,0xD1,0xF5,0xBB,0xAF,0xC7,0xE2,0x3A, 0x20,0x20,0x20,0x0d,0x0a
              };
uint8_t Test_data2[] =                                                                       
             {  
              //0x1B,0x40,//初始化命令
							//0x1B,0x33,0x30,
							//0x1c,0x26,//0x1B,0x42,0x10,
							0xB0,0xD7,0xCF,0xB8,0xB0,0xFB,0xF5,0xA5,0xC3,0xB8,0x3A, 0x20,0x20,0x20,0x0d,0x0a,
						 };
uint8_t Test_data3[] =                                                                       
             {  
             // 0x1B,0x40,//初始化命令
							//0x1B,0x33,0x30,
							//0x1c,0x26,//0x1B,0x42,0x10,
							0xCD,0xD9,0xD2,0xBA,0xCB,0xE1,0xDC,0xD5,0xC3,0xB8,0x3A, 0x20,0x20,0x20,0x0d,0x0a
						 };
uint8_t Test_data4[] =                                                                      
             {  
              0x1B,0x40,//初始化命令
							//0x1B,0x33,0x30,
							0x1c,0x26,//0x1B,0x42,0x10,
							0xB8,0xAC,0xB0,0xB1,0xCB,0xE1,0xB0,0xB1,0x0d,0x0a,
							0xBB,0xF9,0xEB,0xC4,0xC3,0xB8,0x3A, 0x20,0x20,0x20,0x0d,0x0a
						 };
uint8_t Test_data5[] =                                                                       
             {  
              0x1B,0x40,//初始化命令
							//0x1B,0x33,0x30,
							0x1c,0x26,//0x1B,0x42,0x10,
							0xD2,0xD2,0xF5,0xA3,0xB0,0xB1,0xBB,0xF9,0xC6,0xCF,0x0d,0x0a,
							0xCC,0xD1,0xCC,0xC7,0xDC,0xD5,0xC3,0xB8,0x3A,
							0x20,0x20,0x20,0x0d,0x0a,
							//0x1c,0x26,0x0d,0x0a,
							//0x1C,0x26,0xA3,0xBA,
							//0x1C,0x2E,
							//0X20,0X20,0x36,0x2E,0x39,0x25,//换行
						 };
uint8_t Test_data6[] =                                                                        
             {  
              0x1B,0x40,//初始化命令
							0x1B,0x33,0x30,0x1c,0x26,//0x1B,0x42,0x10,
							0xB0,0xD7,0xCF,0xB8,0xB0,0xFB,0xF5,0xA5,0xC3,0xB8,0x3A, 0x20,0x20,0x20,0x0d,0x0a,
						 };
uint8_t Test_data7[] =                                                                     
             {  
              0x1B,0x40,//初始化命令
							0x1B,0x33,0x30,0x1c,0x26,//0x1B,0x42,0x10,
							0x50,0x48,0x3A, 0x20,0x20,0x20,0x0d,0x0a,
						 };
uint8_t Test_result1[] = 
						 {0x1B,0x40,
						  0x1b,0x61,0x02,
						  0xD5,0xFD,0xB3,0xA3,0x0d,0x0a    //正常
						 };
uint8_t Test_result2[] = 
						 {0x1B,0x40,
						  0x1b,0x61,0x02,
						  0xB2,0xBB,0xD5,0xFD,0xB3,0xA3,0x0d,0x0a //不正常
						 };

						 

uint8_t one_must[] = {0x1b,0x40};                                                // 开始命令
uint8_t num_O[] = {0X30,0X31,0X32,0X33,0X34,0X35,0X36,0X37,0X38,0X39};           //十进制 0-9
uint8_t hang_dist[] = {0x1b,0x33,0x30};                                          //行间距 30*0.125mm = 3.75mm     
uint8_t hang_none[] = {0x1b,0x32};                                               //缺省行间距 固定为 3.75mm
//对齐方式
uint8_t duiqi_left[] = {0x1b,0x61,0x00};
uint8_t duiqi_mid[] =  {0x1b,0x61,0x01};
uint8_t duiqi_right[] = {0x1b,0x61,0x02};
uint8_t B0[40]={//***20
               0x1B,0x40,0x1b,0x57,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  //0x01,0x1b,0x56,0x1c,0x49,0x00,
             0x1B,0x40,0x1b,0x57,0x01,0x1b,0x56,0x02,0x1c,0x49,0x02,
              0x1B,0x40,
             // 0x1b,0x57,0x02,
               };
extern uint8_t flag_print;
// 输出一个十六进制数 
void U1_SendH(uint8_t data)
{
  uint8_t OutData;
	OutData = data&0xff;
	HAL_UART_Transmit(&huart1,&OutData,1,0xff);
}  

//输出一个数组
void U1_SendStr(uint8_t *str,uint8_t delay)
{
 for(uint16_t i=0;i < (sizeof(str)/sizeof(str[0]));i++)
	{
			osDelay(delay);    // delay
		  U1_SendH(str[i]);      // 需要打印的数组，包括指令和内容
	}
}


void Print_result(void)
{
		uint8_t delay = 5;
		for(uint8_t m = 0;m < (sizeof(title)/sizeof(title[0]));m++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(title[m]);      // 需要打印的数组，包括指令和内容
				 }
		for(uint8_t i = 0;i < (sizeof(Test_data1)/sizeof(Test_data1[0]));i++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data1[i]);      // 需要打印的数组，包括指令和内容
				}
				 
		for(uint8_t j = 0;j < (sizeof(Test_data2)/sizeof(Test_data2[0]));j++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data2[j]);      // 需要打印的数组，包括指令和内容
				 }
				 
		for(uint8_t k = 0;k < (sizeof(Test_data3)/sizeof(Test_data3[0]));k++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data3[k]);      // 需要打印的数组，包括指令和内容
				 }
				 
		for(uint8_t l = 0;l < (sizeof(Test_data4)/sizeof(Test_data4[0]));l++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data4[l]);      // 需要打印的数组，包括指令和内容
				 }
		for(uint8_t n = 0;n < (sizeof(Test_data5)/sizeof(Test_data5[0]));n++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data5[n]);      // 需要打印的数组，包括指令和内容
				 }
		for(uint8_t l = 0;l < (sizeof(Test_data6)/sizeof(Test_data6[0]));l++)
				 {	
					 HAL_Delay(delay);
					 U1_SendH(Test_data6[l]);      // 需要打印的数组，包括指令和内容
				 }
}