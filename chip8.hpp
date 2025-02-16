#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <iostream>

using namespace std;
using u8 = std::uint8_t;
using u16 = std::uint16_t;

const u16 ROM_START = 0X200;
const int RAM_SIZE = 4096;

// predefine Chip8
struct Chip8;

void load_rom(const string& fileName, Chip8& chip);
void printMemory(Chip8& chip);
void printStack(Chip8& chip);

typedef struct Chip8{
    
    // 4096 bytes
    u8 *ram;

    // General 8bit Registers
    u8 V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF;

    // 16 values are allowed 
    u16 *stack;

    // specific registers
    u16 I; // memory address register
    u8 delay_timer;
    u8 sound_timer;

    // screen (represented by 64*32 pixel screen)
    bool **screen;
    int screen_width;
    int screen_height;

    Chip8() {
        ram = (u8*) malloc(sizeof(u8) * RAM_SIZE);
        stack = (u16*) malloc(sizeof(u16) * 16);
        I = 0x0000;
        delay_timer = 0x00;
        sound_timer = 0x00;
        screen_width = 64;
        screen_height = 32;
        screen = (bool**) malloc(sizeof(bool*) * 32);

        for (int i = 0; i < 32; ++i) {
            screen[i] = (bool*) malloc(sizeof(bool) * 64);
        }
    };

}Chip8;

#endif 