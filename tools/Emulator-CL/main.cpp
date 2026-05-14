#include <Emulator/Emulator.h>
#include <Instructions/Disassembler.h>
#include <Util/Binary.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Missing input file" << std::endl;
    return 1;
  }

  emulator::Emulator emulator;
  if (!emulator.LoadGame(argv[1])) {
    return 1;
  }

  emulator.Run();

  return 0;
}
