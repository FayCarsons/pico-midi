#include "pico/stdlib.h"

#define ADDRESS 0x3C
#define WRITE_REG 0x00
#define ON_REG 0xAF
#define OFF_REG 0xAE

#define WIDTH 128
#define HEIGHT 64

class Display
{
public:
    // Address field for convenience 
    int address;

    // Dimensions 
    unsigned char width;
    unsigned char height;

    // Buffer for display data(?)
    unsigned char buffer[1024];

    // Turn display on/off
    void on() {};
    void off() {};

    // Write data to display
    int write(unsigned char *, unsigned char){};
};

int Display::write(unsigned char *data, unsigned char len)
{

}