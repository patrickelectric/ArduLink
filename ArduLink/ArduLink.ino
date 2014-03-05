//Sample to Simulink comunication
#include "ArduLink.h"

ArduLink simulink;

void setup() 
{
	simulink.Init(9600,4); //baudrate=9600,vector size = 10 ([10 1])
}

void loop()
{ 
	float patrick[]={1.32,1.75,3.1,4.1,5.1,0.1,-1.1,-2.1,-3.1,-4.1}; //the vector 
	simulink.SendBuffer2(patrick); //send buffer

	delay(10);
}
