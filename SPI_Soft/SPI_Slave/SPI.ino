
#include "stdbool.h"
#define SS 10
#define MISO 11
#define SCK 13
uint8_t dat=0x00;
void setup() {
  Serial.begin(9600);  
  pinMode(SS, INPUT_PULLUP);
  pinMode(MISO,INPUT);
  pinMode(SCK, INPUT);

}
uint8_t SPI_SlaveReceive()
{
  uint8_t i = 0;  uint8_t dataReceive=0x00;bool st=0;
  while (digitalRead(SS));
  while (!digitalRead(SCK));
    for(i=0; i<8;i++)
    { if(digitalRead(SCK)){
      while (digitalRead(SCK)) st = digitalRead(MISO);
      dataReceive=dataReceive<<1;
      dataReceive=dataReceive|st;
    }
    while (!digitalRead(SCK));
    }
  return dataReceive;
}


void loop(){
  if(!(digitalRead(SS))){
    dat=SPI_SlaveReceive();
    Serial.println(dat,DEC);
  }
}