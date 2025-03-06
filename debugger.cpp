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
  debugger.key.x = 210;
  debugger.key.y = 0;
  SDL_Rect text_rect = {210, 0, debugger.key.w, debugger.key.h};
  const char* keys[] = {"1", "2", "3", "4", "Q", "W", "E", "R", "A", "S", "D", "F", "Z", "X", "C", "V"};

  for (int i = 0; i < debugger.num_of_keys; i++) {
    
    if (i % 4 == 0 && i != 0) {
      debugger.key.y += debugger.key.h;
      debugger.key.x = 210;
    } else if (i != 0){
      debugger.key.x += debugger.key.w;
    }
    SDL_Surface* text_surface = TTF_RenderText_Solid(debugger.font, keys[i], debugger.text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface); 
    SDL_RenderDrawRect(debugger.render, &debugger.key);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &debugger.key);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }
}

// draws current state of all components in debugger
void render_debugger(Debugger& debugger) {
  fill_background(debugger);
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