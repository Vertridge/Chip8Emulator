#include "catch.hpp"

#include "Instructions/Disassembler.h"

#include <iostream>

TEST_CASE("Test retrieving definition") {
  for (auto &def : Instructions) {
    auto nemonic =
        Disassembler::GetInstructionDef(def.GetOpcode()).GetNemonic();
    INFO("Testing: " << def.GetNemonic() << " 0x" << std::hex
                     << static_cast<int>(def.GetOpcode()));
    CHECK(def.GetNemonic() == nemonic);
  }
}
