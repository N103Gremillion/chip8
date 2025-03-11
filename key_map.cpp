#include "key_map.hpp"

bool key_state[122] = {false};

void handle_key_change(SDL_Keycode key_pressed, bool state) {
  if (key_pressed <= 122) {
    key_state[key_pressed] = state;
  }
}

void handle_key_down(SDL_Keycode key_pressed) {
  handle_key_change(key_pressed, true);
}

void handle_key_up(SDL_Keycode key_pressed) {
  handle_key_change(key_pressed, false);
}


int get_keycode_from_u8(u8 value) {
  switch (value) {
      case 0x1: return 49;
      case 0x2: return 50;
      case 0x3: return 51;
      case 0xC: return 52;
      case 0x4: return 113;
      case 0x5: return 119;
      case 0x6: return 101;
      case 0xD: return 114;
      case 0x7: return 97;
      case 0x8: return 115;
      case 0x9: return 100;
      case 0xE: return 102;
      case 0xA: return 122;
      case 0x0: return 120;
      case 0xB: return 99;
      case 0xF: return 118;
      default: return -1;
  }
}

int get_keycode_from_key_string(string key) {
  if (key == "1") {
    return KEYCODE_1;
  } else if (key == "2") {
    return KEYCODE_2;
  } else if (key == "3") {
    return KEYCODE_3;
  } else if (key == "4") {
    return KEYCODE_4;
  } else if (key == "Q") {
    return KEYCODE_Q;
  } else if (key == "W") {
    return KEYCODE_W;
  } else if (key == "E") {
    return KEYCODE_E;
  } else if (key == "R") {
    return KEYCODE_R;
  } else if (key == "A") {
    return KEYCODE_A;
  } else if (key == "S") {
    return KEYCODE_S;
  } else if (key == "D") {
    return KEYCODE_D;
  } else if (key == "F") {
    return KEYCODE_F;
  } else if (key == "Z") {
    return KEYCODE_Z;
  } else if (key == "X") {
    return KEYCODE_X;
  } else if (key == "C") {
    return KEYCODE_C;
  } else if (key == "V") {
    return KEYCODE_V;
  } else {
    return -1;
  }
}

string get_key(int keycode) {
  switch (keycode) {
    case KEYCODE_1: return "1";
    case KEYCODE_2: return "2";
    case KEYCODE_3: return "3";
    case KEYCODE_4: return "4";
    case KEYCODE_Q: return "Q";
    case KEYCODE_W: return "W";
    case KEYCODE_E: return "E";
    case KEYCODE_R: return "R";
    case KEYCODE_A: return "A";
    case KEYCODE_S: return "S";
    case KEYCODE_D: return "D";
    case KEYCODE_F: return "F";
    case KEYCODE_Z: return "Z";
    case KEYCODE_X: return "X";
    case KEYCODE_C: return "C";
    case KEYCODE_V: return "V";
    default: return "unkown key";
  }
}

void print_key_state() {
  // Printing key-value pairs
  for (int i = 0; i < size(key_state); i++) {
    cout << key_state[i] << endl;
  }
}