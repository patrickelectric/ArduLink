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
    //soSerial.println(i);
  }
}

SoftwareSerial soSerial(10, 11); // RX, TX


void setup()
{
  soSerial.begin(115200);
  Serial.begin(9600);
  soSerial.println(">------------<");
}

void loop()
{
  while(Serial.peek()=='L' || Serial.available()!=0)
  {
    if(Serial.peek() == '\n')
      soSerial.print("END");
    soSerial.println("--------------");
    soSerial.print((char)(Serial.peek()));
    soSerial.print(" - ");
    soSerial.println((Serial.read()),HEX);
  } 
}