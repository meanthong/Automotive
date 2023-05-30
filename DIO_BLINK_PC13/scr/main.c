#include "stm32f10x.h"    
#include "Dio.h"
#include "main.h"
// Device header

void CONFIG()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	}
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/*******************Main*******************/
int main(void)
	{
		CONFIG();
		while(1){
				if(Dio_ReadChannel(DIO_CHANNEL_PA0) == STD_HIGH)
					{}
					else {
				for(int i=0; i<5; i++)
					{
						Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW );
						Delay(0xfffff);
						Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
						Delay(0xfffff);
					}
				}
				
			}
	}
	
	
