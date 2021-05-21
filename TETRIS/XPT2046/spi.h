#define F_CPU 16000000

void initSpi();
unsigned char readWriteByte(unsigned char writeThis);
void writeByte(unsigned char writeThis);
unsigned char readByte();