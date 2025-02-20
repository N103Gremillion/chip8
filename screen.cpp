#include "screen.hpp"
#include <iostream>

void init_screen(Screen& screen) {
  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  
  // Create the SDL window
  screen.window = SDL_CreateWindow("Chip8 Emulator", screen.x, screen.y, screen.width, screen.height, 0);

  // Create the SDL renderer
  screen.render = SDL_CreateRenderer(screen.window, -1, SDL_RENDERER_ACCELERATED);

  // Create the SDL texture (64x32 resolution for Chip8 screen)
  screen.texture = SDL_CreateTexture(screen.render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, PIXELS_PER_ROW, PIXELS_PER_COLUMN);
}

void update_screen(Screen& screen) {
  SDL_UpdateTexture(screen.texture, NULL, screen.pixels, PIXELS_PER_ROW * sizeof(u32));
  SDL_RenderClear(screen.render);
  SDL_RenderCopy(screen.render, screen.texture, NULL, NULL);
  SDL_RenderPresent(screen.render);
}

void free_screen(Screen& screen) {
  SDL_DestroyTexture(screen.texture);
  SDL_DestroyRenderer(screen.render);
  SDL_DestroyWindow(screen.window);
  free(screen.pixels);
  SDL_Quit();
}