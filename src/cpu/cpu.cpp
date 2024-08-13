#include "cpu.hpp"

void CPU::do_cycle() {
  if (mCycle == 1) {
    mAddress = mProgramCounter;
    mInstruction = (Instruction)mReadMemory();
    mProgramCounter++;

  } else {
    switch (mInstruction) {
      // 0x00
      case ORA_INDIRECT_X:
        mInstructionSet.ORAIndirectX();
        break;

      // 0x05
      case ORA_ZERO_PAGE:
        mInstructionSet.ORAZeroPage();
        break;

      // 0x06
      case ASL_ZERO_PAGE:
        mInstructionSet.ASLZeroPage();
        break;

      // 0x65
      case ADC_ZERO_PAGE:
        mInstructionSet.ADCZeroPage();
        break;

      // 0x69
      case ADC_IMMEDIATE:
        mInstructionSet.ADCImmediate();
        break;

      default:
        mCycle = 1;
        break;
    }
  }
  mCycle++;
}