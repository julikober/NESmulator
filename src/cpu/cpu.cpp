#include "cpu.hpp"

void CPU::mFetchInstruction() {
  mAddress = mProgramCounter;
  mProgramCounter++;

  mInstruction = (Instruction)mReadMemory();
}

void CPU::mPushStack(uint8_t value) {
  mAddress = mStackPointer + M_STACK_OFFSET;

  mWriteMemory(value);
}

uint8_t CPU::mPopStack() {
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

      // BRK
      case BRK_IMPLIED:
        mInstructionSet.BRKImplied();
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

      // JMP
      case JMP_ABSOLUTE:
        mInstructionSet.JMPAbsolute();
        break;

      case JMP_INDIRECT:
        mInstructionSet.JMPIndirect();
        break;

      // JSR
      case JSR_ABSOLUTE:
        mInstructionSet.JSRAbsolute();
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

      // ROL
      case ROL_ACCUMULATOR:
        mInstructionSet.ROLAccumulator();
        break;

      case ROL_ZERO_PAGE:
        mInstructionSet.ROLZeroPage();
        break;

      case ROL_ZERO_PAGE_X:
        mInstructionSet.ROLZeroPageX();
        break;

      case ROL_ABSOLUTE:
        mInstructionSet.ROLAbsolute();
        break;

      case ROL_ABSOLUTE_X:
        mInstructionSet.ROLAbsoluteX();
        break;

      // ROR
      case ROR_ACCUMULATOR:
        mInstructionSet.RORAccumulator();
        break;

      case ROR_ZERO_PAGE:
        mInstructionSet.RORZeroPage();
        break;

      case ROR_ZERO_PAGE_X:
        mInstructionSet.RORZeroPageX();
        break;

      case ROR_ABSOLUTE:
        mInstructionSet.RORAbsolute();
        break;

      case ROR_ABSOLUTE_X:
        mInstructionSet.RORAbsoluteX();
        break;

      // RTI
      case RTI_IMPLIED:
        mInstructionSet.RTIImplied();
        break;

      // RTS
      case RTS_IMPLIED:
        mInstructionSet.RTSImplied();
        break;

      // SBC
      case SBC_IMMEDIATE:
        mInstructionSet.SBCImmediate();
        break;

      case SBC_ZERO_PAGE:
        mInstructionSet.SBCZeroPage();
        break;

      case SBC_ZERO_PAGE_X:
        mInstructionSet.SBCZeroPageX();
        break;

      case SBC_ABSOLUTE:
        mInstructionSet.SBCAbsolute();
        break;

      case SBC_ABSOLUTE_X:
        mInstructionSet.SBCAbsoluteX();
        break;

      case SBC_ABSOLUTE_Y:
        mInstructionSet.SBCAbsoluteY();
        break;

      case SBC_INDIRECT_X:
        mInstructionSet.SBCIndirectX();
        break;

      case SBC_INDIRECT_Y:
        mInstructionSet.SBCIndirectY();
        break;

      // SEC
      case SEC_IMPLIED:
        mInstructionSet.SECImplied();
        break;

      // SED
      case SED_IMPLIED:
        mInstructionSet.SEDImplied();
        break;

      // SEI
      case SEI_IMPLIED:
        mInstructionSet.SEIImplied();
        break;

      // STA
      case STA_ZERO_PAGE:
        mInstructionSet.STAZeroPage();
        break;

      case STA_ZERO_PAGE_X:
        mInstructionSet.STAZeroPageX();
        break;

      case STA_ABSOLUTE:
        mInstructionSet.STAAbsolute();
        break;

      case STA_ABSOLUTE_X:
        mInstructionSet.STAAbsoluteX();
        break;

      case STA_ABSOLUTE_Y:
        mInstructionSet.STAAbsoluteY();
        break;

      case STA_INDIRECT_X:
        mInstructionSet.STAIndirectX();
        break;

      case STA_INDIRECT_Y:
        mInstructionSet.STAIndirectY();
        break;

      // STX
      case STX_ZERO_PAGE:
        mInstructionSet.STXZeroPage();
        break;

      case STX_ZERO_PAGE_Y:
        mInstructionSet.STXZeroPageY();
        break;

      case STX_ABSOLUTE:
        mInstructionSet.STXAbsolute();
        break;

      // STY
      case STY_ZERO_PAGE:
        mInstructionSet.STYZeroPage();
        break;

      case STY_ZERO_PAGE_X:
        mInstructionSet.STYZeroPageX();
        break;

      case STY_ABSOLUTE:
        mInstructionSet.STYAbsolute();
        break;

      // TAX
      case TAX_IMPLIED:
        mInstructionSet.TAXImplied();
        break;

      // TAY
      case TAY_IMPLIED:
        mInstructionSet.TAYImplied();
        break;

      // TSX
      case TSX_IMPLIED:
        mInstructionSet.TSXImplied();
        break;

      // TXA
      case TXA_IMPLIED:
        mInstructionSet.TXAImplied();
        break;

      // TXS
      case TXS_IMPLIED:
        mInstructionSet.TXSImplied();
        break;

      // TYA
      case TYA_IMPLIED:
        mInstructionSet.TYAImplied();
        break;

      // Unofficial opcodes
      // AHX
      case AHX_ABSOLUTE_Y:
        mInstructionSet.AHXAbsoluteY();
        break;

      case AHX_INDIRECT_Y:
        mInstructionSet.AHXIndirectY();
        break;

      // ALR
      case ALR_IMMEDIATE:
        mInstructionSet.ALRImmediate();
        break;

      // ANC
      case ANC_IMMEDIATE_1:
        mInstructionSet.ANCImmediate();
        break;

      case ANC_IMMEDIATE_2:
        mInstructionSet.ANCImmediate();
        break;

      // ARR
      case ARR_IMMEDIATE:
        mInstructionSet.ARRImmediate();
        break;

      // AXS
      case AXS_IMMEDIATE:
        mInstructionSet.AXSImmediate();
        break;

      // DCP
      case DCP_ZERO_PAGE:
        mInstructionSet.DCPZeroPage();
        break;

      case DCP_ZERO_PAGE_X:
        mInstructionSet.DCPZeroPageX();
        break;

      case DCP_ABSOLUTE:
        mInstructionSet.DCPAbsolute();
        break;

      case DCP_ABSOLUTE_X:
        mInstructionSet.DCPAbsoluteX();
        break;

      case DCP_ABSOLUTE_Y:
        mInstructionSet.DCPAbsoluteY();
        break;

      case DCP_INDIRECT_X:
        mInstructionSet.DCPIndirectX();
        break;

      case DCP_INDIRECT_Y:
        mInstructionSet.DCPIndirectY();
        break;

      // ISC
      case ISC_ZERO_PAGE:
        mInstructionSet.ISCZeroPage();
        break;

      case ISC_ZERO_PAGE_X:
        mInstructionSet.ISCZeroPageX();
        break;

      case ISC_ABSOLUTE:
        mInstructionSet.ISCAbsolute();
        break;

      case ISC_ABSOLUTE_X:
        mInstructionSet.ISCAbsoluteX();
        break;

      case ISC_ABSOLUTE_Y:
        mInstructionSet.ISCAbsoluteY();
        break;

      case ISC_INDIRECT_X:
        mInstructionSet.ISCIndirectX();
        break;

      case ISC_INDIRECT_Y:
        mInstructionSet.ISCIndirectY();
        break;

      // LAS
      case LAS_ABSOLUTE_Y:
        mInstructionSet.LASAbsoluteY();
        break;

      // LAX
      case LAX_IMMEDIATE:
        mInstructionSet.LAXImmediate();
        break;

      case LAX_ZERO_PAGE:
        mInstructionSet.LAXZeroPage();
        break;

      case LAX_ZERO_PAGE_Y:
        mInstructionSet.LAXZeroPageY();
        break;

      case LAX_ABSOLUTE:
        mInstructionSet.LAXAbsolute();
        break;

      case LAX_ABSOLUTE_Y:
        mInstructionSet.LAXAbsoluteY();
        break;

      case LAX_INDIRECT_X:
        mInstructionSet.LAXIndirectX();
        break;

      case LAX_INDIRECT_Y:
        mInstructionSet.LAXIndirectY();
        break;

      // RLA
      case RLA_ZERO_PAGE:
        mInstructionSet.RLAZeroPage();
        break;

      case RLA_ZERO_PAGE_X:
        mInstructionSet.RLAZeroPageX();
        break;

      case RLA_ABSOLUTE:
        mInstructionSet.RLAAbsolute();
        break;

      case RLA_ABSOLUTE_X:
        mInstructionSet.RLAAbsoluteX();
        break;

      case RLA_ABSOLUTE_Y:
        mInstructionSet.RLAAbsoluteY();
        break;

      case RLA_INDIRECT_X:
        mInstructionSet.RLAIndirectX();
        break;

      case RLA_INDIRECT_Y:
        mInstructionSet.RLAIndirectY();
        break;

      // RRA
      case RRA_ZERO_PAGE:
        mInstructionSet.RRAZeroPage();
        break;

      case RRA_ZERO_PAGE_X:
        mInstructionSet.RRAZeroPageX();
        break;

      case RRA_ABSOLUTE:
        mInstructionSet.RRAAbsolute();
        break;

      case RRA_ABSOLUTE_X:
        mInstructionSet.RRAAbsoluteX();
        break;

      case RRA_ABSOLUTE_Y:
        mInstructionSet.RRAAbsoluteY();
        break;

      case RRA_INDIRECT_X:
        mInstructionSet.RRAIndirectX();
        break;

      case RRA_INDIRECT_Y:
        mInstructionSet.RRAIndirectY();
        break;

      // SAX
      case SAX_ZERO_PAGE:
        mInstructionSet.SAXZeroPage();
        break;

      case SAX_ZERO_PAGE_Y:
        mInstructionSet.SAXZeroPageY();
        break;

      case SAX_ABSOLUTE:
        mInstructionSet.SAXAbsolute();
        break;

      case SAX_INDIRECT_X:
        mInstructionSet.SAXIndirectX();
        break;

      // SHX
      case SHX_ABSOLUTE_Y:
        mInstructionSet.SHXAbsoluteY();
        break;

      // SHY
      case SHY_ABSOLUTE_X:
        mInstructionSet.SHYAbsoluteX();
        break;

      // SLO
      case SLO_ZERO_PAGE:
        mInstructionSet.SLOZeroPage();
        break;

      case SLO_ZERO_PAGE_X:
        mInstructionSet.SLOZeroPageX();
        break;

      case SLO_ABSOLUTE:
        mInstructionSet.SLOAbsolute();
        break;

      case SLO_ABSOLUTE_X:
        mInstructionSet.SLOAbsoluteX();
        break;

      case SLO_ABSOLUTE_Y:
        mInstructionSet.SLOAbsoluteY();
        break;

      case SLO_INDIRECT_X:
        mInstructionSet.SLOIndirectX();
        break;

      case SLO_INDIRECT_Y:
        mInstructionSet.SLOIndirectY();
        break;

      // SRE
      case SRE_ZERO_PAGE:
        mInstructionSet.SREZeroPage();
        break;

      case SRE_ZERO_PAGE_X:
        mInstructionSet.SREZeroPageX();
        break;

      case SRE_ABSOLUTE:
        mInstructionSet.SREAbsolute();
        break;

      case SRE_ABSOLUTE_X:
        mInstructionSet.SREAbsoluteX();
        break;

      case SRE_ABSOLUTE_Y:
        mInstructionSet.SREAbsoluteY();
        break;

      case SRE_INDIRECT_X:
        mInstructionSet.SREIndirectX();
        break;

      case SRE_INDIRECT_Y:
        mInstructionSet.SREIndirectY();
        break;

      // XAA
      case XAA_IMMEDIATE:
        mInstructionSet.XAAImmediate();
        break;

      default:
        mCycle = 0;
        break;
    }
  }
  mCycle++;
}

void CPU::loadState(uint16_t programCounter, uint8_t stackPointer,
                    uint8_t accumulator, uint8_t xIndex, uint8_t yIndex,
                    uint8_t status) {
  mProgramCounter = programCounter;
  mStackPointer = stackPointer;
  mAccumulator = accumulator;
  mXIndex = xIndex;
  mYIndex = yIndex;
  mStatus = status;
}