#include "cpu.hpp"

void CPU::InstructionSet::mExecuteCLV() { mCpu.mClearFlag(OVERFLOW); }

void CPU::InstructionSet::CLVImplied() {
  mExecuteImplied(&InstructionSet::mExecuteCLV);
}