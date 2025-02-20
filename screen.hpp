#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <stdlib.h>
#include <cstdint>
#include <SDL2/SDL.h>

#define BLACK 0x00000000
#define WHITE 0xFFFFFFFF
#define TOTAL_PIXELS (64 * 32)
#define PIXELS_PER_ROW 64
#define PIXELS_PER_COLUMN 32

using u32 = std::uint32_t;

struct Screen;

void init_screen(Screen& screen);
void update_screen(Screen& screen);
void free_screen(Screen& screen);


typedef struct Screen {

  int x = SDL_WINDOWPOS_CENTERED;
  int y = SDL_WINDOWPOS_CENTERED;
  int width = 1280;
  int height = 640;
  int pixel_width = 20;
  int pixel_height = 20;

  // screen (represented by 64*32 pixel screen
  SDL_Window* window = nullptr;
  SDL_Renderer* render = nullptr;
  SDL_Texture* texture = nullptr;
  u32* pixels = nullptr;

  Screen() {
    pixels = (u32*) malloc(sizeof(u32) * TOTAL_PIXELS);
    
    // set each pixel to black to start
    for (int i = 0; i < TOTAL_PIXELS; i++) {
      pixels[i] = BLACK;
    }
  }

} Screen;


#endif 