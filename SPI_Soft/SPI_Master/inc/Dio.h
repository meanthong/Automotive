#ifndef __DIO_H
#define __DIO_H

#include "stm32f10x.h"                  // Device header

typedef enum {
	DIO_CHANNEL_PA0,
	DIO_CHANNEL_PA1,
	DIO_CHANNEL_PA2,
	DIO_CHANNEL_PA3,
	DIO_CHANNEL_PA4,
	DIO_CHANNEL_PA5,
	DIO_CHANNEL_PA6,
	DIO_CHANNEL_PA7,
	DIO_CHANNEL_PA8,
	DIO_CHANNEL_PA9,
	DIO_CHANNEL_PA10,
	DIO_CHANNEL_PA11,
	DIO_CHANNEL_PA12,
	DIO_CHANNEL_PA13,
	DIO_CHANNEL_PA14,
	DIO_CHANNEL_PA15,
	DIO_CHANNEL_PB0,
	DIO_CHANNEL_PB1,
	DIO_CHANNEL_PB2,
	DIO_CHANNEL_PB3,
	DIO_CHANNEL_PB4,
	DIO_CHANNEL_PB5,
	DIO_CHANNEL_PB6,
	DIO_CHANNEL_PB7,
	DIO_CHANNEL_PB8,
	DIO_CHANNEL_PB9,
	DIO_CHANNEL_PB10,
	DIO_CHANNEL_PB11,
	DIO_CHANNEL_PB12,
	DIO_CHANNEL_PB13,
	DIO_CHANNEL_PB14,
	DIO_CHANNEL_PB15,
	DIO_CHANNEL_PC0,
	DIO_CHANNEL_PC1,
	DIO_CHANNEL_PC2,
	DIO_CHANNEL_PC3,
	DIO_CHANNEL_PC4,
	DIO_CHANNEL_PC5,
	DIO_CHANNEL_PC6,
	DIO_CHANNEL_PC7,
	DIO_CHANNEL_PC8,
	DIO_CHANNEL_PC9,
	DIO_CHANNEL_PC10,
	DIO_CHANNEL_PC11,
	DIO_CHANNEL_PC12,
	DIO_CHANNEL_PC13,
	DIO_CHANNEL_PC14,
	DIO_CHANNEL_PC15
}                   Dio_ChannelType;
	
typedef enum{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
	DIO_PORTE,
	DIO_PORTF
 }                  Dio_PortType;

typedef enum{
	STD_LOW,
	STD_HIGH
	}                 Dio_LevelType;

#define CHANNEL(Channel_Port, Channel_Pin) \
	case DIO_CHANNEL_P##Channel_Port##Channel_Pin: \
gpioPORT = GPIO##Channel_Port;; \
gpioPIN = GPIO_Pin_##Channel_Pin; \
break;
	
Dio_LevelType setLevel(uint16_t val, uint16_t PIN);
void Dio_Config();

void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level);
	
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID);
	
Dio_LevelType setLevel(uint16_t value,uint16_t PIN);
	#endif
	