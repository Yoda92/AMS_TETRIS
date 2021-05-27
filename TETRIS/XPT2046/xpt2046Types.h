#ifndef XPT2046TYPES_H_
#define XPT2046TYPES_H_

typedef struct Coordinate {
    unsigned int x;
    unsigned int y;
} Coordinate;

struct Rectangle
{
    unsigned int topLeftX;
    unsigned int topLeftY;
    unsigned int bottomRightX;
    unsigned int bottomRightY;
};

struct ADC_read {
    unsigned char x;
    unsigned char y;
};


int isCoordInRect(Coordinate coord, struct Rectangle rect);

#endif /* XPT2046TYPES_H_ */
