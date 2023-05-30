#include "Dio.h"

void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level){
	GPIO_TypeDef *gpioPORT;
	uint16_t gpioPIN;
	GPIO_InitTypeDef PIN;
	switch(ChannelID){
		case DIO_CHANNEL_PA0:
			gpioPORT = GPIOA;
			gpioPIN = GPIO_Pin_0;
			
			PIN.GPIO_Pin = gpioPIN;
			PIN.GPIO_Mode = GPIO_Mode_Out_PP;
			PIN.GPIO_Speed = GPIO_Speed_2MHz;
			GPIO_Init(GPIOA, &PIN);
			break;
		case DIO_CHANNEL_PC13:
			gpioPORT = GPIOC;
			gpioPIN = GPIO_Pin_13;
			
			PIN.GPIO_Pin = gpioPIN;
			PIN.GPIO_Mode = GPIO_Mode_Out_PP;
			PIN.GPIO_Speed = GPIO_Speed_2MHz;
			GPIO_Init(GPIOC, &PIN);
			break;
		default:;
		}
	
	if(Level == STD_LOW) GPIO_ResetBits(gpioPORT, gpioPIN);
		else GPIO_SetBits(gpioPORT, gpioPIN);
	}
/*****************Dio_ReadChannel*********************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID)
	{
			GPIO_TypeDef *gpioPORT;
	uint16_t gpioPIN;
	GPIO_InitTypeDef PIN;
	switch(ChannelID){
		case DIO_CHANNEL_PA0:
			gpioPORT = GPIOA;
			gpioPIN = GPIO_Pin_0;
			
			PIN.GPIO_Pin = gpioPIN;
			PIN.GPIO_Mode = GPIO_Mode_IPU;
			PIN.GPIO_Speed = GPIO_Speed_2MHz;
			GPIO_Init(GPIOA, &PIN);
			break;
		
		default:;
		}
	
		if(GPIO_ReadInputDataBit(gpioPORT, gpioPIN) ==0) return STD_LOW;
		else return STD_HIGH;
	}
