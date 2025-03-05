#include "cpu/cpu.hpp"

void CPU::mDoInterrupt(Interrupt interrupt) {
  switch (mCycle) {
    case 2:
      mProgramCounter++;
      break;

    case 3:
      mPushStack(mGetProgramCounterHigh());
      mStackPointer--;
      break;

    case 4:
      mPushStack(mGetProgramCounterLow());
      mStackPointer--;
      break;

    case 5:
      mPushStack(mStatus | BREAK);
      mStackPointer--;
      break;

    case 6:
      switch (interrupt) {
        case NMI:
          mAddress = NMI_VECTOR;
          break;

        case IRQ:
          mAddress = IRQ_BRK_VECTOR;
          break;

        case BRK:
          mAddress = IRQ_BRK_VECTOR;
          break;

        case RESET:
          mAddress = RESET_VECTOR;
          break;
      }
      mSetProgramCounterLow(mReadMemory());
      break;

    case 7:
      switch (interrupt) {
        case NMI:
          mAddress = NMI_VECTOR + 1;
          break;
        case IRQ:
          mAddress = IRQ_BRK_VECTOR + 1;
          break;
        case BRK:
          mAddress = IRQ_BRK_VECTOR + 1;
          break;
        case RESET:
          mAddress = RESET_VECTOR + 1;
          break;
      }
      mSetProgramCounterHigh(mReadMemory());

      mSetFlag(INTERRUPT_DISABLE);

    default:
      mCycle = 0;
      break;
  }
}