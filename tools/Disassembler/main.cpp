#include <Instructions/Disassembler.h>

#include <Util/Binary.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>

int main(int argc, char *argv[]) {
  std::cout << "Disassembler Begin: " << argc << " " << argv[0] << std::endl;

  if (argc < 2) {
    std::cerr << "Missing input file" << std::endl;
    return 1;
  }

  std::ifstream is(argv[1], std::ios::binary);
  if (!is) {
    std::cerr << "Failed to open file: " << argv[1] << std::endl;
    return 1;
  }
  std::vector<std::uint16_t> inputBuff;
  while (is) {
    std::uint16_t data;
    is.read((char *)&data, sizeof(std::uint16_t));
    util::SwapBinary(data);
    inputBuff.push_back(data);
  }

  std::cout << "Disassembling: " << argv[1] << " " << inputBuff.size()
            << " instructions" << std::endl;

  auto disassembled = Disassembler::DisassembleToString(inputBuff);

  std::cout << disassembled << std::endl;

  if (argc == 3) {
    std::ofstream output(argv[2]);
    output << disassembled;
  }

  return 0;
}
