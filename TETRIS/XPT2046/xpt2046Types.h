#ifndef XPT2046TYPES_H_
#define XPT2046TYPES_H_

typedef struct Coordinate {
    unsigned int x;
    unsigned int y;
} Coordinate;

typedef struct Rectangle
{
    unsigned int topLeftX;
    unsigned int topLeftY;
    unsigned int bottomRightX;
    unsigned int bottomRightY;
} Rectangle;

typedef struct ADC_read {
    unsigned char x;
    unsigned char y;
} ADC_read;

int IsCoordInRect(Coordinate coord, Rectangle rect);

#endif /* XPT2046TYPES_H_ */
