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

  SECTION("Call") {
    auto callInstr = CallInstruction(0x0, 0x2FFF);
    Verify(&callInstr, "0x0 CALL 0xfff");
  }

  SECTION("Sexkk") {
    auto sexkkInstr = SexkkInstruction(0x0, 0x310F);
    Verify(&sexkkInstr, "0x0 SE V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 1);

    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 0);
  }

  SECTION("Sexy") {
    auto sexyInstr = SexyInstruction(0x0, 0x5010);
    Verify(&sexyInstr, "0x0 SE V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 1);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    sexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 0);
  }

  SECTION("Snexkk") {
    auto snexkkInstr = SnexkkInstruction(0x0, 0x410F);
    Verify(&snexkkInstr, "0x0 SNE V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    snexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 0);

    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    snexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 1);
  }

  SECTION("Snexy") {
    auto snexyInstr = SnexyInstruction(0x0, 0x9010);
    Verify(&snexyInstr, "0x0 SNE V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    snexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 0);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    snexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 1);
  }

  SECTION("Jp") {
    auto jpInstr = JpInstruction(0x0, 0x1FFF);
    Verify(&jpInstr, "0x0 JP 0xfff");
  }

  SECTION("Ldxkk") {
    auto ldxkkInstr = LdxkkInstruction(0x0, 0x610F);
    Verify(&ldxkkInstr, "0x0 LD V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0;
    ldxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
  }

  SECTION("Ldxy") {
    auto ldxyInstr = LdxyInstruction(0x0, 0x8010);
    Verify(&ldxyInstr, "0x0 LD V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    ldxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
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
