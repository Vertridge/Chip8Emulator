#pragma once

#include "Instruction.h"

#include <string>

namespace Instructions {

std::string ToString(Opcode opcode);

Instruction *CreateInstruction(std::uint16_t address, Opcode opcode,
                               std::uint16_t data);

} // namespace Instructions
