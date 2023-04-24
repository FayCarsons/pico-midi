#include "pico/stdlib.h"

#define ADDRESS 0x3C
#define WRITE_REG 0x00
#define ON_REG 0xAF
#define OFF_REG 0xAE

class Display {
    public:
        int address;
        unsigned char width;
        unsigned char height;
        unsigned char buffer[1024];

        void on() {};
        void off() {};
        int write(unsigned char*, unsigned char) {};
};

int Display::write(unsigned char* data, unsigned char len) {

}