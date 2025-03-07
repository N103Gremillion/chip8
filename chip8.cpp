#include "chip8.hpp"
#include <fstream>
#include <vector>


void load_rom(const std::string& fileName, Chip8& chip) {
  // Open file in binary mode
  ifstream romFile(fileName, ios::binary);

  if (!romFile) {
    cerr << "Error: could not open ROM file " << fileName << endl;
    return;  
  }

  // Get the size of the file
  romFile.seekg(0, ios::end);
  streampos size = romFile.tellg();
  romFile.seekg(0, ios::beg);

  // Allocate memory for the buffer using a vector for automatic memory management
  vector<char> buffer(size);

  // Read the contents of the file into the buffer
  romFile.read(buffer.data(), size);
  
  if (!romFile) {
    std::cerr << "Error: failed to read the entire ROM file" << std::endl;
    return;
  }

  romFile.close();

  // Copy the ROM data into chip's RAM starting at ROM_START
  for (std::size_t i = 0; i < size; ++i) {
    chip.ram[ROM_START + i] = buffer[i];
  }
}

// HELPERS FUNCTIONS
void printHex(u16 instruction) {
  cout<< hex << uppercase << static_cast<int>(instruction) << endl;
}

void printStack(Chip8& chip) {
  for (int i = 0; i < 16; i++) {
    cout<< "|" << chip.stack[i] << "|" << endl;
  }
}

// MAIN FUNCTIONS
void run(Chip8& chip) {

  bool running = true;
  SDL_Event event;
  char user_input;

  while(running) {
    // Handle use input
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        SDL_Keycode key_pressed = event.key.keysym.sym;
        handle_key_down(key_pressed);
      } else if (event.type == SDL_KEYUP) {
        SDL_Keycode key_pressed = event.key.keysym.sym;
        handle_key_up(key_pressed);
      }
    }

    // show state before running an instrution
    render_debugger(chip.debugger, chip);
    // cout << "Press any key to run next instruction..." << endl;
    // cin.get(user_input);

    // execute an instruction
    u16 instruction = fetch_instruction(chip);
    perform_instruction(instruction, chip);

    // draw pixels / update screen
    update_screen(chip.screen);
  }
}

int get_random_num(int min, int max) {
  static random_device random;
  static mt19937 gen(random());
  uniform_int_distribution<int> dist(min, max);

  return dist(gen);
}

u16 fetch_instruction(Chip8& chip) {
  u16 pc = chip.regs->pc;
  u16 instruction = (chip.ram[pc] << 8) | chip.ram[pc + 1];
  chip.regs->pc+=2;
  return instruction;  
}

void printMemory(Chip8& chip) {
  for (int i = 0; i < RAM_SIZE; ++i) {
    cout << "0x" << hex << (int)(unsigned char)chip.ram[i] << " ";
  }
  cout << std::dec << std::endl;
}

