#include "register.hpp"
#include "chip8.hpp"

int main() {
    Chip8 chip;    
    load_rom(string("Pong.ch8"), chip);
    printMemory(chip);
}   
