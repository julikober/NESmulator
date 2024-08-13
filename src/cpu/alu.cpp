#include "cpu.hpp"

uint8_t CPU::ALU::SUM(uint8_t a, uint8_t b, bool addCarry = false) {
  uint8_t c = addCarry ? mCpu.mCheckFlag(CARRY) : 0;

  if (a + b + c == 0) {
    mCpu.mSetFlag(ZERO);
  } else {
    mCpu.mClearFlag(ZERO);
  }

  if (a + b + c >> 7) {
    mCpu.mSetFlag(NEGATIVE);
  } else {
    mCpu.mClearFlag(NEGATIVE);
  }

  if (a + b + c > 255) {
    mCpu.mSetFlag(CARRY);
  } else {
    mCpu.mClearFlag(CARRY);
  }

  return a + b + c;
}

uint8_t CPU::ALU::OR(uint8_t a, uint8_t b) {
  if (a | b == 0) {
    mCpu.mSetFlag(ZERO);
  } else {
    mCpu.mClearFlag(ZERO);
  }

  if (a | b >> 7) {
    mCpu.mSetFlag(NEGATIVE);
  } else {
    mCpu.mClearFlag(NEGATIVE);
  }

  return a | b;
}