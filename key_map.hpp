#ifndef KEY_MAP_HPP
#define KEY_MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

extern map<string, bool> key_state;

void handle_key_down(SDL_Keycode key_pressed);
void handle_key_up(SDL_Keycode key_pressed);

#endif