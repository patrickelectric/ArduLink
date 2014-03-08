/**
  ******************************************************************************
  * @file    ArduLink.h
  * @author  Patrick José Pereira
  * @version V1.2
  * @date    5-Março-2014
  * @brief   A library to make comunication with simulink
  *
  * By Default:
  *		Terminator 		"\0"
  *		Header  		NONE
  *
  * Is advisable that after burn the Arduino, restart him befone the Simulink comunication.
  *		
  * The transmission's order of the bytes is BigEndian.
  *
  * If the Terminator, Header, Baudrate. vector's size and the
  * vector's format (int32 or single) changed,  REMEMBER to modifie in the
  * Simulink.
  *
  * Vector's size = ['vector's size' 1] in Simulink.
  *
  * @Todo Integrate function that send matrices.
  ******************************************************************************/

class ArduLink
{
	private:
		char* Terminator;
		char Header;
		char buffer[4];		//Buffer 8 bits
		int vector_size;	//Vector's size
    int Hex[16]={'0','1','2','3','4','5','6','8','9','A','B','C','D','E','F'};

		char char2hex(char x);
		void serialFloatPrint(float f); 
		void sendTerminator();
		void sendHeader();
	public:
		void Init(int baudrate, int size);	
		void Init(int baudrate, int size, char* term);	
		void Init(int baudrate, int size, char* term, char head);

		//send buffer to simulink
		///int32
		void SendBuffer(int vector);
		void SendBuffer(int* vector); 
		
		///single
		void SendBuffer(float vector);
		void SendBuffer(float* vector); 		
};

/** \brief Starts the initials values and parameters. 
  *
  * @param  baudrate  Define the baud rate
  * @param 	size      Define the vector's size
  * @param 	term      Define the Simulink's Terminator 
  * @param 	head      Define the Simulink's Header
  * @retval NONE
  */
void ArduLink::Init(int baudrate, int size)	
{
	vector_size=size;
	Header=0x00;
	Terminator="\0";
	Serial.begin(baudrate);
};

void ArduLink::Init(int baudrate, int size,char* term)	
{
	vector_size=size;
	Header=0x00;
	Terminator=term;
	Serial.begin(baudrate);
};

void ArduLink::Init(int baudrate, int size, char* term, char head)	
{
	vector_size=size;
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
	for (int u = 0; u < vector_size; ++u)
		serialFloatPrint(vector[u]);
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

	for (int u = 0; u < vector_size; ++u)
	{
		buffer[0]=vector[u];
		buffer[1]=vector[u]>>8;
		buffer[2]=vector[u]>>16;
		buffer[3]=vector[u]>>24;

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