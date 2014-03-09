/**
  ******************************************************************************
  * @file    ArduLink.h
  * @author  Patrick José Pereira
  * @version V1.4
  * @date    5-Março-2014
  * @brief   A library to make comunication with simulink
  *
  * By Default:
  *		Terminator 		"\0"
  *		Header  	   	NONE
  *
  * Is advisable that after burn the Arduino, restart him befone the Simulink comunication.
  *		
  * The transmission's order of the bytes is BigEndian.
  *
  * If the Terminator, Header, Baudrate. vector's _size and the
  * vector's format (int32 or single) changed,  REMEMBER to modifie in the
  * Simulink.
  *
  *
  ******************************************************************************/
#ifndef ArduLink_h
#define ArduLink_h

#include <Arduino.h>

class ArduLink
{
	private:
		char* Terminator;
		char Header;
		char buffer[4];		
		int cols;			
		int rows;
    int Hex[16]={'0','1','2','3','4','5','6','8','9','A','B','C','D','E','F'};

		char char2hex(char x);
		void serialFloatPrint(float f); 
		void sendTerminator();
		void sendHeader();
	public:
		void Init(int baudrate, int _rows, int _cols);	
		void Init(int baudrate, int _rows, int _cols, char* term);	
		void Init(int baudrate, int _rows, int _cols, char* term, char head);

		//send buffer to simulink
		///int32
		void SendBuffer(int vector);
		void SendBuffer(int* vector); 
		
		///single
		void SendBuffer(float vector);
		void SendBuffer(float* vector); 		
};

#endif