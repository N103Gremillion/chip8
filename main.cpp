#include "register.hpp"
#include "chip8.hpp"
#include <SDL2/SDL.h>

int main() {
    Chip8 chip;    
    load_rom(string("Maze.ch8"), chip);
    run(chip);
    free_chip(chip);
}   
