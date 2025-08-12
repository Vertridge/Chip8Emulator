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
  case Opcode::SExkk:
  case Opcode::SExy:
    return "SE";
  case Opcode::SNExkk:
  case Opcode::SNExy:
    return "SNE";
  case Opcode::LDxkk:
  case Opcode::LDxy:
  case Opcode::LDnnn:
  case Opcode::LDxdt:
  case Opcode::LDx0:
  case Opcode::LDdtx:
  case Opcode::LDstx:
  case Opcode::LDfx:
  case Opcode::LDbx:
  case Opcode::LDix:
  case Opcode::LDxi:
    return "LD";
  case Opcode::ADDxkk:
  case Opcode::ADDxy:
  case Opcode::ADDix:
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
    return new CallInstruction(0x0, data);
  case Opcode::SExkk:
    return new SexkkInstruction(0x0, data);
  case Opcode::SExy:
    return new SexyInstruction(0x0, data);
  case Opcode::SNExkk:
    return new SnexkkInstruction(0x0, data);
  case Opcode::SNExy:
    return new SnexyInstruction(0x0, data);
  case Opcode::LDxkk:
    return new LdxkkInstruction(0x0, data);
  case Opcode::LDxy:
    return new LdxyInstruction(0x0, data);
  case Opcode::LDnnn:
    return new LdnnnInstruction(0x0, data);
  case Opcode::LDxdt:
    return new LdxdtInstruction(0x0, data);
  case Opcode::LDx0:
    return new Instruction(opcode, 0x0, data);
  case Opcode::LDdtx:
    return new LddtxInstruction(0x0, data);
  case Opcode::LDstx:
    return new LdstxInstruction(0x0, data);
  case Opcode::LDfx:
  case Opcode::LDbx:
    return new Instruction(opcode, 0x0, data);
  case Opcode::LDix:
    return new LdixInstruction(0x0, data);
  case Opcode::LDxi:
    return new LdxiInstruction(0x0, data);
  case Opcode::ADDxkk:
    return new AddxkkInstruction(0x0, data);
  case Opcode::ADDxy:
    return new AddxyInstruction(0x0, data);
  case Opcode::ADDix:
    return new AddixInstruction(0x0, data);
  case Opcode::SUB:
    return new SubInstruction(0x0, data);
  case Opcode::SUBN:
    return new SubnInstruction(0x0, data);
  case Opcode::OR:
    return new OrInstruction(0x0, data);
  case Opcode::AND:
    return new AndInstruction(0x0, data);
  case Opcode::XOR:
    return new XorInstruction(0x0, data);
  case Opcode::SHR:
    return new ShrInstruction(0x0, data);
  case Opcode::SHL:
    return new ShlInstruction(0x0, data);
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
