#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <iostream>

// constants
#define RAM_START 0x000
#define RAM_END = 0XFFF

using u8 = std::uint8_t;
using u16 = std::uint16_t;

typedef struct Chip8{
    
    // memory 4096 bytes
    u8 ram[4096];

    // General 8bit Registers
    u8 V[16];
    
    // 16bit stack
    u16 stack[16];

    // specific registers
    u16 I; // memory address register
    u8 delay_timer;
    u8 sound_timer;
    u16 PC; // program counter 
    u8 SP; // stack pointer

    // screen (represented by 64*32 pixel screen)
    bool screen[32][64];

    Chip8() {
        std::fill(std::begin(ram), std::end(ram), 0);
        std::fill(std::begin(V), std::end(V), 0);
        std::fill(std::begin(stack), std::end(stack), 0);
        I = 0;
        delay_timer = 0;
        sound_timer = 0;
        PC = 0x200; // this is the standard starting adress for CHIP-8 programs
        SP = 0;
        std::fill(&screen[0][0], &screen[0][0] +  sizeof(screen), false);
    }

}Chip8;

#endif 