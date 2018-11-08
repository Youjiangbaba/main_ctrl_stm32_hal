#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "cmsis_os.h"
// dma nomal 
uint32_t temp = 0;
uint8_t  TEMP = 0,SHI = 0,GE = 0;
uint32_t arr_t = 0;
void temp_init(void)
{
 
}

void temp_control(void)
{
 		uint32_t ad_sum = 0;
		for(uint8_t i=0;i<10;i++) 
		{ 
 			HAL_ADC_Start_DMA(&hadc1,&temp,1);
			ad_sum += temp;
//			osDelay(5); 
		} 
		arr_t = ad_sum/10;
		TEMP = (arr_t-90)/10;
		if(TEMP > 99) TEMP = 99;
		if(TEMP < 10) TEMP = 10;
	  SHI = TEMP/10 + 0X30;
   	GE = TEMP%10 + 0x30;
		osDelay(100);
		if (arr_t < 458)
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
		if (arr_t > 461)
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}