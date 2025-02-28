#include "catch.hpp"

#include "Instructions/Instruction.h"

#include <iostream>
#include <sstream>

using namespace Instructions;

void Verify(Instruction *instr, std::string expected) {
  std::ostringstream os;
  instr->Dump(os);
  INFO("" << os.str() << "!=" << expected);
  CHECK(os.str() == expected);
}

TEST_CASE("Dump Instruction") {

  SECTION("Base instruction") {
    auto baseInstr = Instruction(Opcode::ADD, 0x0, 0x0);
    Verify(&baseInstr, "0x0 ADD");
  }
  SECTION("Sys") {
    auto sysInstr = SysInstruction(0x0, 0x0FFF);
    Verify(&sysInstr, "0x0 SYS 0xfff");
  }
}
