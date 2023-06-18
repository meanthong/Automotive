#include "Dio.h"
GPIO_InitTypeDef GPIO_InitStruct;

void Dio_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);
}

void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level){
	uint16_t gpioPIN;
	GPIO_TypeDef *gpioPORT;

switch(ChannelID){
		CHANNEL(A,0)
		CHANNEL(A,1)
		CHANNEL(A,2)
		CHANNEL(A,3)
		CHANNEL(A,4)
		CHANNEL(A,5)
		CHANNEL(A,6)
		CHANNEL(A,7)
		CHANNEL(A,8)
		CHANNEL(A,9)
		CHANNEL(A,10)
		CHANNEL(A,11)
		CHANNEL(A,12)
		CHANNEL(A,13)
		CHANNEL(A,14)
		CHANNEL(A,15)
		CHANNEL(B,0)
		CHANNEL(B,1)
		CHANNEL(B,2)
		CHANNEL(B,3)
		CHANNEL(B,4)
		CHANNEL(B,5)
		CHANNEL(B,6)
		CHANNEL(B,7)
		CHANNEL(B,8)
		CHANNEL(B,9)
		CHANNEL(B,10)
		CHANNEL(B,11)
		CHANNEL(B,12)
		CHANNEL(B,13)
		CHANNEL(B,14)
		CHANNEL(B,15)
		CHANNEL(C,0)
		CHANNEL(C,1)
		CHANNEL(C,2)
		CHANNEL(C,3)
		CHANNEL(C,4)
		CHANNEL(C,5)
		CHANNEL(C,6)
		CHANNEL(C,7)
		CHANNEL(C,8)
		CHANNEL(C,9)
		CHANNEL(C,10)
		CHANNEL(C,11)
		CHANNEL(C,12)
		CHANNEL(C,13)
		CHANNEL(C,14)
		CHANNEL(C,15)
	}
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = gpioPIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(gpioPORT, &GPIO_InitStruct);
	
	if(Level==STD_LOW){
		GPIO_ResetBits(gpioPORT,gpioPIN);
	}
	else{
		GPIO_SetBits(gpioPORT,gpioPIN);
	}
	}
/*****************Dio_ReadChannel*********************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID)
	{
	GPIO_TypeDef *gpioPORT;
	uint16_t gpioPIN;
		
switch(ChannelID){
		CHANNEL(A,0)
		CHANNEL(A,1)
		CHANNEL(A,2)
		CHANNEL(A,3)
		CHANNEL(A,4)
		CHANNEL(A,5)
		CHANNEL(A,6)
		CHANNEL(A,7)
		CHANNEL(A,8)
		CHANNEL(A,9)
		CHANNEL(A,10)
		CHANNEL(A,11)
		CHANNEL(A,12)
		CHANNEL(A,13)
		CHANNEL(A,14)
		CHANNEL(A,15)
		CHANNEL(B,0)
		CHANNEL(B,1)
		CHANNEL(B,2)
		CHANNEL(B,3)
		CHANNEL(B,4)
		CHANNEL(B,5)
		CHANNEL(B,6)
		CHANNEL(B,7)
		CHANNEL(B,8)
		CHANNEL(B,9)
		CHANNEL(B,10)
		CHANNEL(B,11)
		CHANNEL(B,12)
		CHANNEL(B,13)
		CHANNEL(B,14)
		CHANNEL(B,15)
		CHANNEL(C,0)
		CHANNEL(C,1)
		CHANNEL(C,2)
		CHANNEL(C,3)
		CHANNEL(C,4)
		CHANNEL(C,5)
		CHANNEL(C,6)
		CHANNEL(C,7)
		CHANNEL(C,8)
		CHANNEL(C,9)
		CHANNEL(C,10)
		CHANNEL(C,11)
		CHANNEL(C,12)
		CHANNEL(C,13)
		CHANNEL(C,14)
		CHANNEL(C,15)
	}
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = gpioPIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(gpioPORT, &GPIO_InitStruct);
	
	if(GPIO_ReadInputDataBit(gpioPORT,gpioPIN)==Bit_SET){
		return STD_HIGH;
	}else{
		return STD_LOW;
	}
	}
	
Dio_LevelType setLevel(uint16_t val, uint16_t PIN){
	if((val & PIN) == PIN)
		return STD_HIGH;
	else
		return STD_LOW;
}
