#include <Instructions/Disassembler.h>

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
    inputBuff.push_back(data);
  }
  // std::istream_iterator<std::uint16_t> start(is), end;
  // std::vector<std::uint16_t> inputBuff(start, end);

  std::cout << "Disassembling: " << argv[1] << " " << inputBuff.size()
            << " instructions" << std::endl;

  auto disassembled = Disassembler::DisassembleToString(inputBuff);

  std::cout << disassembled << std::endl;

  return 0;
}
