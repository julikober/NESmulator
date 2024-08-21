#include "cpu.hpp"

bool CPU::InstructionSet::mCheckBMI() { return mCpu.mCheckFlag(NEGATIVE); }

void CPU::InstructionSet::BMIRelative() {
  mExecuteRelative(&InstructionSet::mCheckBMI);
}