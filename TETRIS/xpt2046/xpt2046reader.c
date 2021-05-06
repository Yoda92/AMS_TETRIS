#include <avr/io.h>
#include "spi.h"

#define READ_X 0x91
#define READ_Y 0xD1
#define READ_Z 0x


#define START_BIT = 7
#define CHANNEL_SELECT_MSB 6
#define 



void init(){
    initSpi();
}

unsigned char read(){

}

unsigned char makeControlByte()