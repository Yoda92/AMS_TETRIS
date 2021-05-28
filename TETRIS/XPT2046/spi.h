#ifndef SPI_H_
#define SPI_H_

void initSpi();
unsigned char readWriteByte(unsigned char writeThis);
unsigned char readWriteLastByte(unsigned char command);
unsigned char readSimplex(unsigned char command);

#endif /* SPI_H_ */
