#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"  
#define btn1 DIO_CHANNEL_PA0
#define btn2 DIO_CHANNEL_PA1
#define btn3 DIO_CHANNEL_PA2
#define led1 DIO_CHANNEL_PB5
#define led2 DIO_CHANNEL_PB6
#define led3 DIO_CHANNEL_PB7
void CONFIG();
void Delay(__IO uint32_t nCount);
void readbtn();
void blink(__IO uint32_t delay, int time);
void chasing(__IO uint32_t delay, int time);
void offled();
#endif