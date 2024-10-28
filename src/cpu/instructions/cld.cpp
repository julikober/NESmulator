#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteCLD() { mCpu.mClearFlag(DECIMAL); }

void CPU::InstructionSet::CLDImplied() {
  mExecuteImplied(&InstructionSet::mExecuteCLD);
}
