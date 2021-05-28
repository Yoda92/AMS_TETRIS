#ifndef SPI_H_
#define SPI_H_

void initSpi();
unsigned char ReadWriteByte(unsigned char writeThis);
unsigned char ReadWriteLastByte(unsigned char command);
unsigned char ReadSimplex(unsigned char command);

#endif /* SPI_H_ */
