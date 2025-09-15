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

Instruction *CreateInstruction(std::uint16_t address, Opcode opcode,
                               std::uint16_t data) {
  switch (opcode) {
  case Opcode::CLS:
    return new ClsInstruction(address, data);
  case Opcode::RET:
    return new RetInstruction(address, data);
  case Opcode::SYS:
    return new SysInstruction(address, data);
  case Opcode::JP:
    return new JpInstruction(address, data);
  case Opcode::RND:
    return new Instruction(opcode, address, data);
  case Opcode::CALL:
    return new CallInstruction(address, data);
  case Opcode::SExkk:
    return new SexkkInstruction(address, data);
  case Opcode::SExy:
    return new SexyInstruction(address, data);
  case Opcode::SNExkk:
    return new SnexkkInstruction(address, data);
  case Opcode::SNExy:
    return new SnexyInstruction(address, data);
  case Opcode::LDxkk:
    return new LdxkkInstruction(address, data);
  case Opcode::LDxy:
    return new LdxyInstruction(address, data);
  case Opcode::LDnnn:
    return new LdnnnInstruction(address, data);
  case Opcode::LDxdt:
    return new LdxdtInstruction(address, data);
  case Opcode::LDx0:
    return new Instruction(opcode, address, data);
  case Opcode::LDdtx:
    return new LddtxInstruction(address, data);
  case Opcode::LDstx:
    return new LdstxInstruction(address, data);
  case Opcode::LDfx:
  case Opcode::LDbx:
    return new Instruction(opcode, address, data);
  case Opcode::LDix:
    return new LdixInstruction(address, data);
  case Opcode::LDxi:
    return new LdxiInstruction(address, data);
  case Opcode::ADDxkk:
    return new AddxkkInstruction(address, data);
  case Opcode::ADDxy:
    return new AddxyInstruction(address, data);
  case Opcode::ADDix:
    return new AddixInstruction(address, data);
  case Opcode::SUB:
    return new SubInstruction(address, data);
  case Opcode::SUBN:
    return new SubnInstruction(address, data);
  case Opcode::OR:
    return new OrInstruction(address, data);
  case Opcode::AND:
    return new AndInstruction(address, data);
  case Opcode::XOR:
    return new XorInstruction(address, data);
  case Opcode::SHR:
    return new ShrInstruction(address, data);
  case Opcode::SHL:
    return new ShlInstruction(address, data);
  case Opcode::SKP:
    return new Instruction(opcode, address, data);
  case Opcode::SKNP:
    return new Instruction(opcode, address, data);
  case Opcode::DRW:
    return new Instruction(opcode, address, data);
  case Opcode::SCD:
    return new Instruction(opcode, address, data);
  case Opcode::SCR:
    return new Instruction(opcode, address, data);
  case Opcode::SCL:
    return new Instruction(opcode, address, data);
  case Opcode::EXIT:
    return new Instruction(opcode, address, data);
  case Opcode::LOW:
    return new Instruction(opcode, address, data);
  case Opcode::HIGH:
    return new Instruction(opcode, address, data);
  }
}

} // namespace Instructions
