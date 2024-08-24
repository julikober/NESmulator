#include "cpu.hpp"

void CPU::mFetchInstruction() {
  mAddress = mProgramCounter;
  mProgramCounter++;

  mInstruction = (Instruction)mReadMemory();
}

void CPU::mPushStack(uint8_t value) {
  mAddress = mStackPointer + M_STACK_OFFSET;

  mWriteMemory(value);
  mStackPointer--;
}

uint8_t CPU::mPopStack() {
  mStackPointer++;
  mAddress = mStackPointer + M_STACK_OFFSET;

  return mReadMemory();
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

      // EOR
      case EOR_IMMEDIATE:
        mInstructionSet.EORImmediate();
        break;

      case EOR_ZERO_PAGE:
        mInstructionSet.EORZeroPage();
        break;

      case EOR_ZERO_PAGE_X:
        mInstructionSet.EORZeroPageX();
        break;

      case EOR_ABSOLUTE:
        mInstructionSet.EORAbsolute();
        break;

      case EOR_ABSOLUTE_X:
        mInstructionSet.EORAbsoluteX();
        break;

      case EOR_ABSOLUTE_Y:
        mInstructionSet.EORAbsoluteY();
        break;

      case EOR_INDIRECT_X:
        mInstructionSet.EORIndirectX();
        break;

      case EOR_INDIRECT_Y:
        mInstructionSet.EORIndirectY();
        break;

      // INC
      case INC_ZERO_PAGE:
        mInstructionSet.INCZeroPage();
        break;

      case INC_ZERO_PAGE_X:
        mInstructionSet.INCZeroPageX();
        break;

      case INC_ABSOLUTE:
        mInstructionSet.INCAbsolute();
        break;

      case INC_ABSOLUTE_X:
        mInstructionSet.INCAbsoluteX();
        break;

      // INX
      case INX_IMPLIED:
        mInstructionSet.INXImplied();
        break;

      // INY
      case INY_IMPLIED:
        mInstructionSet.INYImplied();
        break;

      // LDA
      case LDA_IMMEDIATE:
        mInstructionSet.LDAImmediate();
        break;

      case LDA_ZERO_PAGE:
        mInstructionSet.LDAZeroPage();
        break;

      case LDA_ZERO_PAGE_X:
        mInstructionSet.LDAZeroPageX();
        break;

      case LDA_ABSOLUTE:
        mInstructionSet.LDAAbsolute();
        break;

      case LDA_ABSOLUTE_X:
        mInstructionSet.LDAAbsoluteX();
        break;

      case LDA_ABSOLUTE_Y:
        mInstructionSet.LDAAbsoluteY();
        break;

      case LDA_INDIRECT_X:
        mInstructionSet.LDAIndirectX();
        break;

      case LDA_INDIRECT_Y:
        mInstructionSet.LDAIndirectY();
        break;

      // LDX
      case LDX_IMMEDIATE:
        mInstructionSet.LDXImmediate();
        break;

      case LDX_ZERO_PAGE:
        mInstructionSet.LDXZeroPage();
        break;

      case LDX_ZERO_PAGE_Y:
        mInstructionSet.LDXZeroPageY();
        break;

      case LDX_ABSOLUTE:
        mInstructionSet.LDXAbsolute();
        break;

      case LDX_ABSOLUTE_Y:
        mInstructionSet.LDXAbsoluteY();
        break;

      // LDY
      case LDY_IMMEDIATE:
        mInstructionSet.LDYImmediate();
        break;

      case LDY_ZERO_PAGE:
        mInstructionSet.LDYZeroPage();
        break;

      case LDY_ZERO_PAGE_X:
        mInstructionSet.LDYZeroPageX();
        break;

      case LDY_ABSOLUTE:
        mInstructionSet.LDYAbsolute();
        break;

      case LDY_ABSOLUTE_X:
        mInstructionSet.LDYAbsoluteX();
        break;

      // LSR
      case LSR_ACCUMULATOR:
        mInstructionSet.LSRAccumulator();
        break;

      case LSR_ZERO_PAGE:
        mInstructionSet.LSRZeroPage();
        break;

      case LSR_ZERO_PAGE_X:
        mInstructionSet.LSRZeroPageX();
        break;

      case LSR_ABSOLUTE:
        mInstructionSet.LSRAbsolute();
        break;

      case LSR_ABSOLUTE_X:
        mInstructionSet.LSRAbsoluteX();
        break;

      // NOP
      case NOP_IMPLIED:
        mInstructionSet.NOPImplied();
        break;

      // ORA
      case ORA_IMMEDIATE:
        mInstructionSet.ORAImmediate();
        break;

      case ORA_ZERO_PAGE:
        mInstructionSet.ORAZeroPage();
        break;

      case ORA_ZERO_PAGE_X:
        mInstructionSet.ORAZeroPageX();
        break;

      case ORA_ABSOLUTE:
        mInstructionSet.ORAAbsolute();
        break;

      case ORA_ABSOLUTE_X:
        mInstructionSet.ORAAbsoluteX();
        break;

      case ORA_ABSOLUTE_Y:
        mInstructionSet.ORAAbsoluteY();
        break;

      case ORA_INDIRECT_X:
        mInstructionSet.ORAIndirectX();
        break;

      case ORA_INDIRECT_Y:
        mInstructionSet.ORAIndirectY();
        break;

      // PHA
      case PHA_IMPLIED:
        mInstructionSet.PHAImplied();
        break;

      // PHP
      case PHP_IMPLIED:
        mInstructionSet.PHPImplied();
        break;

      // PLA
      case PLA_IMPLIED:
        mInstructionSet.PLAImplied();
        break;

      // PLP
      case PLP_IMPLIED:
        mInstructionSet.PLPImplied();
        break;

      default:
        mCycle = 0;
        break;
    }
  }
  mCycle++;
}
