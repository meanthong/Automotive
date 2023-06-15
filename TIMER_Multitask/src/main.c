#include "delay.h"    // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x.h"  
#include "system_stm32f10x.h"
void TIM2_INT_Init(){
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM2 initialization for overflow every 1us

	TIM_TimeBaseInitStruct.TIM_Prescaler = 3499;
	TIM_TimeBaseInitStruct.TIM_Period = 9;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// Start TIM2
	TIM_Cmd(TIM2, ENABLE);
	
	// Nested vectored interrupt settings
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void LED(){GPIOB->ODR ^= GPIO_Pin_12;}
void LED1(){GPIOC->ODR ^= GPIO_Pin_13;}
void multitask(void (*func)(), uint32_t *time, uint32_t delay){
	if((milis()-*time)>=delay){
		func();
		*time=milis();
		}
}
int main(void)
{
	TIM2_INT_Init();
	// Initialize PB12 as push-pull output for LED
		GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
 //uint32_t time = milis();
// uint32_t time1 = milis();
	uint32_t time=milis();
	uint32_t time1=milis();
	while(1)
	{	
	multitask(&LED, &time, 500);
	multitask(&LED1, &time1, 10000);
	}
}




