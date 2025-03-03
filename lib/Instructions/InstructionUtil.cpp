#include "Instructions/InstructionUtil.h"
#include "Instructions/Instruction.h"
#include <cstdint>

namespace Instructions {

std::string ToString(Opcode opcode) {
  switch (opcode) {
  case Opcode::CLS:
    return "CLS";
  case Opcode::RET:
    return "RET";
  case Opcode::SYS:
    return "SYS";
  case Opcode::JP:
    return "JP";
  case Opcode::RND:
    return "RND";
  case Opcode::CALL:
    return "CALL";
  case Opcode::SE:
    return "SE";
  case Opcode::SNE:
    return "SNE";
  case Opcode::LD:
    return "LD";
  case Opcode::ADD:
    return "ADD";
  case Opcode::SUB:
    return "SUB";
  case Opcode::SUBN:
    return "SUBN";
  case Opcode::OR:
    return "OR";
  case Opcode::AND:
    return "AND";
  case Opcode::XOR:
    return "XOR";
  case Opcode::SHR:
    return "SHR";
  case Opcode::SHL:
    return "SHL";
  case Opcode::SKP:
    return "SKP";
  case Opcode::SKNP:
    return "SKNP";
  case Opcode::DRW:
    return "DRAW";
  case Opcode::SCD:
    return "SCD";
  case Opcode::SCR:
    return "SCR";
  case Opcode::SCL:
    return "SCL";
  case Opcode::EXIT:
    return "EXIT";
  case Opcode::LOW:
    return "LOW";
  case Opcode::HIGH:
    return "HIGH";
  }
}

Instruction *CreateInstruction(Opcode opcode, std::uint16_t data) {
  switch (opcode) {
  case Opcode::CLS:
    return new ClsInstruction(0x0, data);
  case Opcode::RET:
    return new RetInstruction(0x0, data);
  case Opcode::SYS:
    return new SysInstruction(0x0, data);
  case Opcode::JP:
    return new JpInstruction(0x0, data);
  case Opcode::RND:
    return new Instruction(opcode, 0x0, data);
  case Opcode::CALL:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SE:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SNE:
    return new Instruction(opcode, 0x0, data);
  case Opcode::LD:
    return new Instruction(opcode, 0x0, data);
  case Opcode::ADD:
    return new AddInstruction(0x0, data);
  case Opcode::SUB:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SUBN:
    return new Instruction(opcode, 0x0, data);
  case Opcode::OR:
    return new Instruction(opcode, 0x0, data);
  case Opcode::AND:
    return new Instruction(opcode, 0x0, data);
  case Opcode::XOR:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SHR:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SHL:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SKP:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SKNP:
    return new Instruction(opcode, 0x0, data);
  case Opcode::DRW:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SCD:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SCR:
    return new Instruction(opcode, 0x0, data);
  case Opcode::SCL:
    return new Instruction(opcode, 0x0, data);
  case Opcode::EXIT:
    return new Instruction(opcode, 0x0, data);
  case Opcode::LOW:
    return new Instruction(opcode, 0x0, data);
  case Opcode::HIGH:
    return new Instruction(opcode, 0x0, data);
  }
}

} // namespace Instructions
