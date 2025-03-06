#include "debugger.hpp"
#include <iostream>

void fill_background(Debugger& debugger) {
  SDL_SetRenderDrawColor(debugger.render, BLACK);
  SDL_RenderClear(debugger.render);
  SDL_SetRenderDrawColor(debugger.render, WHITE);
}

void draw_instructions(Debugger& debugger) {
  // reset location of instruction to correct starting value
  debugger.instruction.y = 0;

  for (int i = 0; i < debugger.num_of_instruction; i++) {
    SDL_Surface* text_surface = TTF_RenderText_Solid(debugger.font, "instruction", debugger.text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface);
    SDL_RenderDrawRect(debugger.render, &debugger.instruction);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &debugger.instruction);
    debugger.instruction.y += debugger.instruction.h;
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }
}

void draw_keys(Debugger& debugger) {
  // reset location of key to correct starting value
  debugger.key.x = 200;
  debugger.key.y = 0;
  SDL_Rect text_rect = {200, 0, debugger.key.w / 2, debugger.key.h / 2};
  const char* keys[] = {"1", "2", "3", "4", "Q", "W", "E", "R", "A", "S", "D", "F", "Z", "X", "C", "V"};

  for (int i = 0; i < debugger.num_of_keys; i++) {
    if (i % 4 == 0 && i != 0) {
      debugger.key.y += debugger.key.h;
      text_rect.y += debugger.key.h;
      debugger.key.x = 200;
      text_rect.x = 200;
    } else if (i != 0){
      debugger.key.x += debugger.key.w;
      text_rect.x += debugger.key.w;
    }
    SDL_Surface* text_surface = TTF_RenderText_Solid(debugger.font, keys[i], debugger.text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface); 
    SDL_RenderDrawRect(debugger.render, &debugger.key);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }
}

void draw_registers(Debugger& debugger) {
  debugger.u8_reg.x = 400;
  debugger.u8_reg.y = 0;
  // char* text = "V: E693";
  // render the general Vx registers first
  for (int i = 0; i < debugger.num_of_general_registers; i++){
    if (i % 3 == 0 && i != 0){
      debugger.u8_reg.x = 400;
      debugger.u8_reg.y += debugger.u8_reg.h;
    } else if (i != 0){
      debugger.u8_reg.x += debugger.u8_reg.w;
    }
    SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);
  }
  // render the remaning specific registers
  SDL_Rect u16_reg = {debugger.u8_reg.x + debugger.u8_reg.w, debugger.u8_reg.y, debugger.u8_reg.w * 2, debugger.u8_reg.h};

  // pc register
  SDL_RenderDrawRect(debugger.render, &u16_reg);

  u16_reg.y += u16_reg.h;

  // sp register
  SDL_RenderDrawRect(debugger.render, &u16_reg);

  u16_reg.y += u16_reg.h;

  // I register
  SDL_RenderDrawRect(debugger.render, &u16_reg);

  // remaining special u8 registers
  // delay timer
  debugger.u8_reg.y += debugger.u8_reg.h;
  SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);

  // sound timer
  debugger.u8_reg.y += debugger.u8_reg.h;
  SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);
}

// draws current state of all components in debugger
void render_debugger(Debugger& debugger) {
  fill_background(debugger);
  draw_registers(debugger);
  draw_instructions(debugger);
  draw_keys(debugger);
  SDL_RenderPresent(debugger.render);
}

void setup_fonts(Debugger& debugger) {
  debugger.font = TTF_OpenFont("./cascadia-code/Cascadia.ttf", 24);
}

void init_debugger(Debugger& debugger) {
  // Initialize Font library
  TTF_Init();
  
  // Create the SDL window
  debugger.window = SDL_CreateWindow("State", debugger.x, debugger.y, debugger.width, debugger.height, 0);

  // Create the SDL renderer
  debugger.render = SDL_CreateRenderer(debugger.window, -1, SDL_RENDERER_ACCELERATED);
  
  setup_fonts(debugger);
  render_debugger(debugger);  
}