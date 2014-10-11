#include <CircularBuffer.h>

void CircularBuffer::add(byte inChar)
{
  buffer[endi]=inChar;
  if(starti==endi+1)
    starti++;
  else
    empty=0;
  endi++;
}

byte CircularBuffer::read()
{
  byte temp=buffer[starti];
  if(starti!=endi)
    starti++;
  else
    empty=1;
  return temp;
}

unsigned int CircularBuffer::avaiable()
{
  if(empty==1)
    return 0;
  else 
    return (endi-starti);
}

byte CircularBuffer::peek(unsigned int id)
{
  return buffer[id];
}

byte CircularBuffer::peek()
{
  return buffer[starti];
}

void CircularBuffer::update()
{
}

void CircularBuffer::clear()
{
  empty=endi=starti=0;
}