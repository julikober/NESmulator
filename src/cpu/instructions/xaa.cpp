#include "cpu/cpu.hpp"

#define UNDETERMINISTIC_CONSTANT \
  0xEE  // This constant varies from cpu to cpu. To match the test cases 0xEE
        // was chosen.

void CPU::InstructionSet::mReadXAA() {
  mCpu.mAccumulator = (mCpu.mAccumulator | UNDETERMINISTIC_CONSTANT) &
                      mCpu.mXIndex & mCpu.mReadMemory();

  mCpu.mUpdateZeroAndNegative(mCpu.mAccumulator);
}

void CPU::InstructionSet::XAAImmediate() {
  mExecuteImmediate(&CPU::InstructionSet::mReadXAA);
}
