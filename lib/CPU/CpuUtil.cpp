#include "CPU/CpuUtil.h"
#include <cassert>

namespace cpu {
std::string ToString(Register reg) {
  switch (reg) {
  case Register::V0:
    return "V0";
  case Register::V1:
    return "V1";
  case Register::V2:
    return "V2";
  case Register::V3:
    return "V3";
  case Register::V4:
    return "V4";
  case Register::V5:
    return "V5";
  case Register::V6:
    return "V6";
  case Register::V7:
    return "V7";
  case Register::V8:
    return "V8";
  case Register::V9:
    return "V9";
  case Register::VA:
    return "VA";
  case Register::VB:
    return "VB";
  case Register::VC:
    return "VC";
  case Register::VD:
    return "VD";
  case Register::VE:
    return "VE";
  case Register::VF:
    return "VF";
  case Register::I:
    return "I";
  case Register::VDelay:
    return "VDelay";
  case Register::VSound:
    return "VSound";
  case Register::PC:
    return "PC";
  case Register::SP:
    return "SP";
  }
}
std::uint8_t &GetRegister(Register reg, CpuState &state) {
  switch (reg) {
  case Register::V0:
    return state.registers.V0;
  case Register::V1:
    return state.registers.V1;
  case Register::V2:
    return state.registers.V2;
  case Register::V3:
    return state.registers.V3;
  case Register::V4:
    return state.registers.V4;
  case Register::V5:
    return state.registers.V5;
  case Register::V6:
    return state.registers.V6;
  case Register::V7:
    return state.registers.V7;
  case Register::V8:
    return state.registers.V8;
  case Register::V9:
    return state.registers.V9;
  case Register::VA:
    return state.registers.VA;
  case Register::VB:
    return state.registers.VB;
  case Register::VC:
    return state.registers.VC;
  case Register::VD:
    return state.registers.VD;
  case Register::VE:
    return state.registers.VE;
  case Register::VF:
    return state.registers.VF;
  case Register::I:
    assert(false && "Cannot get 16bit register");
    return state.registers.V0;
  case Register::VDelay:
    return state.registers.VDelay;
  case Register::VSound:
    return state.registers.VSound;
  case Register::PC:
    assert(false && "Cannot get 16bit register");
    return state.registers.V0;
  case Register::SP:
    return state.registers.SP;
  }
}
} // namespace cpu
