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

}

u16 fetch_intruction(Chip8& chip) {
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

void perform_instruction(u16 instruction) {
  
  // niblets= (4 bits)
  u8 opcode = instruction >> 12; // defines the type of instruction

  switch (opcode) {
    case 0x0:
      switch (instruction) {
        // clear screen
        case 0x00E0:
          printf("clear screen \n");
          break;
        // return from subroutine
        case 0x00EE:
          printf("return \n");
          break;
      }
    case 0x1:
      //jump to the nnn register 
      printf("jump \n");
    case 0x2:
      // call insturciton
      printf("call \n");
    case 0x3:
      // skip next insturction Vx = kk
      printf("check skip \n");
    case 0x4:
      // skip next instuction if Vx != kk
      printf("check skip \n");
    case 0x5: 
      // skip next instuction if Vx = Vy 
      printf("check skip \n");
    case 0x6:
      // put value kk into register Vx
      printf("put in reg \n");
    case 0x7:
      // add kk to the value of register Vx, then store result in Vx
      printf("add to reg and set \n");
    case 0x8:
      u8 finalNib = (instruction & 0xF);
      switch (finalNib) {
        case 0x1:
          // perfoms bitwise OR on the values of Vx and Vy, and stores the result in Vx
          printf("OR Vx and Vy then stor in Vx \n");
        case 0x2:
          // perorms bitwise AND on values in Vx and Vy and stores in Vx
          printf("AND Vx and Vy then store in Vx \n");
        case 0x3:
          // performs bitwise exclusive OR On value in Vx and Vy and stores in Vx
          printf("XOR Vx and Vy then store in Vx \n");
        case 0x4:
          // ADD Vx and Vy values if res is > 8bits (255) VF is set to 1 else 0,
          // only the lowest 8 bits of the result are kept and stored in Vx
          printf("ADD and do some checks \n");
        case 0x5:
          // if Vx > Vy VF is set to 1, else 0. 
          // then Vy is subtracted from Vx, and res is stored in Vx
          printf("Subtract and other stuff \n");
        case 0x6:
          // if LSB(least significant bit) of Vx is 1, then VF is set to 1, else 0. 
          // then Vx is divided by 2
          printf("check LSB and divide Vx by 2 \n");
        case 0x7:
          // if Vy > Vx, then VF is set to 1, else 0. then Vx is subtracted from Vy, and res is in Vx
          printf("check if Vy > Vx then sub Vx from Vy and store in Vx \n");
        case 0xE:
          // if MSB(most sig bit) of Vx is 1, then GVF is set to 1, else 0. Then Vx is multiplied by 2.
          printf("check MSB and the multiply Vx by 2");
      }
    case 0x9:
      // skip next insturction if Vx != Vy
      printf("If Vx != Vy pc += 2 \n");

  }
  
}



