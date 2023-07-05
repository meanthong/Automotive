/*Spi Autosar include file
	@Author: Phan Minh Thong.
	File name: Spi.h
*/
#ifndef _SPI_HARDWARE_H
#define _SPI_HARDWARE_H

#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI

//Define RCC and GPIO for SPI: using SPI2.
#define SPIx_RCC RCC_APB1Periph_SPI2
#define SPIx SPI2
#define SPI_GPIO_RCC  RCC_APB2Periph_GPIOB
#define SPI_GPIO      GPIOB
#define SPI_PIN_MOSI  GPIO_Pin_15 //Master out Slave in Pin.
#define SPI_PIN_MISO  GPIO_Pin_14 //Master in Slave out Pin.
#define SPI_PIN_SCK   GPIO_Pin_13 //Clock Pin.
#define SPI_PIN_SS    GPIO_Pin_12 //Slave select Pin.

//Autosar SPI return type.
typedef enum {
	
  E_OK,
  E_NOT_OK
	
} Std_ReturnType;

#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1
#define Spi_DataBufferType uint8_t 
//Autosar SPI ChannelType.
typedef enum {
	
    SPI_CHANNEL_1,
    SPI_CHANNEL_2,
    SPI_CHANNEL_3,
    SPI_CHANNEL_INVALID
	
} Spi_ChannelType;

//Spi_ConfigType
typedef SPI_InitTypeDef Spi_ConfigType;

//Struct for Init Spi.
GPIO_InitTypeDef GPIO_InitStruct;

//Struct of data.



//Functions.
void Spi_Init (Spi_ConfigType* ConfigPtr);

Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPtr);

Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel, Spi_DataBufferType* DataBufferPointer);

Std_ReturnType Spi_DeInit ();

#endif