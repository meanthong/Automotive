#include "delay.h"
uint32_t milis(){
return count;
}
void TIM2_IRQHandler()
{
		count++;
		//GPIOC->ODR ^= GPIO_Pin_13;	
		// Clears the TIM2 interrupt pending bit
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
