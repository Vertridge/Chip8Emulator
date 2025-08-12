#include "catch.hpp"

#include "CPU/Memory.h"

TEST_CASE("Test Valid Addresses") {
  cpu::Memory memory;
  CHECK_FALSE(memory.IsValidAddress(0x0));
  CHECK_FALSE(memory.IsValidAddress(cpu::memory_start - 0x1));
  CHECK_FALSE(memory.IsValidAddress(cpu::memory_size));

  CHECK(memory.IsValidAddress(cpu::memory_start));
  CHECK(memory.IsValidAddress(cpu::memory_size - 0x1));
  CHECK(memory.IsValidAddress(cpu::memory_size - cpu::memory_start));
}

TEST_CASE("Read write memory") {
  cpu::Memory memory;
  SECTION("Writing") {
    memory.Write(cpu::memory_start, 0xF);
    CHECK(memory.Read(cpu::memory_start) == 0xF);
  }

  SECTION("Zero initialised") { CHECK(memory.Read(cpu::memory_start) == 0x0); }
}
