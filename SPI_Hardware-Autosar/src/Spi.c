/*Spi Autosar source file
	@Author: Phan Minh Thong.
	File name: Spi.c
*/
#include "Spi.h"                  // Include header files.
#include "string.h"				  // 

/*
* Function name: Spi_Init
* Description: Service for SPI initialization.
* Input:
*   ConfigPtr: Pointer to configuration structure
* Output:
*   None
*/
void Spi_Init (Spi_ConfigType* ConfigPtr){
	RCC_APB1PeriphClockCmd(SPIx_RCC, ENABLE);
	ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //Clock/64: 72M/64.
	ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge;
	ConfigPtr->SPI_CPOL = SPI_CPOL_Low;
	ConfigPtr->SPI_DataSize = SPI_DataSize_8b;
	ConfigPtr->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB;
	ConfigPtr->SPI_Mode = SPI_Mode_Master;
	ConfigPtr->SPI_NSS = SPI_NSS_Soft|SPI_NSSInternalSoft_Set;
	SPI_Init(SPIx, ConfigPtr);
	SPI_Cmd(SPIx, ENABLE);
	
}
/*
* Function name: Spi_WriteIB
* Description: Service for writing one or more data to an IB SPI Handler/Driver Channel specified by parameter.
* Input: 
	Channel: Channel ID of the SPI.
	DataBufferPtr : Pointer to the data buffer. If this pointer is null, it is assumed that
					the data to be transmitted is not relevant and the default transmit
					value of this channel will be used instead. 
* Output:
	E_OK: write command has been accepted
	E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr){
	switch(Channel){
	case SPI_CHANNEL_1:
			RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_2:
			RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_3:
		RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_INVALID: 
		return E_NOT_OK;
	}
	
	if(!DataBufferPtr) return E_NOT_OK;
	
	GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 0);
	while(DataBufferPtr){
		while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE));
		SPI_I2S_SendData(SPIx, *(DataBufferPtr++));		
	}
	GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
}
/*
* Function name: Spi_ReadIB
* Description: Service for reading one or more data to an IB SPI Handler/Driver Channel specified by parameter.
* Input: 
	Channel: Channel ID of the SPI.
	DataBufferPtr : Pointer to destination data buffer in RAM
* Output:
	E_OK: write command has been accepted
	E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer){
	switch(Channel){
	case SPI_CHANNEL_1:
			RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_2:
			RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_3:
		RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		//GPIO_WriteBit(SPI_GPIO, SPI_PIN_SS, 1);
	
	case SPI_CHANNEL_INVALID: 
		return E_NOT_OK;
	}
	if(!DataBufferPointer) return E_NOT_OK;
	while(DataBufferPointer){
		while(!SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE));
		*DataBufferPointer = SPI_I2S_ReceiveData(SPIx);
		DataBufferPointer++;
	}
}
/*
* Function name: Spi_DeInit
* Description: Service for SPI de-initialization.
* Input:
	None
* Output:
	E_OK: de-initialisation command has been accepted
	E_NOT_OK: de-initialisation command has not been accepted
*/
Std_ReturnType Spi_DeInit (){
	if(SPIx==SPI1){
		/* Enable SPI1 reset state */
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
		/* Release SPI1 from reset state */
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
		return E_OK;
		}
	if(SPIx==SPI2){
		/* Enable SPI2 reset state */
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
		/* Release SPI2 from reset state */
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
		return E_OK;
		}
	if(SPIx==SPI3){
		/* Enable SPI3 reset state */
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
		/* Release SPI3 from reset state */
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
		return E_OK;
		}
	else return E_NOT_OK;
	}

int main(){}