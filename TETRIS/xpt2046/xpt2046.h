
#define ADC_MAXVAL 4096
#define X_DIMENSION 240
#define Y_DIMENSION 320

struct Coordinate {
    unsigned int x;
    unsigned int y;
};

struct ADC_read {
    unsigned int x;
    unsigned int y;
};


void init();

// ADC related
struct Coordinate coordFromADC(struct ADC_read reading);
float fractionFromADC(unsigned int ADC_val);
unsigned int dimensionFromFraction(float fraction, unsigned int maxDimension);

// SPI related
struct ADC_read readADC();

// Interrupt related