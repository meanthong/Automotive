#include "stm32f10x.h"    
#include "Dio.h"
#include "main.h"
// Device header
#include "setjmp.h"
static uint8_t bits=0;
jmp_buf buf;
void CONFIG()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	}
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void delay_ms(__IO uint32_t t)
{
		__IO uint32_t i;
		for(i=0; i<t; i++){
			Delay(100);
		}
		if(Dio_ReadChannel(btn1) == 0)
			{
				while(Dio_ReadChannel(btn1) == 0){}
				blink(10000, 5);

			}
		if(Dio_ReadChannel(btn2) == 0)
			{
				while(Dio_ReadChannel(btn2) == 0){}
				chasing(10000,5);

			}
		if(Dio_ReadChannel(btn3) == 0)
			{
				while(Dio_ReadChannel(btn3) == 0){}
				offled();
			}
	}
void readbtn()
	{
		int temp=setjmp(buf);
		if(Dio_ReadChannel(btn1) == 0)
			{
				while(Dio_ReadChannel(btn1) == 0){}
				blink(10000, 5);
			
			}
		 if(Dio_ReadChannel(btn2) == 0)
			{
				while(Dio_ReadChannel(btn2) == 0){}
				chasing(10000,5);

			}
		 if(Dio_ReadChannel(btn3) == 0)
			{
				while(Dio_ReadChannel(btn3) == 0){}
				offled();
			}

	}
	
void blink(__IO uint32_t delay, int time){
for(int i=0;i<time;i++)
	{
		Dio_WriteChannel(led1, STD_LOW);
		Dio_WriteChannel(led2, STD_LOW);
		Dio_WriteChannel(led3, STD_LOW);
		delay_ms(delay);
		
		Dio_WriteChannel(led1, STD_HIGH);
		Dio_WriteChannel(led2, STD_HIGH);
		Dio_WriteChannel(led3, STD_HIGH);
		delay_ms(delay);
	}

	longjmp(buf, 2);
}

void chasing(__IO uint32_t delay, int time){
	Dio_ChannelType arr[] = {led1, led2, led3};
	for(int i=0; i<time; i++){
	for(int j=0; j<3; j++)
		{
			Dio_WriteChannel(arr[j], STD_LOW);
			delay_ms(delay);
		}
	for(int j=0; j<3; j++)
		{
			Dio_WriteChannel(arr[j], STD_HIGH);
			delay_ms(delay);
		}
	}

	longjmp(buf,2);
}

void offled(){
Dio_WriteChannel(led1, STD_LOW);
Dio_WriteChannel(led2, STD_LOW);
Dio_WriteChannel(led3, STD_LOW);
delay_ms(10);
	longjmp(buf,2);
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
	
	
