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
uint8_t readbtn()
	{
		uint8_t bits=0b00000000;
		if(Dio_ReadChannel(btn1) == 0)
			{
				while(Dio_ReadChannel(btn1) == 0){}
				bits = 0b000000001;
				blink(1000000,5);
					offled();
				return bits;
			}
		else if(Dio_ReadChannel(btn2) == 0)
			{
				while(Dio_ReadChannel(btn2) == 0){}
				bits = 0b000000010;
				chasing(1000000,5);
					offled();
				return bits;
			}
		else if(Dio_ReadChannel(btn3) == 0)
			{
				while(Dio_ReadChannel(btn3) == 0){}
				bits = 0b000000100;
				offled();
				return bits;
			}
		bits=0b00000000; return bits;
	}
	
void blink(volatile uint32_t delay, int time){
for(int i=0;i<time;i++)
	{
		Dio_WriteChannel(led1, STD_LOW);
		Dio_WriteChannel(led2, STD_LOW);
		Dio_WriteChannel(led3, STD_LOW);
		if(readbtn()!=0x00) return;
		Delay(delay);
		
		Dio_WriteChannel(led1, STD_HIGH);
		Dio_WriteChannel(led2, STD_HIGH);
		Dio_WriteChannel(led3, STD_HIGH);
		Delay(delay);
		if(readbtn()!=0x00) return;
	}
}

void chasing(volatile uint32_t delay, int time){
	Dio_ChannelType arr[] = {led1, led2, led3};
	for(int i=0; i<time; i++){
	for(int j=0; j<3; j++)
		{
			Dio_WriteChannel(arr[j], STD_LOW);
			if(readbtn()!=0x00) return;
			Delay(delay);
		}
	for(int j=0; j<3; j++)
		{
			Dio_WriteChannel(arr[j], STD_HIGH);
			if(readbtn()!=0x00) return;
			Delay(delay);
		}
	}
}

void offled(){
Dio_WriteChannel(led1, STD_LOW);
Dio_WriteChannel(led2, STD_LOW);
Dio_WriteChannel(led3, STD_LOW);
if(readbtn()!=0x00) return;
}
/*******************Main*******************/
int main(void)
	{
		CONFIG();
		while(1)
			{
				readbtn();
			}
	}
	
	
