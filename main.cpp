#include "register.hpp"
#include "chip8.hpp"
#include <SDL2/SDL.h>

#define ROM "./game_roms/RPS.ch8"

bool debug_mod = false;

int main() {
    Chip8 chip;    
    load_rom(string(ROM), chip);
    run(chip, debug_mod);
    free_chip(chip);
}   
