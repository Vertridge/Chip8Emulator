#include <Emulator/Emulator.h>
#include <Instructions/Disassembler.h>
#include <Util/Binary.h>

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Missing input file" << std::endl;
    return 1;
  }

  emulator::Emulator emulator;
  if (!emulator.LoadGame(argv[1])) {
    return 1;
  }

  emulator.Run(true);

  return 0;
}
