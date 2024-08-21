#include "cpu.hpp"

void CPU::mFetchInstruction() {
  mAddress = mProgramCounter;
  mProgramCounter++;

  mInstruction = (Instruction)mReadMemory();
}

void CPU::doCycle() {
  if (mCycle == 1) {
    mFetchInstruction();
  } else {
    switch (mInstruction) {
      // ADC
      case ADC_IMMEDIATE:
        mInstructionSet.ADCImmediate();
        break;

      case ADC_ZERO_PAGE:

        mInstructionSet.ADCZeroPage();
        break;

      case ADC_ZERO_PAGE_X:
        mInstructionSet.ADCZeroPageX();
        break;

      case ADC_ABSOLUTE:

        mInstructionSet.ADCAbsolute();
        break;

      case ADC_ABSOLUTE_X:
        mInstructionSet.ADCAbsoluteX();
        break;

      case ADC_ABSOLUTE_Y:
        mInstructionSet.ADCAbsoluteY();
        break;

      case ADC_INDIRECT_X:
        mInstructionSet.ADCIndirectX();
        break;

      case ADC_INDIRECT_Y:
        mInstructionSet.ADCIndirectY();
        break;

      // AND
      case AND_IMMEDIATE:
        mInstructionSet.ANDImmediate();
        break;

      case AND_ZERO_PAGE:
        mInstructionSet.ANDZeroPage();
        break;

      case AND_ZERO_PAGE_X:
        mInstructionSet.ANDZeroPageX();
        break;

      case AND_ABSOLUTE:
        mInstructionSet.ANDAbsolute();
        break;

      case AND_ABSOLUTE_X:
        mInstructionSet.ANDAbsoluteX();
        break;

      case AND_ABSOLUTE_Y:
        mInstructionSet.ANDAbsoluteY();
        break;

      case AND_INDIRECT_X:
        mInstructionSet.ANDIndirectX();
        break;

      case AND_INDIRECT_Y:
        mInstructionSet.ANDIndirectY();
        break;

      default:
        mCycle = 0;
        break;
    }
  }
  mCycle++;
}