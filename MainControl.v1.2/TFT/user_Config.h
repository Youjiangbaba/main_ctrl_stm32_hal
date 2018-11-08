#include "main.h"
#include "gpio.h"
#include "can.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"
/*8��LED�ӿڶ���*/
//#define RCC_GPIO_LED8                   RCC_APB2Periph_GPIOC    //LEDʹ�õ�GPIOʱ��
//#define LEDn                            8                       //LED����Ϊ8
//#define GPIO_LED8                       GPIOC                   //LEDʹ�õ�GPIOΪPC

//#define DS1_PIN                         GPIO_Pin_0             	//DS1ʹ�õ�GPIO�ܽ�
//#define DS2_PIN                         GPIO_Pin_1							//DS2ʹ�õ�GPIO�ܽ�
//#define DS3_PIN                         GPIO_Pin_2  						//DS3ʹ�õ�GPIO�ܽ�
//#define DS4_PIN                         GPIO_Pin_3							//DS4ʹ�õ�GPIO�ܽ�
//#define DS5_PIN                         GPIO_Pin_4             	//DS5ʹ�õ�GPIO�ܽ�
//#define DS6_PIN                         GPIO_Pin_5							//DS6ʹ�õ�GPIO�ܽ�
//#define DS7_PIN                         GPIO_Pin_6  						//DS7ʹ�õ�GPIO�ܽ�
//#define DS8_PIN                         GPIO_Pin_7							//DS8ʹ�õ�GPIO�ܽ�

/*2.8��TFT��������ʾ�ӿڶ���*/
#define GPIO_TFT_DATA                   GPIOC    				         //���ݿ�PC0~PC7
#define RCC_GPIO_TFT                    RCC_APB2Periph_GPIOC 

#define GPIO_CTRA                   		GPIOA    				         //���ƿ�
//#define RCC_GPIO_CTRA    		            RCC_APB2Periph_GPIOA
#define GPIO_CTRB			              		GPIOB    				         //���ƿ�
//#define RCC_GPIO_CTRB    								RCC_APB2Periph_GPIOB

#define RS_CLR	        HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_0,GPIO_PIN_RESET)     //RS�õ�
#define RS_SET	        HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_0,GPIO_PIN_SET)       //RS�ø�

#define RW_CLR	         HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_1,GPIO_PIN_RESET)     //RW�õ�
#define RW_SET	         HAL_GPIO_WritePin(GPIO_CTRA, GPIO_PIN_1,GPIO_PIN_SET)  		  //RW�ø�

#define RD_CLR	         HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_8,GPIO_PIN_RESET)     //E�õ�
#define RD_SET	         HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_8,GPIO_PIN_SET)       //E�ø�

#define CS_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_0,GPIO_PIN_RESET)     //CS�õ�
#define CS_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_0,GPIO_PIN_SET)       //CS�ø�

#define RST_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_1,GPIO_PIN_RESET)     //RST�õ�
#define RST_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_1,GPIO_PIN_SET)       //RST�ø�

#define LE_CLR	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_2,GPIO_PIN_RESET)     //LE�õ�
#define LE_SET	        HAL_GPIO_WritePin(GPIO_CTRB, GPIO_PIN_2,GPIO_PIN_SET)       //LE�ø�

#define DataPort        GPIOC                     								//PC��Ϊ���ݿ�

#define D0              GPIO_PIN_0             										//D0ʹ�õ�GPIO�ܽ�
#define D1              GPIO_PIN_1																//D1ʹ�õ�GPIO�ܽ�
#define D2              GPIO_PIN_2  															//D2ʹ�õ�GPIO�ܽ�
#define D3							GPIO_PIN_3																//D3ʹ�õ�GPIO�ܽ�
#define D4					    GPIO_PIN_4             										//D4ʹ�õ�GPIO�ܽ�
#define D5				      GPIO_PIN_5																//D5ʹ�õ�GPIO�ܽ�
#define D6				     	GPIO_PIN_6  															//D6ʹ�õ�GPIO�ܽ�
#define D7				     	GPIO_PIN_7																//D7ʹ�õ�GPIO�ܽ�

//������TFT�������������Ӳ������

#define GPIO_TOUCHA                   		GPIOA    				         //���ƿ�
#define RCC_GPIO_TOUCHA    		            RCC_APB2Periph_GPIOA
#define GPIO_TOUCHC			              		GPIOC    				         //���ƿ�
#define RCC_GPIO_TOUCHC    								RCC_APB2Periph_GPIOC

#define PEN_CLR	        HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_12,GPIO_PIN_RESET)   //PEN�õ�,����������ʱ��ADS7843Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
#define PEN_SET	        HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_12,GPIO_PIN_SET)     //PEN�ø�
#define PEN             HAL_GPIO_ReadPin(GPIO_TOUCHC,GPIO_PIN_12)    //PC12�����ֵ

#define TPDO_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_11,GPIO_PIN_RESET)   //TPDO�õ�
#define TPDO_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_11,GPIO_PIN_SET)     //TPDO�ø�
#define TPDOUT          HAL_GPIO_ReadPin(GPIO_TOUCHC,GPIO_PIN_11)   //PC11�����ֵ

#define BUSY_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_10,GPIO_PIN_RESET)   //BUSY�õ�
#define BUSY_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_10,GPIO_PIN_SET)     //BUSY�ø�

#define TPDI_CLR				HAL_GPIO_WritePin(GPIO_TOUCHA, GPIO_PIN_8,GPIO_PIN_RESET)    //TPDI�õ�
#define TPDI_SET				HAL_GPIO_WritePin(GPIO_TOUCHA, GPIO_PIN_8,GPIO_PIN_SET)      //TPDI�ø�

#define TPCS_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_9,GPIO_PIN_RESET)     //TPCS�õ�
#define TPCS_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_9,GPIO_PIN_SET)       //TPCS�ø�

#define TPCLK_CLR				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_8,GPIO_PIN_RESET)     //TPCLK�õ�
#define TPCLK_SET				HAL_GPIO_WritePin(GPIO_TOUCHC, GPIO_PIN_8,GPIO_PIN_SET)       //TPCLK�ø�

#define TCLK            GPIO_PIN_8             										 //TCLKʹ�õ�GPIO�ܽ�
#define TCS             GPIO_PIN_9																 //TCSʹ�õ�GPIO�ܽ�
#define BUSY            GPIO_PIN_10  															 //BUSYʹ�õ�GPIO�ܽ�



/*ȫ�ֱ���-��ɫ����*/

#define White          0xFFFF           													//��ʾ��ɫ����
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

//��Һʹ��
#define FlipMotor_en    HAL_GPIO_WritePin(Flip_EN_GPIO_Port,Flip_EN_GPIO_PIN,GPIO_PIN_RESET)  
#define FlipMotor_noen  HAL_GPIO_WritePin(Flip_EN_GPIO_Port,Flip_EN_GPIO_PIN,GPIO_PIN_SET)
/*����������*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);
void LED_Runing(u8 LED_NUM);


