#include "Instructions/InstructionDef.h"

namespace Instructions {

InstructionDef::InstructionDef(std::uint16_t opcodeNum,
                               Instructions::Opcode opcode,
                               std::uint16_t immidiates,
                               std::array<std::uint16_t, 4> masks)
    : mOpcodeNum(opcodeNum), mOpcode(opcode), mImmidiates(immidiates),
      mMasks(masks) {}

bool InstructionDef::ContainsOpcode(std::uint16_t data) const {
  auto op = data & mMasks[0];
  return op == mOpcodeNum;
}

} // namespace Instructions
