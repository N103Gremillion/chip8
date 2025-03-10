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

void handle_key_change(SDL_Keycode key_pressed, bool state) {
  switch (key_pressed) {
    case SDLK_1: key_state["1"] = state; break;
    case SDLK_2: key_state["2"] = state; break;
    case SDLK_3: key_state["3"] = state; break;
    case SDLK_4: key_state["4"] = state; break;
    case SDLK_q: key_state["Q"] = state; break;
    case SDLK_w: key_state["W"] = state; break;
    case SDLK_e: key_state["E"] = state; break;
    case SDLK_r: key_state["R"] = state; break;
    case SDLK_a: key_state["A"] = state; break;
    case SDLK_s: key_state["S"] = state; break;
    case SDLK_d: key_state["D"] = state; break;
    case SDLK_f: key_state["F"] = state; break;
    case SDLK_z: key_state["Z"] = state; break;
    case SDLK_x: key_state["X"] = state; break;
    case SDLK_c: key_state["C"] = state; break;
    case SDLK_v: key_state["V"] = state; break;
    default: break;
  }
}

void handle_key_down(SDL_Keycode key_pressed) {
  handle_key_change(key_pressed, true);
}

void handle_key_up(SDL_Keycode key_pressed) {
  handle_key_change(key_pressed, false);
}


string get_key_from_u8(u8 value) {
  switch (value) {
      case 0x1: return "1";
      case 0x2: return "2";
      case 0x3: return "3";
      case 0xC: return "4";
      case 0x4: return "Q";
      case 0x5: return "W";
      case 0x6: return "E";
      case 0xD: return "R";
      case 0x7: return "A";
      case 0x8: return "S";
      case 0x9: return "D";
      case 0xE: return "F";
      case 0xA: return "Z";
      case 0x0: return "X";
      case 0xB: return "C";
      case 0xF: return "V";
      default: return "Unknown";
  }
}

void print_key_state() {
  // Printing key-value pairs
  for (const auto& pair : key_state) {
      std::cout << "Key: " << pair.first << ", Value: " << std::boolalpha << pair.second << '\n';
  }
}