#include "cpu/cpu.hpp"

bool CPU::InstructionSet::mCheckBNE() { return !mCpu.mCheckFlag(ZERO); }

void CPU::InstructionSet::BNERelative() {
  mExecuteRelative(&InstructionSet::mCheckBNE);
}
