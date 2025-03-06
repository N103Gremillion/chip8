#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <stdlib.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 0

using u16 = std::uint16_t;
using u8 = std::uint8_t;
using namespace std;

struct Debugger;

void fill_background(Debugger& debugger);
void draw_instructions(Debugger& debugger);
void draw_keys(Debugger& debugger);
void draw_registers(Debugger& debugger);
void setup_fonts(Debugger& debugger);
void render_debugger(Debugger& debugger);
void init_debugger(Debugger& debugger);

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

} Debugger;

#endif