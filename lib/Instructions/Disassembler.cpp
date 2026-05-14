#include "Instructions/Disassembler.h"
#include "Instructions/InstructionUtil.h"

#include <CPU/Memory.h>

#include <algorithm>
#include <iostream>
#include <sstream>

namespace Disassembler {

const Instructions::InstructionDef &GetInstructionDef(std::uint16_t data) {
  auto res = std::find_if(Instructions::InstructionDefinitions.begin(),
                          Instructions::InstructionDefinitions.end(),
                          [data](const Instructions::InstructionDef &def) {
                            return def.ContainsOpcode(data);
                          });
  if (res == Instructions::InstructionDefinitions.end()) {
    std::cerr << "Could not find instruction for the data 0x" << std::hex
              << static_cast<int>(data) << std::endl;
    assert(false);
    return Instructions::InstructionDefinitions[0];
  }
  return *res;
}

std::string DisassembleToString(const std::vector<std::uint16_t> &input) {
  std::stringstream sstream;
  std::uint16_t address = instruction_start;
  for (auto &c : input) {
    auto &def = GetInstructionDef(c);
    auto *instruction = CreateInstruction(address, def.GetOpcode(), c);
    instruction->Dump(sstream);
    sstream << "\n";
    delete instruction;
    address += Instructions::instruction_size;
  }

  return sstream.str();
}

Instructions::Instruction *Disassemble(std::uint16_t input,
                                       std::uint16_t address) {
  auto &def = GetInstructionDef(input);
  return CreateInstruction(address, def.GetOpcode(), input);
}

std::vector<Instructions::Instruction *>
Disassemble(const std::vector<std::uint16_t> &input) {
  std::vector<Instructions::Instruction *> result;
  result.reserve(input.size());
  std::uint16_t address = instruction_start;
  for (auto &c : input) {
    auto *ins = Disassemble(c, address);
    result.push_back(ins);
    address += Instructions::instruction_size;
  }
  return result;
}

} // namespace Disassembler
