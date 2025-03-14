#include "cpu/cpu.hpp"

CPU::CPU(Mapper** mapper, PPU* ppu)
    : mInstructionSet(*this),
      mMemory(new CPUMemoryMap(mapper, ppu)),
      mProgramCounter(0xFFFC),
      mStackPointer(0xFD),
      mAccumulator(0),
      mXIndex(0),
      mYIndex(0),
      mStatus(INTERRUPT_DISABLE),
      mCycle(0) {};

CPU::~CPU() { delete mMemory; }
CPU::InstructionSet::InstructionSet(CPU& cpu) : mCpu(cpu) {};

void CPU::mFetchInstruction() {
  mAddress = mProgramCounter;
  mProgramCounter++;

  mInstruction = (Instruction)mReadMemory();
}

uint8_t CPU::mReadMemory() { return mMemory->read(mAddress); }
void CPU::mWriteMemory(uint8_t value) { mMemory->write(mAddress, value); }

void CPU::mPushStack(uint8_t value) {
  mAddress = mStackPointer + M_STACK_OFFSET;

  mWriteMemory(value);
}

uint8_t CPU::mPopStack() {
  mAddress = mStackPointer + M_STACK_OFFSET;

  return mReadMemory();
}

void CPU::mUpdateZeroAndNegative(uint8_t value) {
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
  mCycle++;

  if (mNMI) {
    mDoInterrupt(NMI);

    return;
  }

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
      case U_AHX_ABSOLUTE_Y:
        mInstructionSet.AHXAbsoluteY();
        break;

      case U_AHX_INDIRECT_Y:
        mInstructionSet.AHXIndirectY();
        break;

      // ALR
      case U_ALR_IMMEDIATE:
        mInstructionSet.ALRImmediate();
        break;

      // ANC
      case U_ANC_IMMEDIATE_1:
        mInstructionSet.ANCImmediate();
        break;

      case U_ANC_IMMEDIATE_2:
        mInstructionSet.ANCImmediate();
        break;

      // ARR
      case U_ARR_IMMEDIATE:
        mInstructionSet.ARRImmediate();
        break;

      // AXS
      case U_AXS_IMMEDIATE:
        mInstructionSet.AXSImmediate();
        break;

      // DCP
      case U_DCP_ZERO_PAGE:
        mInstructionSet.DCPZeroPage();
        break;

      case U_DCP_ZERO_PAGE_X:
        mInstructionSet.DCPZeroPageX();
        break;

      case U_DCP_ABSOLUTE:
        mInstructionSet.DCPAbsolute();
        break;

      case U_DCP_ABSOLUTE_X:
        mInstructionSet.DCPAbsoluteX();
        break;

      case U_DCP_ABSOLUTE_Y:
        mInstructionSet.DCPAbsoluteY();
        break;

      case U_DCP_INDIRECT_X:
        mInstructionSet.DCPIndirectX();
        break;

      case U_DCP_INDIRECT_Y:
        mInstructionSet.DCPIndirectY();
        break;

      // ISC
      case U_ISC_ZERO_PAGE:
        mInstructionSet.ISCZeroPage();
        break;

      case U_ISC_ZERO_PAGE_X:
        mInstructionSet.ISCZeroPageX();
        break;

      case U_ISC_ABSOLUTE:
        mInstructionSet.ISCAbsolute();
        break;

      case U_ISC_ABSOLUTE_X:
        mInstructionSet.ISCAbsoluteX();
        break;

      case U_ISC_ABSOLUTE_Y:
        mInstructionSet.ISCAbsoluteY();
        break;

      case U_ISC_INDIRECT_X:
        mInstructionSet.ISCIndirectX();
        break;

      case U_ISC_INDIRECT_Y:
        mInstructionSet.ISCIndirectY();
        break;

      // JAM
      case U_JAM_1:
        mInstructionSet.JAM();
        break;

      case U_JAM_2:
        mInstructionSet.JAM();
        break;

      case U_JAM_3:
        mInstructionSet.JAM();
        break;

      case U_JAM_4:
        mInstructionSet.JAM();
        break;

      case U_JAM_5:
        mInstructionSet.JAM();

      case U_JAM_6:
        mInstructionSet.JAM();
        break;

      case U_JAM_7:
        mInstructionSet.JAM();
        break;

      case U_JAM_8:
        mInstructionSet.JAM();
        break;

      case U_JAM_9:
        mInstructionSet.JAM();
        break;

      case U_JAM_10:
        mInstructionSet.JAM();
        break;

      case U_JAM_11:
        mInstructionSet.JAM();
        break;

      case U_JAM_12:
        mInstructionSet.JAM();
        break;

      // LAS
      case U_LAS_ABSOLUTE_Y:
        mInstructionSet.LASAbsoluteY();
        break;

      // LAX
      case U_LAX_IMMEDIATE:
        mInstructionSet.LAXImmediate();
        break;

      case U_LAX_ZERO_PAGE:
        mInstructionSet.LAXZeroPage();
        break;

      case U_LAX_ZERO_PAGE_Y:
        mInstructionSet.LAXZeroPageY();
        break;

      case U_LAX_ABSOLUTE:
        mInstructionSet.LAXAbsolute();
        break;

      case U_LAX_ABSOLUTE_Y:
        mInstructionSet.LAXAbsoluteY();
        break;

      case U_LAX_INDIRECT_X:
        mInstructionSet.LAXIndirectX();
        break;

      case U_LAX_INDIRECT_Y:
        mInstructionSet.LAXIndirectY();
        break;

      // NOP (unofficial)
      case U_NOP_IMPLIED_1:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMPLIED_2:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMPLIED_3:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMPLIED_4:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMPLIED_5:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMPLIED_6:
        mInstructionSet.NOPImplied();
        break;

      case U_NOP_IMMEDIATE_1:
        mInstructionSet.NOPImmediate();
        break;

      case U_NOP_IMMEDIATE_2:
        mInstructionSet.NOPImmediate();
        break;

      case U_NOP_IMMEDIATE_3:
        mInstructionSet.NOPImmediate();
        break;

      case U_NOP_IMMEDIATE_4:
        mInstructionSet.NOPImmediate();
        break;

      case U_NOP_IMMEDIATE_5:
        mInstructionSet.NOPImmediate();
        break;

      case U_NOP_ZERO_PAGE_1:
        mInstructionSet.NOPZeroPage();
        break;

      case U_NOP_ZERO_PAGE_2:
        mInstructionSet.NOPZeroPage();
        break;

      case U_NOP_ZERO_PAGE_3:
        mInstructionSet.NOPZeroPage();
        break;

      case U_NOP_ZERO_PAGE_X_1:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ZERO_PAGE_X_2:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ZERO_PAGE_X_3:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ZERO_PAGE_X_4:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ZERO_PAGE_X_5:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ZERO_PAGE_X_6:
        mInstructionSet.NOPZeroPageX();
        break;

      case U_NOP_ABSOLUTE:
        mInstructionSet.NOPAbsolute();
        break;

      case U_NOP_ABSOLUTE_X_1:
        mInstructionSet.NOPAbsoluteX();
        break;

      case U_NOP_ABSOLUTE_X_2:
        mInstructionSet.NOPAbsoluteX();
        break;

      case U_NOP_ABSOLUTE_X_3:
        mInstructionSet.NOPAbsoluteX();
        break;

      case U_NOP_ABSOLUTE_X_4:
        mInstructionSet.NOPAbsoluteX();
        break;

      case U_NOP_ABSOLUTE_X_5:
        mInstructionSet.NOPAbsoluteX();
        break;

      case U_NOP_ABSOLUTE_X_6:
        mInstructionSet.NOPAbsoluteX();
        break;

      // RLA
      case U_RLA_ZERO_PAGE:
        mInstructionSet.RLAZeroPage();
        break;

      case U_RLA_ZERO_PAGE_X:
        mInstructionSet.RLAZeroPageX();
        break;

      case U_RLA_ABSOLUTE:
        mInstructionSet.RLAAbsolute();
        break;

      case U_RLA_ABSOLUTE_X:
        mInstructionSet.RLAAbsoluteX();
        break;

      case U_RLA_ABSOLUTE_Y:
        mInstructionSet.RLAAbsoluteY();
        break;

      case U_RLA_INDIRECT_X:
        mInstructionSet.RLAIndirectX();
        break;

      case U_RLA_INDIRECT_Y:
        mInstructionSet.RLAIndirectY();
        break;

      // RRA
      case U_RRA_ZERO_PAGE:
        mInstructionSet.RRAZeroPage();
        break;

      case U_RRA_ZERO_PAGE_X:
        mInstructionSet.RRAZeroPageX();
        break;

      case U_RRA_ABSOLUTE:
        mInstructionSet.RRAAbsolute();
        break;

      case U_RRA_ABSOLUTE_X:
        mInstructionSet.RRAAbsoluteX();
        break;

      case U_RRA_ABSOLUTE_Y:
        mInstructionSet.RRAAbsoluteY();
        break;

      case U_RRA_INDIRECT_X:
        mInstructionSet.RRAIndirectX();
        break;

      case U_RRA_INDIRECT_Y:
        mInstructionSet.RRAIndirectY();
        break;

      // SAX
      case U_SAX_ZERO_PAGE:
        mInstructionSet.SAXZeroPage();
        break;

      case U_SAX_ZERO_PAGE_Y:
        mInstructionSet.SAXZeroPageY();
        break;

      case U_SAX_ABSOLUTE:
        mInstructionSet.SAXAbsolute();
        break;

      case U_SAX_INDIRECT_X:
        mInstructionSet.SAXIndirectX();
        break;

      // SHX
      case U_SHX_ABSOLUTE_Y:
        mInstructionSet.SHXAbsoluteY();
        break;

      // SHY
      case U_SHY_ABSOLUTE_X:
        mInstructionSet.SHYAbsoluteX();
        break;

      // SLO
      case U_SLO_ZERO_PAGE:
        mInstructionSet.SLOZeroPage();
        break;

      case U_SLO_ZERO_PAGE_X:
        mInstructionSet.SLOZeroPageX();
        break;

      case U_SLO_ABSOLUTE:
        mInstructionSet.SLOAbsolute();
        break;

      case U_SLO_ABSOLUTE_X:
        mInstructionSet.SLOAbsoluteX();
        break;

      case U_SLO_ABSOLUTE_Y:
        mInstructionSet.SLOAbsoluteY();
        break;

      case U_SLO_INDIRECT_X:
        mInstructionSet.SLOIndirectX();
        break;

      case U_SLO_INDIRECT_Y:
        mInstructionSet.SLOIndirectY();
        break;

      // SRE
      case U_SRE_ZERO_PAGE:
        mInstructionSet.SREZeroPage();
        break;

      case U_SRE_ZERO_PAGE_X:
        mInstructionSet.SREZeroPageX();
        break;

      case U_SRE_ABSOLUTE:
        mInstructionSet.SREAbsolute();
        break;

      case U_SRE_ABSOLUTE_X:
        mInstructionSet.SREAbsoluteX();
        break;

      case U_SRE_ABSOLUTE_Y:
        mInstructionSet.SREAbsoluteY();
        break;

      case U_SRE_INDIRECT_X:
        mInstructionSet.SREIndirectX();
        break;

      case U_SRE_INDIRECT_Y:
        mInstructionSet.SREIndirectY();
        break;

      // TAS
      case U_TAS_ABSOLUTE_Y:
        mInstructionSet.TASAbsoluteY();
        break;

      // SBC (unofficial)
      case U_SBC_IMMEDIATE:
        mInstructionSet.SBCImmediate();
        break;

      // XAA
      case U_XAA_IMMEDIATE:
        mInstructionSet.XAAImmediate();
        break;

      default:
        mCycle = 0;
        break;
    }
  }
}
