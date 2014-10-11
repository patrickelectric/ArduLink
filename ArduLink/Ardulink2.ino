#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Timer.h>
 
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

class Ring
{
  private:
    static const int maxSize=256;
    volatile byte buffer[maxSize];
    unsigned char starti;
    unsigned char endi;
    bool empty;
  public:
    Ring()
    {
      empty=endi=starti=0;
    };

    void add(byte inChar);
    byte read();
    unsigned int avaiable();
    byte peek(unsigned int);
    byte peek();
    void update();
} Buffer;

void Ring::add(byte inChar)
{
  buffer[endi]=inChar;
  if(starti==endi+1)
    starti++;
  else
    empty=0;
  endi++;
}

byte Ring::read()
{
  byte temp=buffer[starti];
  if(starti!=endi)
    starti++;
  else
    empty=1;
  return temp;
}

unsigned int Ring::avaiable()
{
  if(empty==1)
    return 0;
  else 
    return (endi-starti);
}

byte Ring::peek(unsigned int id)
{
  return buffer[id];
}

byte Ring::peek()
{
  return buffer[starti];
}

void Ring::update()
{
  
}

Timer t;

void setup()
{
  soSerial.begin(115200);
  Serial.begin(9600);
  t.every(1000, printData);
  soSerial.println(">------------<");
}

void loop()
{
  t.update();
}

void printData()
{
  if(Buffer.avaiable()!=0)
    soSerial.println("New:");

  while(Buffer.avaiable()!=0)
  {
    soSerial.print("- ");
    soSerial.println(Buffer.read(),HEX); 
  }
}

void serialEvent()
{
  while (Serial.available())
    Buffer.add((byte)Serial.read()); 
}