void free_chip(Chip8& chip) {
  // free everything from the stack
  free(chip.ram);
  delete chip.regs;
  free(chip.stack);
  free_screen(chip.screen);
}

  
void perform_instruction(u16 instruction, Chip8& chip) {
  // niblets = (4 bits)
  u8 opcode = instruction >> 12; // defines the type of instruction

  switch (opcode) {

    case 0x0:
      switch (instruction) {

        // clear screen
        case 0x00E0: 
          clear_screen(chip.screen);
          break;

        // return from subroutine sets pc to address at top of stck then sp --
        case 0x00EE:
          chip.regs->sp--;
          chip.regs->pc = chip.stack[chip.regs->sp];
          // chip.stack[chip.regs->sp] = chip.regs->pc;
          break;
      }

    // jump to the nnn register
    case 0x1: {
      u16 nnn = (instruction & 0xFFF);
      chip.regs->pc = nnn;
      break;
    }

    // call instruction
    case 0x2: {
      if (chip.regs->sp >= 16 - 1) {
        std::cerr<<"Stack overflow"<<std::endl;
      } else {
        chip.regs->sp++;
        chip.stack[chip.regs->sp] = chip.regs->pc;
        chip.regs->pc = (instruction & 0xFFF);
      }
      break;
    }

    // skip next instruction Vx = kk
    case 0x3: {
      u8 kk = (instruction & 0xFF);
      int reg_num = (int) ((instruction >> 8) & 0xF);
      if (kk == get_value_in_Vreg(reg_num, *(chip.regs))) {
        chip.regs->pc += 2;
      }
      break;
    }

    // skip next instruction if Vx != kk
    case 0x4: {
      u8 kk = (instruction & 0xFF);
      int reg_num = (int) ((instruction >> 8) & 0xF);
      if (kk != get_value_in_Vreg(reg_num, *(chip.regs))) {
        chip.regs->pc += 2;
      }
      break;
    }

    // skip next instruction if Vx = Vy
    case 0x5: {
      int x_reg_num = ((instruction >> 8) & 0xF);
      int y_reg_num = ((instruction >> 4) & 0xF);
      if (get_value_in_Vreg(x_reg_num, *(chip.regs)) == get_value_in_Vreg(y_reg_num, *(chip.regs))) {
        chip.regs->pc += 2;
      }
      printf("check skip \n");
      break;
    }

    // put value kk into register Vx
    case 0x6: {
      u8 kk = (instruction & 0xFF);
      int x = (int) ((instruction >> 8) & 0xF);
      put_value_in_Vreg(x, kk, *(chip.regs));
      break;
    }

    // add kk to the value of register Vx, then store result in Vx
    case 0x7: {
      u8 kk = (instruction & 0xFF);
      int x_reg_num = ((instruction >> 8) & 0xF);
      u8 new_reg_val = get_value_in_Vreg(x_reg_num, *(chip.regs)) + kk;
      put_value_in_Vreg(x_reg_num, new_reg_val, *(chip.regs));
      break;
    }

    case 0x8: {
      u8 finalNib = (instruction & 0xF);
      int x_reg_num = ((instruction >> 8) & 0xF);
      int y_reg_num = ((instruction >> 4) & 0xF);
      u8 Vy = get_value_in_Vreg(y_reg_num, *(chip.regs));
      u8 Vx = get_value_in_Vreg(x_reg_num, *(chip.regs));

      switch (finalNib) {
        
        // store value in Vy in Vx register
        case 0x0:
          put_value_in_Vreg(x_reg_num, Vy, *(chip.regs));
          break;

        // performs bitwise OR on the values of Vx and Vy, and stores the result in Vx   
        case 0x1: 
          put_value_in_Vreg(x_reg_num, (Vx | Vy), *(chip.regs));
          break;

        // performs bitwise AND on values in Vx and Vy and stores in Vx
        case 0x2:
          put_value_in_Vreg(x_reg_num, (Vx & Vy), *(chip.regs));
          break;

        // performs bitwise exclusive OR on values in Vx and Vy and stores in Vx
        case 0x3:
          put_value_in_Vreg(x_reg_num, (Vx ^ Vy), *(chip.regs));
          break;

        // ADD Vx and Vy values; if result > 8 bits, VF is set to 1, else 0
        case 0x4: {
          u16 sum = (u16)Vx +(u16)Vy;
          u8 result = (u8)sum;
          u8 carry = (sum > 255) ? 1 : 0;
          put_value_in_Vreg(x_reg_num, result, *(chip.regs));
          put_value_in_Vreg(0xF, carry, *(chip.regs));
          break;
        }

        // if Vx > Vy, VF is set to 1, else 0
        case 0x5: {
          u8 carry = (Vx > Vy) ? 1 : 0;
          put_value_in_Vreg(x_reg_num, (Vx - Vy), *(chip.regs));
          put_value_in_Vreg(0xF, carry, *(chip.regs));
          break;
        }

        // if LSB of Vx is 1, then VF is set to 1, else 0. Then Vx is divided by 2
        case 0x6: {
          u8 lsb = (Vx & 0x1);
          put_value_in_Vreg(0xF, lsb, *(chip.regs));
          put_value_in_Vreg(x_reg_num, (Vx >> 1), *(chip.regs));
          break;
        }

        // if Vy > Vx, VF is set to 1, else 0. Then Vx is subtracted from Vy
        case 0x7: {
          u8 carry = (Vy > Vx) ? 1 : 0;
          put_value_in_Vreg(x_reg_num, (Vy - Vx), *(chip.regs));
          put_value_in_Vreg(0xF, carry, *(chip.regs));
          break;
        }

        // if MSB of Vx is 1, VF is set to 1, else 0. Then Vx is multiplied by 2
        case 0xE: {
          u8 msb = (Vx >> 7);
          put_value_in_Vreg(x_reg_num, (Vx << 1), *(chip.regs));
          put_value_in_Vreg(0xF, msb, *(chip.regs));
          break;
        }
      }
    }
      break;

    // skip next instruction if Vx != Vy
    case 0x9:{
      u8 x_reg_num = (instruction >> 8) & 0xF;
      u8 y_reg_num = (instruction >> 4) & 0xF;
      if (get_value_in_Vreg(x_reg_num, *(chip.regs)) != get_value_in_Vreg(y_reg_num, *(chip.regs))){
        chip.regs->pc += 2;
      }
      break;
    }
    
    // value of register I is set to nnn
    case 0xA: {
      u16 nnn = (instruction & 0xFFF);
      chip.regs->I = nnn;
      break;
    }

    // Jump to location nnn + V0
    case 0xB:{
      u16 nnn = (instruction & 0xFFF);
      chip.regs->pc = (nnn + get_value_in_Vreg(0, *(chip.regs)));
      break;
    }

    // generate random num (0 - 255), AND with value kk, store in Vx
    case 0xC:{
      u8 kk = (instruction & 0xFF);
      u8 x_reg_num = ((instruction >> 8) & 0xF);
      u8 random_byte = get_random_num(0, 255);
      put_value_in_Vreg(x_reg_num, (kk & random_byte), *(chip.regs));
      break;
    }

    // display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
    case 0xD: {
      int x_reg_num = (int) ((instruction >> 8) & 0xF);
      int y_reg_num = (int) ((instruction >> 4) & 0xF);
      int n = (int) (instruction & 0xF);
      int x = get_value_in_Vreg(x_reg_num, *(chip.regs)) & 63; // % 64 helps it wrap 
      int y = get_value_in_Vreg(y_reg_num, *(chip.regs)) & 31; // %32 helps it wrap
      u16 memory_location = chip.regs->I;

      put_value_in_Vreg(15, 0x00, *(chip.regs));

      while (n > 0) {
        u8 cur_byte = chip.ram[memory_location];
        bool set_Vf_to_1 = draw_pixel_row(x, y, chip.screen, cur_byte);
        if (set_Vf_to_1) {
          put_value_in_Vreg(15, 1, *(chip.regs)); // if collision occurs set VF to 1
        }
        // Update coordinates for the next row of pixels
        y++;
        memory_location++;
        n--;
        // stop when you hit the bottom of screen
        if (y >= 32) {
          break;
        }
      } 
      break;
    }

    case 0xE: {
      u8 last8 = (instruction & 0xFF);
      int x_reg_num = ((instruction >> 8) & 0xF);
      u8 Vx = get_value_in_Vreg(x_reg_num, *(chip.regs));
      string key = get_key_from_u8(Vx);

      switch (last8) {
        // skip next instruction if key with value of Vx is pressed
        case 0x9E: {
          if (key_state[key]) {
            chip.regs->pc += 2;
          }
          break;
        }
         // skip next instruction if key with value of Vx is not pressed
        case 0xA1: {
          if (!key_state[key]) {
            chip.regs->pc += 2;
          }
          break;
        }
        default:
          break;
      }
      break;
    }

    case 0xF: {
      u8 last8 = (instruction & 0xFF);
      switch (last8) {
        case 0x07:
          // set Vx = delay_timer value
          printf("Vx = delay_timer\n");
          break;
        case 0x0A:
          // Wait for key press, store value in Vx
          printf("wait for key press and store in Vx \n");
          break;
        case 0x15:
          // set delay timer to Vx
          printf("delay_timer = Vx \n");
          break;
        case 0x18:
          // set sound timer = Vx
          printf("sound_timer = Vx \n");
          break;
        case 0x1E:
          // set I = I + Vx
          printf("I = I + Vx \n");
          break;
        case 0x29:
          // value of I is set to location of the hex sprite corresponding to the value of Vx
          printf("I set to sprite hex in Vx \n");
          break;
        case 0x33:
          // take decimal value of Vx, place hundreds, tens, and ones digit in memory at I, I+1, I+2
          printf("Some decimal val in Vx are placed in I register locations\n");
          break;
        case 0x55:
          // copies values of V0 through Vx into memory, starting at the address in I
          printf("value of V0 is copied into memory through Vx starting at the address in I \n");
          break;
        case 0x65:
          // read values from memory starting at I into registers V0 through Vx
          printf("copy values from memory starting at location I into V0 through Vx\n");
          break;
        }
      }
    break;
  }
}





