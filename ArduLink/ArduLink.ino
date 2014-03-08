/* Examble to Simulink comunication
 *
 * In "Serial Configuraton"
 * 	Baud rate:   	9600
 * 	Data bits:   	8
 * 	Parity:      	none
 * 	Stop bits:   	1
 * 	Bytes order: 	BigEndian
 * 	Flow control:	none
 * 	Timeout:		10
 *
 * In "Serial Receive"
 *  Header: 		L
 *  Terminator:		NULL ('\0')
 *  Data size:		[8 1]
 *  Data type:		int32 or single
 *  Enable blocking mode: 				[x]
 *  Action when data is unavailable: 	Output last received value
 *  Custom value: 0
 *  Block sample time: 0.1
*/
#include "ArduLink.h"
ArduLink simulink;

void setup() 
{
	simulink.Init(9600,8,"\0",'L'); //baudrate=9600,vector size = 8 ([8 1]),Terminator '\0',Header L
}

void loop()
{ 
	float patrick[]={1.32,1.75,3.1,4.9,5.35,0.09,-1.32,-2.9}; 	// float vector
	int patrick2[]={1,2,3,4,-1,-2,-3,-4};						// int vector

	// 0 - send int32 example
	// 1 - send float (single) example

	#if 1
		simulink.SendBuffer(patrick); //send buffer
	#else
		simulink.SendBuffer(patrick2); //send buffer
	#endif

	delay(10);
}
