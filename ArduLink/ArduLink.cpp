/**
  ******************************************************************************
  * @file    ArduLink.h
  * @author  Patrick José Pereira
  * @version V1.4
  * @date    9-Março-2014
  * @brief   A library to make comunication with simulink
  *
  * By Default:
  *		Terminator 		"\0"
  *		Header  		NONE
  *
  ******************************************************************************/

#include <ArduLink.h>

/** \brief Starts the initials values and parameters. 
  *
  * @param  baudrate  Define the baud rate
  * @param 	_rows     Define the matrix's rows
  * @param 	_cols     Define the matrix's cols
  * @retval NONE
  */
void ArduLink::Init(int baudrate, int _rows, int _cols)	
{
	cols=_cols;
	rows=_rows;
	Header=0x00;
	Terminator="\0";
	Serial.begin(baudrate);
}

/** \brief Starts the initials values and parameters. 
  *
  * @param  baudrate  Define the baud rate
  * @param 	_rows     Define the matrix's rows
  * @param 	_cols     Define the matrix's cols
  * @param 	term      Define the Simulink's Terminator 
  * @retval NONE
  */
void ArduLink::Init(int baudrate, int _rows, int _cols, char* term)	
{
	cols=_cols;
	rows=_rows;
	Header=0x00;
	Terminator=term;
	Serial.begin(baudrate);
}

/** \brief Starts the initials values and parameters. 
  *
  * @param  baudrate  Define the baud rate
  * @param 	_rows     Define the matrix's rows
  * @param 	_cols     Define the matrix's cols
  * @param 	term      Define the Simulink's Terminator 
  * @param 	head      Define the Simulink's Header
  * @retval NONE
  */
void ArduLink::Init(int baudrate, int _rows, int _cols, char* term, char head)	
{
	cols=_cols;
	rows=_rows;
	Header=head;
	Terminator=term;
	Serial.begin(baudrate);
};

/** \brief Send the float vector to serial.
  * It can be a single float of an array
  *
  * @param  vector    Indicates the initial address of the vector
  * @retval NONE
  */
void ArduLink::SendBuffer(float* vector)
{
	sendHeader();
	for (int i = 0; i < cols; ++i)
		for (int u = 0; u < rows; ++u)
		serialFloatPrint(vector[u*cols+i]);
	sendTerminator();
};

void ArduLink::SendBuffer(float vector)
{
	sendHeader();
	serialFloatPrint(vector);	
	sendTerminator();
};

/** \brief Send the int vector to serial.
  * It can be a single int of an array
  *
  * @param  vector    Indicates the initial address of the vector
  * @retval NONE
  */
void ArduLink::SendBuffer(int* vector)
{
	sendHeader();

	for (int i = 0; i < cols; ++i)
		for (int u = 0; u < rows; ++u)
		{
			buffer[0]=vector[u*cols+i];
			buffer[1]=vector[u*cols+i]>>8;
			buffer[2]=vector[u*cols+i]>>16;
			buffer[3]=vector[u*cols+i]>>24;

			for (int i = 0; i < 4; ++i)
				Serial.write(buffer[i]);
		}
	sendTerminator();
};

void ArduLink::SendBuffer(int vector)
{
	sendHeader();

	buffer[0]=vector;
	buffer[1]=vector>>8;
	buffer[2]=vector>>16;
	buffer[3]=vector>>24;

	for (int i = 0; i < 4; ++i)
		Serial.write(buffer[i]);

	sendTerminator();
};

/** \brief Transform a letter in a hexadecimal value
  *
  * @param  x          the char that have 0 to A
  * @retval return a char that have the value 0x00 to 0x0A
  */
char ArduLink::char2hex(char x)
{
  int i;
	for (i = 0; x!=Hex[i]; ++i);
  return (char) i;
}

/** \brief Transform a float to SINGLE and send by the serial in BigEndian
  * found in http://forum.arduino.cc/index.php?topic=112597.0
  *
  * @param  f          the float number
  */
void ArduLink::serialFloatPrint(float f) 
{
	byte * b = (byte *) &f;
  	Serial.write(b,4);
}

/** \brief Send the terminator by the serial
  *
  * @param  NONE
  */
void ArduLink::sendTerminator()
{
	Serial.write(Terminator);	
}

/** \brief Send the Header by the serial
  *
  * @param  NONE
  */
void ArduLink::sendHeader()
{
	if(Header!=0x00)
		Serial.write(Header);	
}