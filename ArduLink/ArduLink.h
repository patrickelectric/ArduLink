//Class to make comunication with simulink

//Terminator NULL
//Data Size ["Vector size" 1]

//Byte order BigEndian
class ArduLink
{
	private:
		char buffer[4];		//Buffer 8 bits
		int vector_size;	//Vector size

		char char2hex(char x);
		void serialFloatPrint(float f); 
	public:
		void Init(int baudrate,int size);	// start the class  (baudrate , vector size)
		void SendBuffer(int* vector); 		// send buffer to simulink
		void SendBuffer(float* vector); 		
		void SendBuffer(int vector);
		void SendBuffer(float vector);
};

void ArduLink::Init(int baudrate,int size)	
{
	vector_size=size;
	Serial.begin(baudrate);
};

void ArduLink::SendBuffer(float* vector)
{
	for (int u = 0; u < vector_size; ++u)
		serialFloatPrint(vector[u]);
	Serial.write("\0");
};

void ArduLink::SendBuffer(float vector)
{
	serialFloatPrint(vector);	
	Serial.write("\0");
};

void ArduLink::SendBuffer(int* vector)
{
	for (int u = 0; u < vector_size; ++u)
	{
		buffer[0]=vector[u];
		buffer[1]=vector[u]>>8;
		buffer[2]=vector[u]>>16;
		buffer[3]=vector[u]>>24;

		for (int i = 0; i < 4; ++i)
			Serial.write(buffer[i]);
	}
	Serial.write("\0");
};

void ArduLink::SendBuffer(int vector)
{
	buffer[0]=vector;
	buffer[1]=vector>>8;
	buffer[2]=vector>>16;
	buffer[3]=vector>>24;

	for (int i = 0; i < 4; ++i)
		Serial.write(buffer[i]);

	Serial.write("\0");
};

char ArduLink::char2hex(char x)
{
	switch (x) 
	{
    case '0':
      return 0x00;
      break;
    case '1':
      return 0x01;
      break;
    case '2':
      return 0x02;
      break;
    case '3':
      return 0x03;
      break;
    case '4':
      return 0x05;
      break;
    case '5':
      return 0x05;
      break;
    case '6':
      return 0x06;
      break;
    case '7':
      return 0x07;
      break;
    case '8':
      return 0x08;
      break;
    case '9':
      return 0x09;
      break;
    case 'A':
      return 0x0a;
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

//http://forum.arduino.cc/index.php?topic=112597.0
//BigEndian
void ArduLink::serialFloatPrint(float f) 
{
	byte * b = (byte *) &f;
  	Serial.write(b,4);
}