#include "cpu.hpp"

uint8_t CPU::mAddWithCarry(uint8_t a, uint8_t b) {
  uint8_t c = mCheckFlag(CARRY);

  if ((uint8_t)(a + b + c) == 0) {
    mSetFlag(ZERO);
  } else {
    mClearFlag(ZERO);
  }

  if ((uint8_t)(a + b + c) >> 7) {
    mSetFlag(NEGATIVE);
  } else {
    mClearFlag(NEGATIVE);
  }

  if (a + b + c > 255) {
    mSetFlag(CARRY);
  } else {
    mClearFlag(CARRY);
  }

  if (((a ^ (uint8_t)(a + b + c)) & (uint8_t)(b ^ (a + b + c))) >> 7) {
    mSetFlag(OVERFLOW);
  } else {
    mClearFlag(OVERFLOW);
  }

  return a + b + c;
}

uint8_t CPU::mOr(uint8_t a, uint8_t b) {
  if (a | b == 0) {
    mSetFlag(ZERO);
  } else {
    mClearFlag(ZERO);
  }

  if (a | b >> 7) {
    mSetFlag(NEGATIVE);
  } else {
    mClearFlag(NEGATIVE);
  }

  return a | b;
}

uint8_t CPU::mShiftLeft(uint8_t a) {
  if (a << 1 == 0) {
    mSetFlag(ZERO);
  } else {
    mClearFlag(ZERO);
  }

  if (a << 1 >> 7) {
    mSetFlag(NEGATIVE);
  } else {
    mClearFlag(NEGATIVE);
  }

  if (a << 7) {
    mSetFlag(CARRY);
  } else {
    mClearFlag(CARRY);
  }

  return a << 1;
}