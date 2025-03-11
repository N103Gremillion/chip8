#include "debugger.hpp"
#include "chip8.hpp"
#include <iostream>


#define FONT_WHITE 255, 255, 255, 255
#define FONT_BLACK 0, 0, 0, 0

void fill_background(Debugger& debugger) {
  SDL_SetRenderDrawColor(debugger.render, FONT_BLACK);
  SDL_RenderClear(debugger.render);
  SDL_SetRenderDrawColor(debugger.render, FONT_WHITE);
}

void draw_instructions(Debugger& debugger, Chip8& chip) {
  // reset location of instruction to correct starting value
  debugger.instruction.y = 0;
  u16 pc = chip.regs->pc;

  for (int i = 0; i < debugger.num_of_instruction; i++) {
    u16 instruction = (chip.ram[pc] << 8) | chip.ram[pc + 1];
    string instruction_string = "Instruction: " + get_u16hex_string(instruction);
    SDL_Surface* text_surface = TTF_RenderText_Solid(debugger.font, instruction_string.c_str(), debugger.text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface);
    SDL_RenderDrawRect(debugger.render, &debugger.instruction);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &debugger.instruction);
    debugger.instruction.y += debugger.instruction.h;
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    pc += 2;
  }
}

void draw_keys(Debugger& debugger) {
  // reset location of key to correct starting value
  debugger.key.x = 200;
  debugger.key.y = 0;
  SDL_Rect text_rect = {200, 0, debugger.key.w / 2, debugger.key.h / 2};

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
    SDL_Surface* text_surface;
    int keycode = get_keycode_from_key_string(debugger.keys[i]);
    if (key_state[keycode]){
      text_surface = TTF_RenderText_Solid(debugger.font, get_key(keycode).c_str(), debugger.green);
    }else {
      text_surface = TTF_RenderText_Solid(debugger.font, get_key(keycode).c_str(), debugger.text_color);
    }
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface); 
    SDL_RenderDrawRect(debugger.render, &debugger.key);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &text_rect);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }
}

void draw_registers(Debugger& debugger, Registers* registers) {
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
    string str = get_u8reg_string(i, *(registers));
    SDL_Surface* text_surface = TTF_RenderText_Solid(debugger.font, str.c_str(), debugger.text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(debugger.render, text_surface); 
    SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);
    SDL_RenderCopy(debugger.render, text_texture, NULL, &debugger.u8_reg);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }
  // render the remaning specific registers
  SDL_Rect u16_reg = {debugger.u8_reg.x + debugger.u8_reg.w, debugger.u8_reg.y, debugger.u8_reg.w * 2, debugger.u8_reg.h};

  // pc register
  string pc = "PC: " + get_u16hex_string(registers->pc);
  SDL_Surface* pc_text = TTF_RenderText_Solid(debugger.font, pc.c_str(), debugger.text_color);
  SDL_Texture* pc_texture = SDL_CreateTextureFromSurface(debugger.render, pc_text);
  SDL_RenderDrawRect(debugger.render, &u16_reg);
  SDL_RenderCopy(debugger.render, pc_texture, NULL, &u16_reg);
  SDL_FreeSurface(pc_text);
  SDL_DestroyTexture(pc_texture);

  u16_reg.y += u16_reg.h;

  // sp register
  string sp = "SP: " + get_u16hex_string(registers->sp);
  SDL_Surface* sp_surface = TTF_RenderText_Solid(debugger.font, sp.c_str(), debugger.text_color);
  SDL_Texture* sp_texture = SDL_CreateTextureFromSurface(debugger.render, sp_surface);
  SDL_RenderDrawRect(debugger.render, &u16_reg);
  SDL_RenderCopy(debugger.render, sp_texture, NULL, &u16_reg);
  SDL_FreeSurface(sp_surface);
  SDL_DestroyTexture(sp_texture);

  u16_reg.y += u16_reg.h;

  // I register
  string I = "I: " + get_u16hex_string(registers->I);
  SDL_Surface* I_surface = TTF_RenderText_Solid(debugger.font, I.c_str(), debugger.text_color);
  SDL_Texture* I_texture = SDL_CreateTextureFromSurface(debugger.render, I_surface);
  SDL_RenderDrawRect(debugger.render, &u16_reg);
  SDL_RenderCopy(debugger.render, I_texture, NULL, &u16_reg);
  SDL_FreeSurface(I_surface);
  SDL_DestroyTexture(I_texture);

  // remaining special u8 registers
  // delay timer
  string dt = "DT: " + get_u8hex_string(registers->delay_timer);
  SDL_Surface* DT_surface = TTF_RenderText_Solid(debugger.font, dt.c_str(), debugger.text_color);
  SDL_Texture* DT_texture = SDL_CreateTextureFromSurface(debugger.render, DT_surface);
  debugger.u8_reg.y += debugger.u8_reg.h;
  SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);
  SDL_RenderCopy(debugger.render, DT_texture, NULL, &debugger.u8_reg);
  SDL_FreeSurface(DT_surface);
  SDL_DestroyTexture(DT_texture);

  // sound timer
  string st = "PC: " + get_u8hex_string(registers->sound_timer);
  SDL_Surface* ST_surface = TTF_RenderText_Solid(debugger.font, st.c_str(), debugger.text_color);
  SDL_Texture* ST_texture = SDL_CreateTextureFromSurface(debugger.render, ST_surface);
  debugger.u8_reg.y += debugger.u8_reg.h;
  SDL_RenderDrawRect(debugger.render, &debugger.u8_reg);
  SDL_RenderCopy(debugger.render, ST_texture, NULL, &debugger.u8_reg);
  SDL_FreeSurface(ST_surface);
  SDL_DestroyTexture(ST_texture);
}

// draws current state of all components in debugger
void render_debugger(Debugger& debugger, Chip8& chip) {
  fill_background(debugger);
  draw_registers(debugger, chip.regs);
  draw_instructions(debugger, chip);
  draw_keys(debugger);
  SDL_RenderPresent(debugger.render);
}

void setup_fonts(Debugger& debugger) {
  debugger.font = TTF_OpenFont("./cascadia-code/Cascadia.ttf", 24);
}

void init_debugger(Debugger& debugger, Chip8& chip) {
  // Initialize Font library
  TTF_Init();
  
  // Create the SDL window
  debugger.window = SDL_CreateWindow("State", debugger.x, debugger.y, debugger.width, debugger.height, 0);

  // Create the SDL renderer
  debugger.render = SDL_CreateRenderer(debugger.window, -1, SDL_RENDERER_ACCELERATED);
  setup_fonts(debugger);
  render_debugger(debugger, chip);  
}