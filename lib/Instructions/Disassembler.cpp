#include "Instructions/Disassembler.h"

#include <algorithm>
#include <iostream>
#include <sstream>

namespace {}

const InstructionDef &Disassembler::GetInstructionDef(std::uint16_t data) {
  auto res = std::find_if(
      InstructionDefinitions.begin(), InstructionDefinitions.end(),
      [data](const InstructionDef &def) { return def.ContainsOpcode(data); });
  if (res == InstructionDefinitions.end()) {
    std::cerr << "Could not find instruction for the data 0x" << std::hex
              << static_cast<int>(data) << std::endl;
    return InstructionDefinitions[0];
  }
  return *res;
}

std::string
Disassembler::DisassembleToString(const std::vector<std::uint16_t> &input) {
  std::stringstream sstream;
  for (auto &c : input) {
    auto &def = GetInstructionDef(c);
    sstream << def.GetNemonic() << "\n";
  }

  return sstream.str();
}

std::vector<Instruction *>
Disassembler::Disassemble(const std::vector<std::uint16_t> &input) {
  std::vector<Instruction *> result;
  result.reserve(input.size());
  for (auto &c : input) {
    auto &def = GetInstructionDef(c);
    result.push_back(CreateInstruction(def.GetOpcode(), c));
  }
  return result;
}
