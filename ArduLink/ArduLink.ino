//Sample to Simulink comunication
#include "ArduLink.h"

ArduLink simulink;

void setup() 
{
	simulink.Init(9600,10); //baudrate=9600,vector size = 10 ([10 1])
}

void loop()
{ 
	float patrick[]={1,2,3,4,5,0,-1,-2,-3,-4}; //the vector 
	//simulink.SendBuffer(patrick); //send buffer
	float teste=1.25;
	//Serial.println(teste,BIN);
	/*
	//3eaa aaab   ≈ 1/3
	Serial.write(0xab);
	Serial.write(0xaa);
	Serial.write(0xaa);
	Serial.write(0x3e);
	Serial.write("\0");
	*/
	//8192 323E   =0.174387;
	//Serial.print(0.1742,BIN);
	serialFloatPrint(1.32);
	Serial.write("\0");
	delay(1000);
}

// http://stackoverflow.com/questions/4315190/single-precision-big-endian-float-values-to-pythons-float-double-precision-bi
void serialFloatPrint(float f) 
{

	byte * b = (byte *) &f;
	char vector[8];
	Serial.print("f:");
	for(int i=0; i<4; i++) 
	{
		byte b1 = (b[i] >> 4) & 0x0f;
		byte b2 = (b[i] & 0x0f);

		char c1 = (b1 < 10) ? ('0' + b1) : 'A' + b1 - 10;
		char c2 = (b2 < 10) ? ('0' + b2) : 'A' + b2 - 10;

		
		vector[7-i*2]=c2;
		vector[6-i*2]=c1;
	}
	for(int i=0; i<8; i++)
		Serial.write(vector[i]);
	//Serial.println();
}

char char2hex(char x)
{
	switch (x) 
	{
    case '0':
      return 0;
      break;
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 5;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case 'A':
      return 0xA;
      break;
    case 'B':
      return 0x0b;
      break;
    case 'C':
      return 0x0c;
      break;
    case 'D':
      return 0x0d;
      break;
    case 'E':
      return 0x0e;
      break;
    case 'F':
      return 0x0f;
      break;

  	}
}
