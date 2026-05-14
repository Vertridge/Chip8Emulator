#pragma once

#include "Instructions/Instruction.h"
#include "Instructions/InstructionDef.h"

#include <string>
#include <vector>

namespace Disassembler {

const Instructions::InstructionDef &GetInstructionDef(std::uint16_t data);
std::string DisassembleToString(const std::vector<std::uint16_t> &input);

std::vector<Instructions::Instruction *>
Disassemble(const std::vector<std::uint16_t> &input);

Instructions::Instruction *Disassemble(std::uint16_t input,
                                       std::uint16_t address);

} // namespace Disassembler
