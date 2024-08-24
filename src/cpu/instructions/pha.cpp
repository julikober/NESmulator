#include "cpu.hpp"

void CPU::InstructionSet::mExecutePHA() { mCpu.mPushStack(mCpu.mAccumulator); }

void CPU::InstructionSet::PHAImplied() {
  mExecuteImplied(&InstructionSet::mExecutePHA);
}
