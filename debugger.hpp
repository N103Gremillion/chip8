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
void setup_fonts(Debugger& debugger);
void render_debugger(Debugger& debugger);
void init_debugger(Debugger& debugger);

typedef struct Debugger{

  int x = SDL_WINDOWPOS_CENTERED;
  int y = SDL_WINDOWPOS_CENTERED;
  int width = 400;
  int height = 200;

  // for the instruction part left side
  SDL_Rect instruction = {0, 0, 195, 50}; // x=0, y=0, w=200, h=50
  int num_of_instruction = 4;

  // for the keys part right side
  SDL_Rect key = {210, 0, 45, 50}; // x=200, y=0, w=50, h=50
  int num_of_keys = 16;
  

  // screen (represented by 64*32 pixel screen
  SDL_Window* window = nullptr;
  SDL_Renderer* render = nullptr;
  SDL_Texture* texture = nullptr;

  TTF_Font* font = nullptr;
  SDL_Color text_color = {255, 255, 255};

} Debugger;

#endif