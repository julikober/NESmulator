#include "cpu/cpu.hpp"

void CPU::InstructionSet::mExecuteSED() { mCpu.mSetFlag(DECIMAL); }

void CPU::InstructionSet::SEDImplied() {
  mExecuteImplied(&InstructionSet::mExecuteSED);
}
