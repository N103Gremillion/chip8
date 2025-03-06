#include "key_map.hpp"

map<string, bool> key_state = {
  {"1", false},
  {"2", false},
  {"3", false},
  {"4", false},
  {"Q", false},
  {"W", false},
  {"E", false},
  {"R", false},
  {"A", false},
  {"S", false},
  {"D", false},
  {"F", false},
  {"Z", false},
  {"X", false},
  {"C", false},
  {"V", false}
};

void handle_key_down(SDL_Keycode key_pressed) {
  // only handle presses to valid keys 
  switch (key_pressed) {
    case SDLK_1:
      key_state["1"] = true;
      break;
    case SDLK_2:
      key_state["2"] = true;
      break;
    case SDLK_3:
      key_state["3"] = true;
      break;
    case SDLK_4:
      key_state["4"] = true;
      break;
    case SDLK_q:
      key_state["Q"] = true;
      break;
    case SDLK_w:
      key_state["W"] = true;
      break;
    case SDLK_e:
      key_state["E"] = true;
      break;
    case SDLK_r:
      key_state["R"] = true;
      break;
    case SDLK_a:
      key_state["A"] = true;
      break;
    case SDLK_s:
      key_state["S"] = true;
      break;
    case SDLK_d:
      key_state["D"] = true;
      break;
    case SDLK_f:
      key_state["F"] = true;
      break;
    case SDLK_z:
      key_state["Z"] = true;
      break;
    case SDLK_x:
      key_state["X"] = true;
      break;
    case SDLK_c:
      key_state["C"] = true;
      break;
    case SDLK_v:
      key_state["V"] = true;
      break;
  } 
}

void handle_key_up(SDL_Keycode key_pressed) {
  // only handle presses to valid keys
  switch (key_pressed) {
    case SDLK_1:
      key_state["1"] = false;
      break;
    case SDLK_2:
      key_state["2"] = false;
      break;
    case SDLK_3:
      key_state["3"] = false;
      break;
    case SDLK_4:
      key_state["4"] = false;
      break;
    case SDLK_q:
      key_state["Q"] = false;
      break;
    case SDLK_w:
      key_state["W"] = false;
      break;
    case SDLK_e:
      key_state["E"] = false;
      break;
    case SDLK_r:
      key_state["R"] = false;
      break;
    case SDLK_a:
      key_state["A"] = false;
      break;
    case SDLK_s:
      key_state["S"] = false;
      break;
    case SDLK_d:
      key_state["D"] = false;
      break;
    case SDLK_f:
      key_state["F"] = false;
      break;
    case SDLK_z:
      key_state["Z"] = false;
      break;
    case SDLK_x:
      key_state["X"] = false;
      break;
    case SDLK_c:
      key_state["C"] = false;
      break;
    case SDLK_v:
      key_state["V"] = false;
      break;
  }
}