#include "main.h"
#include "gpio.h"
#include "can.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"
/*8个LED接口定义*/
//#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LED使用的GPIO时钟
//#define LEDn                            8                       //LED数量为8
//#define GPIO_LED8                       GPIOC                   //LED使用的GPIO为PC

//#define DS1_PIN                         GPIO_Pin_0             	//DS1使用的GPIO管脚
//#define DS2_PIN                         GPIO_Pin_1							//DS2使用的GPIO管脚
//#define DS3_PIN                         GPIO_Pin_2  						//DS3使用的GPIO管脚
//#define DS4_PIN                         GPIO_Pin_3							//DS4使用的GPIO管脚
//#define DS5_PIN                         GPIO_Pin_4             	//DS5使用的GPIO管脚
//#define DS6_PIN                         GPIO_Pin_5							//DS6使用的GPIO管脚
//#define DS7_PIN                         GPIO_Pin_6  						//DS7使用的GPIO管脚
//#define DS8_PIN                         GPIO_Pin_7							//DS8使用的GPIO管脚

/*2.8寸TFT触摸屏显示接口定义*/
#define GPIO_TFT_DATA                   GPIOC    				         //数据口PC0~PC7
#define RCC_GPIO_TFT                    RCC_APB2Periph_GPIOC 

#define GPIO_CTRA                   		GPIOA    				         //控制口
//#define RCC_GPIO_CTRA    		            RCC_APB2Periph_GPIOA
#define GPIO_CTRB			              		GPIOB    				         //控制口
//#define RCC_GPIO_CTRB    								RCC_APB2Periph_GPIOB

#define RS_CLR	        HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_0,GPIO_PIN_RESET)     //RS置低
#define RS_SET	        HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_0,GPIO_PIN_SET)       //RS置高

#define RW_CLR	         HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_1,GPIO_PIN_RESET)     //RW置低
#define RW_SET	         HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_1,GPIO_PIN_SET)  		  //RW置高

#define RD_CLR	         HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_8,GPIO_PIN_RESET)     //E置低
#define RD_SET	         HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_8,GPIO_PIN_SET)       //E置高

#define CS_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_0,GPIO_PIN_RESET)     //CS置低
#define CS_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_0,GPIO_PIN_SET)       //CS置高

#define RST_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_1,GPIO_PIN_RESET)     //RST置低
#define RST_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_1,GPIO_PIN_SET)       //RST置高

#define LE_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_2,GPIO_PIN_RESET)     //LE置低
#define LE_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_2,GPIO_PIN_SET)       //LE置高

#define DataPort        GPIOC                     								//PC口为数据口

#define D0              GPIO_PIN_0             										//D0使用的GPIO管脚
#define D1              GPIO_PIN_1																//D1使用的GPIO管脚
#define D2              GPIO_PIN_2  															//D2使用的GPIO管脚
#define D3							GPIO_PIN_3																//D3使用的GPIO管脚
#define D4					    GPIO_PIN_4             										//D4使用的GPIO管脚
#define D5				      GPIO_PIN_5																//D5使用的GPIO管脚
#define D6				     	GPIO_PIN_6  															//D6使用的GPIO管脚
#define D7				     	GPIO_PIN_7																//D7使用的GPIO管脚

//以下是TFT触摸屏控制相关硬件配置

#define GPIO_TOUCHA                   		GPIOA    				         //控制口
#define RCC_GPIO_TOUCHA    		            RCC_APB2Periph_GPIOA
#define GPIO_TOUCHC			              		GPIOC    				         //控制口
#define RCC_GPIO_TOUCHC    								RCC_APB2Periph_GPIOC

#define PEN_CLR	        HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_12,GPIO_PIN_RESET)   //PEN置低,触碰触摸屏时，ADS7843Penirq引脚由未触摸时的高电平变为低电平
#define PEN_SET	        HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_12,GPIO_PIN_SET)     //PEN置高
#define PEN             HAL_GPIO_ReadPin(GPIO_TOUCHC,GPIO_PIN_12)    //PC12输入的值

#define TPDO_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_11,GPIO_PIN_RESET)   //TPDO置低
#define TPDO_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_11,GPIO_PIN_SET)     //TPDO置高
#define TPDOUT          HAL_GPIO_ReadPin(GPIO_TOUCHC,GPIO_PIN_11)   //PC11输入的值

#define BUSY_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_10,GPIO_PIN_RESET)   //BUSY置低
#define BUSY_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_10,GPIO_PIN_SET)     //BUSY置高

#define TPDI_CLR				HAL_GPIO_WritePin(GPIO_TOUCHA, GPIO_PIN_8,GPIO_PIN_RESET)    //TPDI置低
#define TPDI_SET				HAL_GPIO_WritePin(GPIO_TOUCHA, GPIO_PIN_8,GPIO_PIN_SET)      //TPDI置高

#define TPCS_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_9,GPIO_PIN_RESET)     //TPCS置低
#define TPCS_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_9,GPIO_PIN_SET)       //TPCS置高

#define TPCLK_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_8,GPIO_PIN_RESET)     //TPCLK置低
#define TPCLK_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_8,GPIO_PIN_SET)       //TPCLK置高

#define TCLK            GPIO_PIN_8             										 //TCLK使用的GPIO管脚
#define TCS             GPIO_PIN_9																 //TCS使用的GPIO管脚
#define BUSY            GPIO_PIN_10  															 //BUSY使用的GPIO管脚



/*全局变量-颜色代码*/

#define White          0xFFFF           													//显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define vu32  uint32_t
#define u8 uint8_t
#define u16 uint16_t

//滴液使能
#define FlipMotor_en    HAL_GPIO_WritePin(Flip_EN_GPIO_Port,Flip_EN_GPIO_PIN,GPIO_PIN_RESET)  
#define FlipMotor_noen  HAL_GPIO_WritePin(Flip_EN_GPIO_Port,Flip_EN_GPIO_PIN,GPIO_PIN_SET)
/*函数声明区*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void LED_Runing(u8 LED_NUM);


