#include "register.hpp"
#include "chip8.hpp"

int main() {
    Chip8 chip;    
    load_rom(string("Pong.ch8"), chip);
    u16 instruc = fetch_intruction(chip);
    printHex(instruc);
    perform_instruction(instruc);
}   
