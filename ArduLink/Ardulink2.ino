#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Timer.h>
#include <CircularBuffer.h>
 
// exemplo funcional
// matrix 3x3
// Sample Time = 2
// single
// 
// Little Endian
// Header = L
// Terminator = \n

/*
typedef union _FLOATCONV
{
    float f;
    byte b[4];
} _FLOATCONV;

float byte2float(byte* buffer)
{
  _FLOATCONV _float;
  for(int i=0; i<4; i++)
    _float.b[i]=buffer[i];
  return _float.f;
}
*/

SoftwareSerial soSerial(10, 11); // RX, TX
CircularBuffer Buffer;
Timer t;


void dataAnalize()
{
  int row=2,colun=3;
  int type=4; //int32
  while(Buffer.avaiable()!=0)
  {
    for(int i=0; i<Buffer.avaiable() && Buffer.avaiable()!=0; i++)
    {
      if(Buffer.peek(i)=='L' && Buffer.peek(i+type*row*colun+1)=='\n')
      { 
        while(Buffer.peek()!='L' && Buffer.avaiable()!= 0)
          Buffer.read();
        Buffer.read();

        if(1) //int
          for(int k=0; k<6; k++)
          {
            int inbyte[4];
            inbyte[0]=(int)Buffer.read();//msb
            inbyte[1]=(int)Buffer.read();//msb
            inbyte[2]=(int)Buffer.read();//msb
            inbyte[3]=(int)Buffer.read();//msb
            int temp;
            temp=(inbyte[3]<<24)+(inbyte[2]<<16)+(inbyte[1]<<8)+inbyte[0];
            soSerial.println(temp);
          }
        
        soSerial.println("AEAEAEA");
      }
    }
  }
}


void setup()
{
  soSerial.begin(115200);
  Serial.begin(9600);
  //t.every(1000, printData);
  t.every(100, dataAnalize);
  soSerial.println(">------------<");
}

void loop()
{
  t.update();
}

void serialEvent()
{
  while (Serial.available())
    Buffer.add((byte)Serial.read()); 
}