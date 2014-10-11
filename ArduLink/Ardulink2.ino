#include <Arduino.h>
#include <SoftwareSerial.h>

// exemplo funcional
// matrix 3x3
// Sample Time = 2
// single
// 
// Little Endian
// Header = L
// Terminator = \n

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

void ringbyteback(byte* buffer,int n, int _size, byte* _byte)
{
  for(int i=0; i<_size+n; i++)
  {
    _byte[i]=buffer[i+n];
    //Serial.println(i);
  }
}

//SoftwareSerial soSerial(10, 11); // RX, TX


void setup()
{
  //soSerial.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  //Serial.println("--------------");
  //Serial.print("->");
  //Serial.println(Serial.available());
  //Serial.print(" ");
  //Serial.println(char(Serial.peek()));
  while(Serial.peek()=='L' && Serial.available()>24)
  {
    Serial.read();
    Serial.println("Start byte !");

    int i=0;
    byte buffer[32]={0};
    for(i=0; Serial.peek()!='\n'; i++)
      buffer[i]=Serial.read();
    Serial.read();//\n
    Serial.print("S-E = "); Serial.println(i);
    float b;
    if(i!=24) break;

    b=byte2float(buffer);
    Serial.println(b);

    for(int i=0; i<8; i++)
    {
      ringbyteback(buffer,4,32,buffer);
      b=byte2float(buffer);
      Serial.println(b);
    }
  } 
  if(Serial.available()>24)
    Serial.read();
  /*
  else
  if((Serial.available()!=0 && Serial.available()<36))
  {
    Serial.println(Serial.read());
    //Serial.flush();
  }*/
  
}