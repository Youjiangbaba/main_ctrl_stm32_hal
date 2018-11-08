#ifndef __alltasks_H
#define __alltasks_H
#include "can.h"



void display_init(void);
void my_gui(void);

void temp_control(void);
void temp_init(void);

void flip_init(void);
void start_flip(void);

void CAN_SEND_MESSAGE(CAN_HandleTypeDef* _hcan,uint8_t id,uint8_t symbol,uint8_t _RPX,uint8_t _RPY,uint8_t _RPTHETA);

void Print_result(void);
#endif