#include "stm32f10x.h"                  // Device header
#include "Dio.h"
#include "stdbool.h"
#define SCK DIO_CHANNEL_PA0
#define MISO DIO_CHANNEL_PA1
#define MOSI DIO_CHANNEL_PA2
#define CS DIO_CHANNEL_PA3
#define LED DIO_CHANNEL_PC13
uint8_t DataTrans[] = {1,3,9,10,15,19,90};//Data to transmit to Slave.

void delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void Clock()
{
	Dio_WriteChannel(SCK, STD_HIGH);
	delay(1000);
	Dio_WriteChannel(SCK, STD_LOW);
	delay(1000);
}

void SPI_Init(){
	Dio_WriteChannel(SCK, STD_LOW);
	Dio_WriteChannel(CS, STD_HIGH);
	Dio_WriteChannel(MISO, STD_LOW);
	Dio_WriteChannel(MOSI, STD_LOW);
}

void SPI_MasterTrans(uint8_t dataTrans)
{
	//uint8_t DataRecie = 0x00;
	uint8_t tempDat = 0x00;
	bool st=0;
	uint8_t mark =0x80;
	int i=0;
	Dio_WriteChannel(CS, STD_LOW);//Set the ChiipSelect Pin.
	delay(10);
	for(i=0; i<8; i++){
		tempDat = dataTrans&mark;
		if(tempDat)
			{
				Dio_WriteChannel(MOSI, STD_HIGH);Dio_WriteChannel(LED, STD_HIGH);
				st=1;
				delay(10);
			}else
			{
				st=0;
				Dio_WriteChannel(MOSI, STD_LOW);Dio_WriteChannel(LED, STD_LOW);
				delay(10);
			}
		//DataRecie=DataRecie<<1;
		//DataRecie = (uint8_t)DataRecie|st;
		dataTrans= dataTrans<< 1;
		Clock();
	}	
	Dio_WriteChannel(CS, STD_HIGH);
	delay(10);
	//return DataRecie;
}

int main(){
	SPI_Init();
	Dio_Config();
	while(1)
		{	
			for(int i=0; i<7; i++){
			SPI_MasterTrans(DataTrans[i]);
			delay(5000000);
			}
		}
}