//Sample to Simulink comunication
#include "ArduLink.h"

ArduLink simulink;

void setup() 
{
	simulink.Init(9600,10); //baudrate=9600,vector size = 10 ([10 1])
}

void loop()
{ 
	int patrick[]={1,2,3,4,5,0,-1,-2,-3,-4}; //the vector 
	simulink.SendBuffer(patrick); //send buffer
	delay(10);
}
