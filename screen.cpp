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

bool draw_pixel_row(int x, int y, Screen& screen, u8 byte) {
  x -=1;
  y -= 1;
  int cur_bit_index = 0;
  bool vf_to_1 = false;

  while (cur_bit_index < 8) {

    int cur_bit = (int) ((byte >> (7 - cur_bit_index)) & 0x1);
    int screen_index = y * PIXELS_PER_ROW + x;
    int screen_bit = (int) (screen.pixels[screen_index] & 0x1);
    std::cout << "x: " << x << ", y: " << y << std::endl;
    if (cur_bit ^ screen_bit) {
      if (cur_bit == 1) {
        screen.pixels[screen_index] = WHITE;
      }
    } else {

      if (cur_bit == 1 && screen_bit == 1) {
        screen.pixels[screen_index] = BLACK;
        vf_to_1 = true;
      }

    }

    // move to next pixel
    x++;
    cur_bit_index++;

    if (x >= PIXELS_PER_ROW) {
      break;
    }
  }
  return vf_to_1;
}

void free_screen(Screen& screen) {
  SDL_DestroyTexture(screen.texture);
  SDL_DestroyRenderer(screen.render);
  SDL_DestroyWindow(screen.window);
  free(screen.pixels);
  SDL_Quit();
}