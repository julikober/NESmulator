#include "cpu.hpp"

bool CPU::InstructionSet::mCheckBVC() { return !mCpu.mCheckFlag(OVERFLOW); }

void CPU::InstructionSet::BVCRelative() {
  mExecuteRelative(&InstructionSet::mCheckBVC);
}