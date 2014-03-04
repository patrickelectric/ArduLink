//Class to make comunication with simulink

//Terminator NULL
//Data Size ["Vector size" 1]
class ArduLink
{
	private:
		char buffer[4];		//Buffer 8 bits
		int vector_size;	//Vector size
	public:
		void Init(int baudrate,int size);	// start the class  (baudrate , vector size)
		void SendBuffer(int* vector); 		// send buffer to simulink
};

void ArduLink::Init(int baudrate,int size)	
{
	vector_size=size;
	Serial.begin(baudrate);
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
		{
			Serial.write(buffer[i]);
		}
	}
	Serial.write("\0");
};


	/*
	//int 32 bits [2 1]
	//[10 0]
	//[-10 6]
	//10
	Serial.write(0x0A); //lsb1
	Serial.write(0x00); //lsb2
	Serial.write(0x00); //msb1 
	Serial.write(0x00); //msb2 
	delay(10);

	//-10
	Serial.write(0xF6); //lsb1
	Serial.write(0xFF); //lsb2 
	Serial.write(0xFF); //msb1 
	Serial.write(0xFF); //msb2 
	delay(10);

	//0
	Serial.write(0x00); //lsb1
	Serial.write(0x00); //lsb2
	Serial.write(0x00); //msb1 
	Serial.write(0x00); //msb2 
	delay(10);

	//-6
	Serial.write(0xFA); //lsb1
	Serial.write(0xFF); //lsb2 
	Serial.write(0xFF); //msb1 
	Serial.write(0xFF); //msb2 
	delay(10)
	*/
