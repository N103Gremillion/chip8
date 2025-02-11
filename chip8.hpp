#ifndef CHIP8_HPP
#define CHIP8_HPP


// constants
#define RAM_START 0x000
#define CHIP8_PROGRAM_START = 0X200
#define ETI660_PROGRAM_START = 0X600
#define RAM_END = 0XFFF

class Chip8 {
    public:
        // memory
        
        // General 8bit Registers
        int V0;
        int V1; 
        int V2; 
        int V3; 
        int V4;
        int V5;
        int V6;
        int V7;
        int V8;
        int V9;
        int VA;
        int VB;
        int VC;
        int VD;
        int VE;
        int VF;


        // 16bit register for memory addresses
        int I;
        
        // sepecial 8bit registers for delay and sound timers
        int delay_timer;
        int sound_timer;

        // 16bit program counter
        int PC;

        // 8bit stack pointer
        int SP;
}


#endif CHIP8_HPP