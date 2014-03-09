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
 *  Data size:		[8 1] or [2 4]
 *  Data type:		int32 or single
 *  Enable blocking mode: 				[x]
 *  Action when data is unavailable: 	Output last received value
 *  Custom value: 0
 *  Block sample time: 0.1
*/
#include "ArduLink.h"
ArduLink simulink;

#define VECTOR 1
#define INT    1

void setup() 
{
	#if VECTOR
		simulink.Init(9600,8,1,"\0",'L'); //baudrate=9600,vector size = 8 ([8 1]),Terminator '\0',Header L
	#else
		simulink.Init(9600,2,4,"\0",'L'); //baudrate=9600,vector size = 8 ([8 1]),Terminator '\0',Header L
	#endif
}

void loop()
{ 
	#if VECTOR
		float float_vector[]={1.32,1.75,3.1,4.9,5.35,0.09,-1.32,-2.9}; 	// float vector
		int int_vector[]={1,2,3,4,-1,-2,-3,-4};						// int vector
	#else
		float float_matrix[]=
		{
			1.32,	1.75,	3.1,	4.9,
			5.35,	0.09,  -1.3,   -2.9
		};// float matrix
		int int_matrix[]=
		{
			1,	2,	3,	4,
		   -1, -2, -3, -4
		};// int matrix
	#endif

 	#if VECTOR
		#if INT
			simulink.SendBuffer(int_vector);   //send buffer
		#else
			simulink.SendBuffer(float_vector); //send buffer
		#endif 	
 	#else
 		#if INT
			simulink.SendBuffer(int_matrix);   //send buffer
		#else
			simulink.SendBuffer(float_matrix); //send buffer
		#endif 	
 	#endif

	delay(10);
}
