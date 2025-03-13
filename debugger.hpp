#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <stdlib.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <array>
#include "register.hpp"

using u16 = std::uint16_t;
using u8 = std::uint8_t;
using namespace std;

struct Chip8;

typedef struct Debugger{

  int x = SDL_WINDOWPOS_CENTERED;
  int y = SDL_WINDOWPOS_CENTERED;
  int width = 700;
  int height = 200;

  // for the instruction part left side
  SDL_Rect instruction = {0, 0, 200, 50}; // x=0, y=0, w=200, h=50
  int num_of_instruction = 4;

  // for the keys middle part
  SDL_Rect key = {200, 0, 50, 50}; // x=200, y=0, w=50, h=50
  int num_of_keys = 16;
  std::array<string, 16> keys;
  
  // for the registers right side
  // SDL_Rect register = {};
  SDL_Rect u8_reg = {400, 0, 100, 25};
  int num_of_general_registers = 16; // for the 16 general register note: still have to add the special ones

  // screen (represented by 64*32 pixel screen
  SDL_Window* window = nullptr;
  SDL_Renderer* render = nullptr;
  SDL_Texture* texture = nullptr;

  TTF_Font* font = nullptr;
  SDL_Color text_color = {255, 255, 255};
  SDL_Color green = {0, 255, 0};

  Debugger() {
    keys = {"1", "2", "3", "4", "Q", "W", "E", "R", "A", "S", "D", "F", "Z", "X", "C", "V"};
  }

} Debugger;

void fill_background(Debugger& debugger);
void draw_instructions(Debugger& debugger, Chip8& chip);
void draw_keys(Debugger& debugger);
void draw_registers(Debugger& debugger, Registers* registers);
void setup_fonts(Debugger& debugger);
void render_debugger(Debugger& debugger, Chip8& chip);
void init_debugger(Debugger& debugger, Chip8& chip);

#endif