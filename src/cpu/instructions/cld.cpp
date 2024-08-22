#include "cpu.hpp"

void CPU::InstructionSet::mExecuteCLD() { mCpu.mClearFlag(DECIMAL); }

void CPU::InstructionSet::CLDImplied() {
  mExecuteImmediate(&InstructionSet::mExecuteCLD);
}
