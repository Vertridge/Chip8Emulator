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

  SECTION("Cls") {
    auto clsInstr = ClsInstruction(0x0, 0x00E0);
    Verify(&clsInstr, "0x0 CLS");
  }

  SECTION("Ret") {
    auto retInstr = RetInstruction(0x0, 0x00EE);
    Verify(&retInstr, "0x0 RET");
  }

  SECTION("Jp") {
    auto jpInstr = JpInstruction(0x0, 0x1FFF);
    Verify(&jpInstr, "0x0 JP 0xfff");
  }

  SECTION("Add") {
    auto addInstr = AddInstruction(0x0, 0x710F);
    Verify(&addInstr, "0x0 ADD V1 0xf");

    CpuState state;
    addInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V1 = 0x10;
    addInstr.Execute(state);
    CHECK(state.registers.V1 == 0x1F);
  }
}
