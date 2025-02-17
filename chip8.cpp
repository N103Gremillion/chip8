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
  
  // niblets
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
      int reg = instruction & 0x0FFF;

  }
  
}



