#include <Arduino.h>
#include "GDDriver.h"
#include "xpt2046reader.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "xpt2046ADC.h"

ISR(INT4_vect)
{
  FillRectangle(140, 0, 320 - 140, 100, 31, 0, 20);
  
  unsigned int Z_adc;

  struct ADC_read reading;

  unsigned int x;
  unsigned int y;

  onScreenPressed(&x,y, &Z_adc);

  reading.x = x;
  reading.y = y;
  struct Coordinate coordinate = coordFromADC(reading);
  FillRectangle(coordinate.x, 5, coordinate.y, 5, 31, 0, 20);
}



void setup()
{
  initReader();
  // Initialize the display
  DisplayInit();

  // All pixels white (background)
  FillRectangle(0, 0, 320, 240, 31, 63, 31);
  // Draw red parts of danish flag
  FillRectangle(0, 140, 100, 100, 31, 0, 0);
  FillRectangle(0, 0, 100, 100, 31, 0, 0);
  FillRectangle(140, 0, 320 - 140, 100, 31, 0, 0);
  FillRectangle(140, 140, 320 - 140, 100, 31, 0, 0);
  DisplayOn();
}

void loop()
{
}