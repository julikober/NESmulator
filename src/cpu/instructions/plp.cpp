#include "cpu.hpp"

void CPU::InstructionSet::PLPImplied() {
  switch (mCpu.mCycle) {
    case 2:
      break;

    case 3:
      mCpu.mStackPointer++;
      break;

    case 4:
      mCpu.mStatus |= mCpu.mPopStack() &
                      (CARRY | ZERO | INTERRUPT_DISABLE | DECIMAL | OVERFLOW |
                       NEGATIVE);  // Ignore BREAK flag when pulling from stack

    default:
      mCpu.mCycle = 0;
      break;
  }
}
