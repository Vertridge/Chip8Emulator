#include "Emulator.h"

#include <Instructions/Disassembler.h>
#include <Util/Binary.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>

std::vector<Instruction *> ReadInput(const std::string &inputFile) {
  std::ifstream is(inputFile, std::ios::binary);
  if (!is) {
    std::cerr << "Failed to open file: " << inputFile << std::endl;
    return {};
  }

  std::vector<std::uint16_t> inputBuff;
  while (is) {
    std::uint16_t data;
    is.read((char *)&data, sizeof(std::uint16_t));
    util::SwapBinary(data);
    inputBuff.push_back(data);
  }

  return Disassembler::Disassemble(inputBuff);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Missing input file" << std::endl;
    return 1;
  }

  auto instructions = ReadInput(argv[1]);

  emulator::Emulator emulator(instructions);
  emulator.Run();

  return 0;
}
