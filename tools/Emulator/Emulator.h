#pragma once

#include <CPU/CpuState.h>
#include <Instructions/Instruction.h>

#include <vector>

namespace emulator {

class Emulator {
public:
  Emulator(std::vector<Instructions::Instruction *> instructions);
  ~Emulator();

  void Run();

private:
  Instructions::Instruction *GetNextInstruction();
  void ExecuteInstruction(Instructions::Instruction *instruction);

  std::vector<Instructions::Instruction *> mInstructions;
  cpu::CpuState mState;
  bool mRunning;
};

} // namespace emulator
