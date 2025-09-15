#include "catch.hpp"

#include "Instructions/Disassembler.h"

#include <cstdint>
#include <iostream>

TEST_CASE("Test retrieving definition") {
  for (auto &def : InstructionDefinitions) {
    auto nemonic =
        Disassembler::GetInstructionDef(def.GetOpcodeNum()).GetNemonic();
    INFO("Testing: " << def.GetNemonic() << " 0x" << std::hex
                     << static_cast<int>(def.GetOpcode()));
    CHECK(def.GetNemonic() == nemonic);
  }
}

TEST_CASE("Disassemble To String") {
  std::vector<std::uint16_t> input = {0x00E0, 0x610F, 0x620A, 0x8124};
  auto disassembled = Disassembler::DisassembleToString(input);
  INFO("Checking Disassembly: " << disassembled);
  auto expected = "0x200 CLS\n"
                  "0x202 LD V1 0xf\n"
                  "0x204 LD V2 0xa\n"
                  "0x206 ADD V1 V2\n";
  CHECK(disassembled == expected);
}
