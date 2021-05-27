
#define ADC_MAXVAL 127
#define X_DIMENSION 240
#define Y_DIMENSION 320


struct ADC_read;
struct Coordinate;

// ADC related
struct Coordinate coordFromADC(struct ADC_read reading);
float fractionFromADC(unsigned int ADC_val);
unsigned int dimensionFromFraction(float fraction, unsigned int maxDimension);

