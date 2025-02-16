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

void printMemory(Chip8& chip) {
  for (int i = 0; i < RAM_SIZE; ++i) {
    cout << "0x" << hex << (int)(unsigned char)chip.ram[i] << " ";
  }
  cout << std::dec << std::endl;
}

void printStack(Chip8& chip) {

}