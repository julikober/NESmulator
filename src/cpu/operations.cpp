#include "cpu.hpp"

CPU::OperationOutput CPU::mSum(uint8_t a, uint8_t b, bool checkCarry) {
  uint8_t c = checkCarry ? mCheckFlag(CARRY) : 0;

  OperationOutput output;
  output.value = a + b + c;
  output.carry = (a + b + c) > 255;
  output.overflow = ((a ^ (uint8_t)(a + b + c)) & (uint8_t)(b ^ (a + b + c))) >> 7;

  return output;
}

CPU::OperationOutput CPU::mAnd(uint8_t a, uint8_t b) {
  OperationOutput output;
  output.value = a & b;
  output.carry = false;
  output.overflow = false;

  return output;
}

CPU::OperationOutput CPU::mOr(uint8_t a, uint8_t b) {
  OperationOutput output;
  output.value = a | b;
  output.carry = false;
  output.overflow = false;

  return output;
}

CPU::OperationOutput CPU::mEor(uint8_t a, uint8_t b) {
  OperationOutput output;
  output.value = a ^ b;
  output.carry = false;
  output.overflow = false;

  return output;
}

CPU::OperationOutput CPU::mShiftRight(uint8_t a) {
  OperationOutput output;
  output.value = a >> 1;
  output.carry = a & 0x01;
  output.overflow = false;

  return output;
}

