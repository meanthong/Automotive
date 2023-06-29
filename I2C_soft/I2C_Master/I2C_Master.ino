/*
  File: I2C_Master.ino
  Author: Phan Minh Thong
*/

//Bus I2C
#define SDA 3
#define SCL 4
//Bit ACK/NACK
#define ACK 1
#define NACK 0
//Bit Write/Read
#define WRITE 0
#define READ 1

char dataSend[6] = "SendTo";//Data gửi tới Slave
uint8_t data1Byte = 0x00;//Data kích thước 1 Byte
char dataReceive[5];//Data nhận được từ Slave
uint8_t indexData = 0;//Vị trí kí tự trong Data

/*
  Function: frameAddress
*/
uint8_t frameAddress(uint8_t addressSlave, uint8_t mode)
{
  return ((addressSlave << 1) | mode);
}

/*
  Function: i2cInit
*/
void I2C_Init()
{
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);

  digitalWrite(SDA, HIGH);
  digitalWrite(SCL, HIGH);
}

/*
  Function: startI2C
*/
void startI2C()
{
  delayMicroseconds(10);
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
}

/*
  Function: stopI2C
*/
void stopI2C()
{
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(10);
  digitalWrite(SDA, HIGH);
}

/*
  Function: clockSignal
*/
void clockSignal()
{
  digitalWrite(SCL, HIGH);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
  delayMicroseconds(10);
}

/*
  Function: getAck
*/
bool getAck()
{
  pinMode(SDA, INPUT);
  delayMicroseconds(2);
  clockSignal();
  unsigned long timeT = micros();
  while (1) {
    if (!digitalRead(SDA)) {
      pinMode(SDA, OUTPUT);
      delayMicroseconds(2);
      return ACK;
    }
    if (micros() - timeT > 50) {
      pinMode(SDA, OUTPUT);
      delayMicroseconds(2);
      return NACK;
    }
  }
}

/*
  Function: sendByteData
*/
bool sendByteData(uint8_t mData)
{
  for (int i = 0; i < 8; i++) {
    digitalWrite(SDA, (mData & 0x80) != 0);
    mData = mData << 1;
    delayMicroseconds(5);
    clockSignal();
    delayMicroseconds(10);
  }
  delayMicroseconds(50);
  return getAck();
}

/*
  Function: readData
*/
bool readData()
{
  pinMode(SDA, INPUT);
  delayMicroseconds(1);
  for (int j = 0; j < 8; j++)
  {
    clockSignal();
    delayMicroseconds(5);
    data1Byte = data1Byte << 1;
    data1Byte = data1Byte | digitalRead(SDA);
    delayMicroseconds(10);
  }
  dataReceive[indexData] = data1Byte;
  indexData++;
  data1Byte = 0x00;
  delayMicroseconds(50);
  return getAck();
}

/*
  Function: beginTrans
*/
bool beginTrans(uint8_t addressSlave)
{
  startI2C();
  delayMicroseconds(50);
  return sendByteData(addressSlave);
}

void setup()
{
  Serial.begin(1000000);
  I2C_Init();
}

void loop()
{
  //Đọc Data từ Slave
  delay(2000);
  uint8_t addressSlave1 = frameAddress(8, READ);
  if (beginTrans(addressSlave1))
  {
    Serial.println("Connect");
    delay(500);
    for (int i = 0; i < 5; i++)
    {
      uint8_t x = readData();
      delayMicroseconds(100);
    }
    indexData = 0;
    pinMode(SDA, OUTPUT);
    Serial.print("Data Receive: ");
    Serial.println(String(dataReceive));
    delayMicroseconds(50);
    stopI2C();
  }

  //Gửi Data đến Slave
  delay(2000);
  uint8_t addressSlave = frameAddress(8, WRITE);
  if (beginTrans(addressSlave))
  {
    Serial.println("Connect");
    delay(500);
    for (int i = 0; i < sizeof(dataSend); i++)
    {
      sendByteData(dataSend[i]);
      delayMicroseconds(100);
    }
    Serial.println("Send Done");
    delayMicroseconds(50);
    stopI2C();
  } 
}