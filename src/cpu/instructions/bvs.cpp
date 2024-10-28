#include "cpu/cpu.hpp"

bool CPU::InstructionSet::mCheckBVS() { return mCpu.mCheckFlag(OVERFLOW); }

void CPU::InstructionSet::BVSRelative() {
  mExecuteRelative(&InstructionSet::mCheckBVS);
}
