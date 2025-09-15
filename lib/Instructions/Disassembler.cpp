#include "Instructions/Disassembler.h"
#include "Instructions/InstructionUtil.h"

#include <CPU/Memory.h>

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
    assert(false);
    return InstructionDefinitions[0];
  }
  return *res;
}

std::string
Disassembler::DisassembleToString(const std::vector<std::uint16_t> &input) {
  std::stringstream sstream;
  std::uint16_t address = memory_start;
  for (auto &c : input) {
    auto &def = GetInstructionDef(c);
    auto *instruction = CreateInstruction(address, def.GetOpcode(), c);
    instruction->Dump(sstream);
    sstream << "\n";
    delete instruction;
    address += 0x2;
  }

  return sstream.str();
}

std::vector<Instruction *>
Disassembler::Disassemble(const std::vector<std::uint16_t> &input) {
  std::vector<Instruction *> result;
  result.reserve(input.size());
  std::uint16_t address = 0;
  for (auto &c : input) {
    auto &def = GetInstructionDef(c);
    result.push_back(CreateInstruction(address, def.GetOpcode(), c));
    address += 0x2;
  }
  return result;
}
