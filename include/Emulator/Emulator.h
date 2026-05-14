#pragma once

#include <CPU/CpuState.h>
#include <Instructions/Instruction.h>

#include <filesystem>
#include <vector>

namespace emulator {

class Emulator {
public:
  Emulator();
  ~Emulator();

  bool LoadGame(const std::filesystem::path path);
  void Run(bool dumpState = false);
  void DumpState(std::ostream &os);

private:
  Instructions::Instruction *GetNextInstruction();
  void ExecuteInstruction(Instructions::Instruction *instruction);
  bool LoadSprites();

  std::vector<Instructions::Instruction *> mInstructions;
  cpu::CpuState mState;
  bool mRunning;
};

} // namespace emulator
