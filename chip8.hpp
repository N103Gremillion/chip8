#ifndef CHIP8_HPP
#define CHIP8_HPP

#include <cstdint>
#include <iostream>
#include <cstdio>
#include <random>
#include <chrono>
#include "register.hpp"
#include "screen.hpp"
#include "debugger.hpp"
#include "key_map.hpp"

using namespace std;
using u8 = std::uint8_t;
using u16 = std::uint16_t;

const int RAM_SIZE = 4096;

// predefine Chip8
struct Chip8;

void load_rom(const string& fileName, Chip8& chip);
void perform_instruction(u16 instruction, Chip8& chip);
u16 fetch_instruction(Chip8& chip);
void run(Chip8& chip, bool debug);
int get_random_num(int min, int max);
void free_chip(Chip8& chip);
void printMemory(Chip8& chip);
void printStack(Chip8& chip);
void printHex(u16 hex);

typedef struct Chip8{
    
    // 4096 bytes
    u8 *ram;
    Registers* regs;

    // 16 values are allowed 
    u16 *stack;

    // 64 * 32 pixel screen
    Screen screen;
    
    // shows the insturctions being run and the keys being pressed
    Debugger debugger;

    Chip8() {
        ram = (u8*) malloc(sizeof(u8) * RAM_SIZE);
        regs = new Registers();
        stack = (u16*) malloc(sizeof(u16) * 16);
        init_screen(screen);
        init_debugger(debugger, *this);
    };

}Chip8;

#endif 