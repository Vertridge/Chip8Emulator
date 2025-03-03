#include "CPU/CpuUtil.h"

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
} // namespace cpu
