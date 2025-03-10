#include "register.hpp"
#include "chip8.hpp"
#include <SDL2/SDL.h>

string games[5] = {"./game_roms/snake.ch8", "./game_roms/octopeg.ch8"};
string demo[5] = {"./demo_roms/1dcell.ch8", "./demo_roms/octojam2title.ch8", "./demo_roms/Zero.ch8", "./demo_roms/octojam5title.ch8"};

bool debug_mod = false;

int main() {
    Chip8 chip;    
    load_rom(string(demo[3]), chip);
    run(chip, debug_mod);
    free_chip(chip);
}   
