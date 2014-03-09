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
 *  Data size:		[2 4]
 *  Data type:		single
 *  Enable blocking mode: 				[x]
 *  Action when data is unavailable: 	Output last received value
 *  Custom value: 0
 *  Block sample time: 0.1
*/
#include <ArduLink.h>
ArduLink simulink;

void setup() 
{
	simulink.Init(9600,2,4,"\0",'L'); //baudrate=9600,matrix size = [2 4],Terminator '\0',Header L
}

void loop()
{ 
	float float_matrix[]=
	{
		1.32,	1.75,	3.1,	4.9,
		5.35,	0.09,  -1.3,   -2.9
	};// float matrix

	simulink.SendBuffer(float_matrix);   //send buffer

	delay(10);
}
