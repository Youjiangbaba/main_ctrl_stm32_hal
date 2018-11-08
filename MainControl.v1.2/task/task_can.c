#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "cmsis_os.h"
//#include "alltasks.h"

extern uint8_t redataMOTOR[8],redataCOLOR[8],MYID;
extern uint8_t start,ph_ok,flip_ok,EN_PUT;
extern void CAN_SEND_MESSAGE(CAN_HandleTypeDef* _hcan,uint8_t id,uint8_t symbol,uint8_t _RPX,uint8_t _RPY,uint8_t _RPTHETA);

//接收中断回调
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* _hcan)
{
 MYID = _hcan->pRxMsg->StdId;
 if(MYID == 0x22)
 {
	 for(uint8_t i = 0;i<8;i++)
     redataMOTOR[i] = _hcan->pRxMsg->Data[i];
 }
 else if(MYID == 0x58)
 {
	 	for(uint8_t j = 0;j<8;j++)
      redataCOLOR[j] = _hcan->pRxMsg->Data[j];
 }
  CAN_SEND_MESSAGE(_hcan,0x22,start,ph_ok,flip_ok,0);
  HAL_CAN_Receive_IT(_hcan,CAN_FIFO0); 
}

// CAN send
void can_senddata()
{
 
}	


void CAN_SEND_MESSAGE(CAN_HandleTypeDef* _hcan,uint8_t id,uint8_t symbol,uint8_t _RPX,uint8_t _RPY,uint8_t _RPTHETA)
{
_hcan->pTxMsg->RTR = CAN_RTR_DATA;
_hcan->pTxMsg->IDE = CAN_ID_STD;
_hcan->pTxMsg->DLC = 8;


_hcan->pTxMsg->StdId=id;
_hcan->pTxMsg->Data[0] = symbol;
_hcan->pTxMsg->Data[1] = _RPX;
_hcan->pTxMsg->Data[2] = _RPY;
_hcan->pTxMsg->Data[3] = _RPTHETA;
_hcan->pTxMsg->Data[4] = 4;
_hcan->pTxMsg->Data[5] = 5;
_hcan->pTxMsg->Data[6] = 6;
_hcan->pTxMsg->Data[7] = 7;


HAL_CAN_Transmit(_hcan,0xff);

}