#include "KangooCan.h"
#include <iostream>
using namespace std;


const uint8_t messageCount = 77;
KangooCan kangooCan;

uint8_t frame155[] = {0x1D, 0x47, 0xD2, 0x54, 0x69, 0xA8, 0x02, 0xE3};
uint8_t frame424[] = {0x11, 0x40, 0x56, 0x84, 0x34, 0x66, 0xF8, 0x35};
uint8_t frame425[] = {0x25, 0xD8, 0x44, 0x9C, 0x42, 0x3A, 0xD1, 0x1A};

uint8_t canMessages [messageCount][8] = {
    {0x10, 0x14, 0x61, 0x61, 0x00, 0x10, 0x5F, 0x90},
    {0x21, 0xC8, 0xC8, 0xC8, 0xCC, 0xCC, 0x00, 0x00},
    {0x22, 0x1B, 0xB5, 0x00, 0x00, 0x05, 0x92, 0xC8},
    {0x10, 0x0E, 0x61, 0x66, 0x00, 0x01, 0x00, 0x7D},
    {0x21, 0x00, 0x25, 0x00, 0x59, 0x00, 0x00, 0x00},
    {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x1D, 0x61, 0x03, 0x01, 0x80, 0x1A, 0x4E},
    {0x21, 0x1B, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x01},
    {0x22, 0x81, 0x01, 0x7E, 0x00, 0x00, 0x00, 0xFF},
    {0x23, 0xFF, 0xFF, 0xFF, 0x01, 0x1A, 0xF9, 0x00},
    {0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x4D, 0x61, 0x04, 0x0A, 0x2B, 0x34, 0x0A},
    {0x21, 0x32, 0x34, 0x0A, 0x3A, 0x34, 0x0A, 0x3A},
    {0x22, 0x34, 0x0A, 0x33, 0x34, 0x0A, 0x29, 0x34},
    {0x23, 0x0A, 0x2C, 0x34, 0x0A, 0x39, 0x34, 0x0A},
    {0x24, 0x3D, 0x34, 0x0A, 0x33, 0x34, 0x0A, 0x36},
    {0x25, 0x34, 0x0A, 0x30, 0x34, 0x0A, 0x0F, 0x35},
    {0x26, 0x0A, 0x0F, 0x35, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x27, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x29, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x2A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x34, 0x34},
    {0x2B, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x56, 0x61, 0x06, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x21, 0x00, 0x00, 0x15, 0x49, 0x00, 0x00, 0x00},
    {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x29, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF},
    {0x2A, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x2C, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x0E, 0x61, 0x07, 0x00, 0x00, 0x00, 0xC9},
    {0x21, 0x01, 0x01, 0x00, 0x40, 0x00, 0x24, 0x03},
    {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    //Cell voltages 
    {0x10, 0x7E, 0x61, 0x41, 0x0F, 0x03, 0x0F, 0x02},
    {0x21, 0x0F, 0x01, 0x0F, 0x04, 0x0F, 0x06, 0x0F},
    {0x22, 0x03, 0x0F, 0x02, 0x0F, 0x06, 0x0E, 0xFD},
    {0x23, 0x0F, 0x06, 0x0F, 0x06, 0x0F, 0x00, 0x0F},
    {0x24, 0x00, 0x0F, 0x06, 0x0F, 0x03, 0x0F, 0x06},
    {0x25, 0x0E, 0xF3, 0x0F, 0x03, 0x0F, 0x02, 0x0F},
    {0x26, 0x01, 0x0F, 0x06, 0x0F, 0x03, 0x0F, 0x03},
    {0x27, 0x0E, 0xFC, 0x0F, 0x0D, 0x0F, 0x07, 0x0F},
    {0x28, 0x06, 0x0F, 0x08, 0x0F, 0x02, 0x0F, 0x04},
    {0x29, 0x0F, 0x07, 0x0F, 0x0E, 0x0F, 0x0D, 0x0F},
    {0x2A, 0x02, 0x0F, 0x02, 0x0F, 0x06, 0x0F, 0x03},
    {0x2B, 0x0F, 0x02, 0x0F, 0x02, 0x0F, 0x01, 0x0F},
    {0x2C, 0x07, 0x0F, 0x03, 0x0F, 0x04, 0x0F, 0x02},
    {0x2D, 0x0F, 0x06, 0x0F, 0x04, 0x0F, 0x03, 0x0F},
    {0x2E, 0x00, 0x0F, 0x06, 0x0F, 0x03, 0x0F, 0x01},
    {0x2F, 0x0F, 0x06, 0x0F, 0x06, 0x0F, 0x07, 0x0F},
    {0x20, 0x00, 0x0F, 0x03, 0x0F, 0x06, 0x0E, 0xFD},
    {0x21, 0x0F, 0x06, 0x0F, 0x08, 0x0F, 0x01, 0x0F},
    {0x22, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

    {0x10, 0x4A, 0x61, 0x42, 0x0F, 0x06, 0x0F, 0x08},
    {0x21, 0x0F, 0x08, 0x0F, 0x04, 0x0F, 0x00, 0x0F},
    {0x22, 0x06, 0x0F, 0x09, 0x0F, 0x08, 0x0F, 0x02},
    {0x23, 0x0F, 0x02, 0x0F, 0x02, 0x0E, 0xF9, 0x0F},
    {0x24, 0x0B, 0x0F, 0x02, 0x0F, 0x02, 0x0F, 0x06},
    {0x25, 0x0E, 0xFD, 0x0F, 0x06, 0x0F, 0x08, 0x0F},
    {0x26, 0x0C, 0x0E, 0xFE, 0x0E, 0xFC, 0x0F, 0x04},
    {0x27, 0x0F, 0x00, 0x0F, 0x07, 0x0F, 0x06, 0x0F},
    {0x28, 0x06, 0x0F, 0x03, 0x0F, 0x01, 0x0F, 0x04},
    {0x29, 0x0F, 0x02, 0x0F, 0x02, 0x0F, 0x03, 0x0F},
    {0x2A, 0x04, 0x90, 0x27, 0x8F, 0xF1, 0x00, 0x00},

    {0x10, 0x34, 0x61, 0x01, 0x13, 0x8D, 0x13, 0x88},
    {0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x87},
    {0x23, 0x0D, 0x5E, 0x10, 0xCC, 0x19, 0xC3, 0x00},
    {0x24, 0x00, 0x04, 0xB9, 0x00, 0x00, 0x00, 0x00},
    {0x25, 0x00, 0x00, 0x00, 0x0A, 0x51, 0x84, 0x00},
    {0x26, 0x00, 0x03, 0x6C, 0x10, 0x27, 0x10, 0x00},
    {0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}


};

int main() { 
    cout << "Processing Can Messages" << endl;
    for (int i = 0; i < messageCount; i++) {
        kangooCan.ProcessISOTPResponse(canMessages[i]);
    }

    kangooCan.handleFrame155(frame155);
    kangooCan.handleFrame424(frame424);
    kangooCan.handleFrame425(frame425);

    kangooCan.printData();
}	