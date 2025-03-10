#ifndef KEY_MAP_HPP
#define KEY_MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;
using u8 = uint8_t;

extern map<string, bool> key_state;

void handle_key_change(SDL_Keycode key_pressed, bool state);
void handle_key_down(SDL_Keycode key_pressed);
void handle_key_up(SDL_Keycode key_pressed);
string get_key_from_u8(u8 value);
void print_key_state();

#endif