#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x_tim.h"
static __IO uint32_t usTicks=0;
void TIM2_INT_Init();
void Delay_us(uint32_t us);
void Delay_ms(int ms);
#endif