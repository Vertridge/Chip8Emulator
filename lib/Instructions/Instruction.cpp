#include "Instructions/InstructionUtil.h"
#include <Instructions/Instruction.h>
#include <ios>

namespace Instructions {

Instruction::Instruction(Opcode opcode, std::uint8_t address,
                         std::uint16_t data)
    : mAddress(address), mData(data), mOpcode(opcode) {}

void Instruction::Dump(std::ostream &os) {
  os << "0x" << std::hex << (std::uint16_t)mAddress << " " << ToString(mOpcode);
}

void Instruction::Execute() {}

SysInstruction::SysInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SYS, address, data) {
  const std::uint16_t mask = 0x0FFF;
  mExecAddr = data & mask;
}

void SysInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " 0x" << std::hex << mExecAddr;
}

void SysInstruction::Execute() {}

} // namespace Instructions
