#include "cpu.hpp"

void CPU::mFetchInstruction() {
  mAddress = mProgramCounter;
  mProgramCounter++;

  mInstruction = (Instruction)mReadMemory();
}

void CPU::mSetZeroAndNegative(uint8_t value) {
  if (value == 0) {
    mSetFlag(ZERO);
  } else {
    mClearFlag(ZERO);
  }

  if (value & (1 << 7)) {
    mSetFlag(NEGATIVE);
  } else {
    mClearFlag(NEGATIVE);
  }
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

      // ASL
      case ASL_ACCUMULATOR:
        mInstructionSet.ASLAccumulator();
        break;

      case ASL_ZERO_PAGE:
        mInstructionSet.ASLZeroPage();
        break;

      case ASL_ZERO_PAGE_X:
        mInstructionSet.ASLZeroPageX();
        break;

      case ASL_ABSOLUTE:
        mInstructionSet.ASLAbsolute();
        break;

      case ASL_ABSOLUTE_X:
        mInstructionSet.ASLAbsoluteX();
        break;

      // BCC
      case BCC_RELATIVE:
        mInstructionSet.BCCRelative();
        break;

      // BCS
      case BCS_RELATIVE:
        mInstructionSet.BCSRelative();
        break;

      // BEQ
      case BEQ_RELATIVE:
        mInstructionSet.BEQRelative();
        break;

      // BIT
      case BIT_ZERO_PAGE:
        mInstructionSet.BITZeroPage();
        break;

      case BIT_ABSOLUTE:
        mInstructionSet.BITAbsolute();
        break;

      // BMI
      case BMI_RELATIVE:
        mInstructionSet.BMIRelative();
        break;

      // BNE
      case BNE_RELATIVE:
        mInstructionSet.BNERelative();
        break;

      // BPL
      case BPL_RELATIVE:
        mInstructionSet.BPLRelative();
        break;

      // BVC
      case BVC_RELATIVE:
        mInstructionSet.BVCRelative();
        break;

      // BVS
      case BVS_RELATIVE:
        mInstructionSet.BVSRelative();
        break;

      // CLC
      case CLC_IMPLIED:
        mInstructionSet.CLCImplied();
        break;

      // CLD
      case CLD_IMPLIED:
        mInstructionSet.CLDImplied();
        break;

      // CLI
      case CLI_IMPLIED:
        mInstructionSet.CLIImplied();
        break;

      // CLV
      case CLV_IMPLIED:
        mInstructionSet.CLVImplied();
        break;

      // CMP
      case CMP_IMMEDIATE:
        mInstructionSet.CMPImmediate();
        break;

      case CMP_ZERO_PAGE:
        mInstructionSet.CMPZeroPage();
        break;

      case CMP_ZERO_PAGE_X:
        mInstructionSet.CMPZeroPageX();
        break;

      case CMP_ABSOLUTE:
        mInstructionSet.CMPAbsolute();
        break;

      case CMP_ABSOLUTE_X:
        mInstructionSet.CMPAbsoluteX();
        break;

      case CMP_ABSOLUTE_Y:
        mInstructionSet.CMPAbsoluteY();
        break;

      case CMP_INDIRECT_X:
        mInstructionSet.CMPIndirectX();
        break;

      case CMP_INDIRECT_Y:
        mInstructionSet.CMPIndirectY();
        break;

      // CPX
      case CPX_IMMEDIATE:
        mInstructionSet.CPXImmediate();
        break;

      case CPX_ZERO_PAGE:
        mInstructionSet.CPXZeroPage();
        break;

      case CPX_ABSOLUTE:
        mInstructionSet.CPXAbsolute();
        break;

      // CPY
      case CPY_IMMEDIATE:
        mInstructionSet.CPYImmediate();
        break;

      case CPY_ZERO_PAGE:
        mInstructionSet.CPYZeroPage();
        break;

      case CPY_ABSOLUTE:
        mInstructionSet.CPYAbsolute();
        break;

      // DEC
      case DEC_ZERO_PAGE:
        mInstructionSet.DECZeroPage();
        break;

      case DEC_ZERO_PAGE_X:
        mInstructionSet.DECZeroPageX();
        break;

      case DEC_ABSOLUTE:
        mInstructionSet.DECAbsolute();
        break;

      case DEC_ABSOLUTE_X:
        mInstructionSet.DECAbsoluteX();
        break;

      // DEX
      case DEX_IMPLIED:
        mInstructionSet.DEXImplied();
        break;

      // DEY
      case DEY_IMPLIED:
        mInstructionSet.DEYImplied();
        break;

      default:
        mCycle = 0;
        break;
    }
  }
  mCycle++;
}