/*This file is for SPI_Master device.*/
/*	@Author: Phan Minh Thong*/

#include "stm32f10x.h"			//include file
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "delay.h"
#include "string.h"

#define SPIx_RCC      RCC_APB1Periph_SPI2	//define SPI RCC and Pins
#define SPIx          SPI2
#define SPI_GPIO_RCC  RCC_APB2Periph_GPIOB
#define SPI_GPIO      GPIOB
#define SPI_PIN_MOSI  GPIO_Pin_15
#define SPI_PIN_MISO  GPIO_Pin_14
#define SPI_PIN_SCK   GPIO_Pin_13
#define SPI_PIN_SS    GPIO_Pin_12

uint8_t receivedByte; 				//Data received from Slave.
uint8_t buffTx[]= "My world";		//Data to be sent to Slave. 

void NVIC_Configuration(void);
void SPIx_Init(void);
void SPIx_EnableSlave(void);
void SPIx_DisableSlave(void);
void SPI2_IRQHandler(void)
{
	while(SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) != RESET);//Wait for transmit
	while (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) != RESET);//Wait for receive 
}

//MAIN.
int main(void)
{
    DelayInit();
	NVIC_Configuration();
	SPIx_Init();
    while (1)
    {
	// Enable slave
	SPIx_EnableSlave();	
	char *ptr = (char*)buffTx;
	while(*ptr)
	{
		SPI_I2S_SendData(SPIx,*(ptr++)); 			
		DelayMs(10);
	}
	//Disable slave
	SPIx_DisableSlave();
	DelayMs(5000);
    }
}

void NVIC_Configuration()
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 1 bit for pre-emption priority, 3 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  /* Configure and enable SPI_MASTER interrupt -------------------------------*/
  NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

void SPIx_Init()
{
    // Initialization struct
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // Initialize SPI
    RCC_APB1PeriphClockCmd(SPIx_RCC, ENABLE);
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPIx, &SPI_InitStruct); 
    SPI_Cmd(SPIx, ENABLE);
    
	//Initialize GPIO
    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
    // GPIO pins: MOSI, MISO, and SCK
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
    // GPIO pin: SS
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

    // Disable SPI slave
    SPIx_DisableSlave();
}


void SPIx_EnableSlave()
{
    //Set slave SS pin low
    SPI_GPIO->BRR = SPI_PIN_SS;
}

void SPIx_DisableSlave()
{
    //Set slave SS pin high
    SPI_GPIO->BSRR = SPI_PIN_SS;
}


