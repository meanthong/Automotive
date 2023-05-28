#include "stm32f10x.h"    
// Device header
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
	DIO_PORTC
 }                  Dio_PortType;

typedef enum{
	STD_LOW,
	STD_HIGH
	}                 Dio_LevelType;
void CONFIG()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	}

void Dio_WriteChannel(Dio_ChannelType ChannelID, Dio_LevelType Level);
void Delay(volatile uint32_t nCount);
uint32_t i=0;
int main(void)
	{
		CONFIG();
		while(1){
			Dio_WriteChannel(DIO_CHANNEL_PC13, STD_LOW);
			Delay(0xfffff);
	    //Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);	
			Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
			Delay(0xfffff);
			i++;
			//Dio_WriteChannel(DIO_CHANNEL_PC13, STD_HIGH);
			}
	}
	
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

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
