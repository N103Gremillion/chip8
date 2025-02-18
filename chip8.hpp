#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <iostream>
#include <cstdio>
#include "register.hpp"

using namespace std;
using u8 = std::uint8_t;
using u16 = std::uint16_t;

const int RAM_SIZE = 4096;

// predefine Chip8
struct Chip8;

void load_rom(const string& fileName, Chip8& chip);
void perform_instruction(u16 instruction);
u16 fetch_intruction(Chip8& chip);
void run(Chip8& chip);
void printMemory(Chip8& chip);
void printStack(Chip8& chip);
void printHex(u16 hex);

typedef struct Chip8{
    
    // 4096 bytes
    u8 *ram;
    Registers* regs;

    // 16 values are allowed 
    u16 *stack;

    // screen (represented by 64*32 pixel screen)
    bool **screen;
    int screen_width;
    int screen_height;

    Chip8() {
        ram = (u8*) malloc(sizeof(u8) * RAM_SIZE);
        regs = new Registers();
        stack = (u16*) malloc(sizeof(u16) * 16);
        screen_width = 64;
        screen_height = 32;
        screen = (bool**) malloc(sizeof(bool*) * 32);

        for (int i = 0; i < 32; ++i) {
            screen[i] = (bool*) malloc(sizeof(bool) * 64);
        }
    };

}Chip8;

#endif 