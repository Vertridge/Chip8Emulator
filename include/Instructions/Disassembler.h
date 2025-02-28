#pragma once

#include "Instructions/Instruction.h"
#include "Instructions/InstructionDef.h"

#include <string>
#include <vector>

using namespace Instructions;

namespace Disassembler {

const InstructionDef &GetInstructionDef(std::uint16_t data);
std::string DisassembleToString(const std::vector<std::uint16_t> &input);

std::vector<Instruction *> Disassemble(const std::vector<std::uint16_t> &input);

} // namespace Disassembler
