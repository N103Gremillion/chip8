#include "register.hpp"

void put_value_in_Vreg(int regNum, u8 value, Registers& registers) {
    if (regNum > 15 || regNum < 0) {
      return;
    }
    switch (regNum) {
      case 0:
        registers.v0 = value;
        break;
      case 1:
        registers.v1 = value;
        break;
      case 2:
        registers.v2 = value;
        break;
      case 3:
        registers.v3 = value;
        break;
      case 4:
        registers.v4 = value;
        break;
      case 5:
        registers.v5 = value;
        break;
      case 6:
        registers.v6 = value;
        break;
      case 7:
        registers.v7 = value;
        break;
      case 8:
        registers.v8 = value;
        break;
      case 9:
        registers.v9 = value;
        break;
      case 10:
        registers.vA = value;
        break;
      case 11:
        registers.vB = value;
        break;
      case 12:
        registers.vC = value;
        break;
      case 13:
        registers.vD = value;
        break;
      case 14:
        registers.vE = value;
        break;
      case 15:  
        registers.vF = value;
        break;
    }
}

u8 get_value_in_Vreg(int regNum, Registers& registers) {
  if (regNum < 0 || regNum > 15) {
    return -1;
  }
  switch (regNum) {
      case 0:
        return registers.v0;
        break;
      case 1:
        return registers.v1;
        break;
      case 2:
        return registers.v2;
        break;
      case 3:
        return registers.v3;
        break;
      case 4:
        return registers.v4;
        break;
      case 5:
        return registers.v5;
        break;
      case 6:
        return registers.v6;
        break;
      case 7:
        return registers.v7;
        break;
      case 8:
        return registers.v8;
        break;
      case 9:
        return registers.v9;
        break;
      case 10:
        return registers.vA;
        break;
      case 11:
        return registers.vB;
        break;
      case 12:
        return registers.vC;
        break;
      case 13:
        return registers.vD;
        break;
      case 14:
        return registers.vE;
        break;
      case 15:  
        return registers.vF;
        break;
      default:
        return -1;
        break;
  }
}

string get_u8reg_string(int reg_num, Registers& registers) {
  if (reg_num < 0 || reg_num > 15) {
    return "";
  }

  string hex_string = get_u8hex_string(get_value_in_Vreg(reg_num, registers));

  switch (reg_num) {
    case 0:
      return ("V0: " + hex_string);
    case 1:
      return ("V1: " + hex_string);
    case 2:
      return ("V2: " + hex_string);
    case 3:
      return ("V3: " + hex_string);
    case 4:
      return ("V4: " + hex_string);
    case 5:
      return ("V5: " + hex_string);
    case 6:
      return ("V6: " + hex_string);
    case 7:
      return ("V7: " + hex_string);
    case 8:
      return ("V8: " + hex_string);
    case 9:
      return ("V9: " + hex_string);
    case 10:
      return ("VA: " + hex_string);
    case 11:
      return ("VB: " + hex_string);
    case 12:
      return ("VC: " + hex_string);
    case 13:
      return ("VD: " + hex_string);
    case 14:
      return ("VE: " + hex_string);
    case 15:
      return ("VF: " + hex_string);
    default:
      return "";
      break;
  }
}

string get_u8hex_string(u8 value) {
  stringstream hex_val;
  hex_val << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(value);
  return hex_val.str();
}

string get_u16hex_string(u16 value) {
  stringstream hex_val;
  hex_val << uppercase << hex << setw(4) << setfill('0') << static_cast<int>(value);
  return hex_val.str();
}