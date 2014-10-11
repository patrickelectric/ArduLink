#ifndef ArduLinkCircularBuffer_h
#define ArduLinkCircularBuffer_h

#include <Arduino.h>

class CircularBuffer
{
  private:
    static const int maxSize=256;
    volatile byte buffer[maxSize];
    unsigned char starti;
    unsigned char endi;
    bool empty;
  public:
    CircularBuffer()
    {
      clear();
    };

    void add(byte inChar);
    byte read();
    unsigned int avaiable();
    byte peek(unsigned int);
    byte peek();
    void update();
    void clear();
};

#endif