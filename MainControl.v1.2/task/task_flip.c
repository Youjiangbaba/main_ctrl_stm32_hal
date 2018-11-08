#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "cmsis_os.h"
uint16_t count_flip = 1,target_flip =80;

void delay_us(int p)
{
	for(uint16_t i = (72*p);i>0;i--) ;
}
void flip_init(void)
{
		//PD2 flip_motor_en 
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitStruct.Pin = Flip_EN_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Flip_EN_GPIO_Port, &GPIO_InitStruct);
  FlipMotor_noen;
}

void start_flip(void)
{		//滴液命令
		FlipMotor_en;
		for(count_flip = 0;count_flip < target_flip;count_flip ++)
		 {
			//	delay_us(120);
			  HAL_Delay(10);
				HAL_GPIO_WritePin(Flip_motor_GPIO_Port,Flip_motor_Pin,GPIO_PIN_SET);   // pa 15
				delay_us(1);
				HAL_GPIO_WritePin(Flip_motor_GPIO_Port,Flip_motor_Pin,GPIO_PIN_RESET);
				//delay_us(60);
		}
//		count_flip++;
//		if(count_flip/target_flip)  
//		{
//			 count_flip=0;
//		}
	  FlipMotor_noen;
}