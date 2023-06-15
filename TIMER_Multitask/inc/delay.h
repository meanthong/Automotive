#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h" 
uint32_t milis();
static uint32_t count=0;
void TIM2_IRQHandler();
#endif