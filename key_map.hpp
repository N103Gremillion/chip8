#ifndef KEY_MAP_HPP
#define KEY_MAP_HPP

#include <map>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#define KEYCODE_1 49
#define KEYCODE_2 50
#define KEYCODE_3 51
#define KEYCODE_4 52
#define KEYCODE_Q 113
#define KEYCODE_W 119
#define KEYCODE_E 101
#define KEYCODE_R 114
#define KEYCODE_A 97
#define KEYCODE_S 115
#define KEYCODE_D 100
#define KEYCODE_F 102
#define KEYCODE_Z 122
#define KEYCODE_X 120
#define KEYCODE_C 99
#define KEYCODE_V 118

using namespace std;
using u8 = uint8_t;

extern bool key_state[122];

void handle_key_change(SDL_Keycode key_pressed, bool state);
void handle_key_down(SDL_Keycode key_pressed);
void handle_key_up(SDL_Keycode key_pressed);
int get_keycode_from_u8(u8 value);
int get_keycode_from_key_string(string key);
string get_key(int keycode);
void print_key_state();

#endif