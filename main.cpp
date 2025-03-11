#include "register.hpp"
#include "chip8.hpp"
#include <SDL2/SDL.h>

string games[5] = {"./game_roms/snake.ch8", "./game_roms/RPS.ch8", "./game_roms/glitchGhost.ch8", "./game_roms/pumpkindressup.ch8", "./game_roms/masquer8.ch8"};
string demo[6] = {"./demo_roms/1dcell.ch8", "./demo_roms/octojam2title.ch8", "./demo_roms/Zero.ch8", "./demo_roms/octojam5title.ch8", "./demo_roms/danm8ku.ch8", "./demo_roms/lights.ch8"};

bool debug_mod = false;

int main() {
    Chip8 chip;    
    load_rom(string(demo[5]), chip);
    run(chip, debug_mod);
    free_chip(chip);
}   
