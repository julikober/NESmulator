#pragma once

#include <cstdint>

#include "memory.hpp"

enum StatusFlag {
  CARRY = 1 << 0,
  ZERO = 1 << 1,
  INTERRUPT_DISABLE = 1 << 2,
  DECIMAL = 1 << 3,  // Not used in NES
  BREAK = 1 << 4,
  OVERFLOW = 1 << 6,
  NEGATIVE = 1 << 7
};

enum Instruction {
  BRK_IMPLIED = 0x00,
  ORA_INDIRECT_X = 0x01,

  ORA_ZERO_PAGE = 0x05,
  ASL_ZERO_PAGE = 0x06,

  PHP_IMPLIED = 0x08,
  ORA_IMMEDIATE = 0x09,
  ASL_ACCUMULATOR = 0x0A,

  ORA_ABSOLUTE = 0x0D,
  ASL_ABSOLUTE = 0x0E,

  BPL_RELATIVE = 0x10,
  ORA_INDIRECT_Y = 0x11,

  ORA_ZERO_PAGE_X = 0x15,
  ASL_ZERO_PAGE_X = 0x16,

  CLC_IMPLIED = 0x18,
  ORA_ABSOLUTE_Y = 0x19,

  ORA_ABSOLUTE_X = 0x1D,
  ASL_ABSOLUTE_X = 0x1E,

  JSR_ABSOLUTE = 0x20,
  AND_INDIRECT_X = 0x21,

  BIT_ZERO_PAGE = 0x24,
  AND_ZERO_PAGE = 0x25,
  ROL_ZERO_PAGE = 0x26,

  PLP_IMPLIED = 0x28,
  AND_IMMEDIATE = 0x29,
  ROL_ACCUMULATOR = 0x2A,

  BIT_ABSOLUTE = 0x2C,
  AND_ABSOLUTE = 0x2D,
  ROL_ABSOLUTE = 0x2E,

  BMI_RELATIVE = 0x30,
  AND_INDIRECT_Y = 0x31,

  AND_ZERO_PAGE_X = 0x35,
  ROL_ZERO_PAGE_X = 0x36,

  SEC_IMPLIED = 0x38,
  AND_ABSOLUTE_Y = 0x39,

  AND_ABSOLUTE_X = 0x3D,
  ROL_ABSOLUTE_X = 0x3E,

  RTI_IMPLIED = 0x40,
  EOR_INDIRECT_X = 0x41,

  EOR_ZERO_PAGE = 0x45,
  LSR_ZERO_PAGE = 0x46,

  PHA_IMPLIED = 0x48,
  EOR_IMMEDIATE = 0x49,
  LSR_ACCUMULATOR = 0x4A,

  JMP_ABSOLUTE = 0x4C,
  EOR_ABSOLUTE = 0x4D,
  LSR_ABSOLUTE = 0x4E,

  BVC_RELATIVE = 0x50,
  EOR_INDIRECT_Y = 0x51,

  EOR_ZERO_PAGE_X = 0x55,
  LSR_ZERO_PAGE_X = 0x56,

  CLI_IMPLIED = 0x58,
  EOR_ABSOLUTE_Y = 0x59,

  EOR_ABSOLUTE_X = 0x5D,
  LSR_ABSOLUTE_X = 0x5E,

  RTS_IMPLIED = 0x60,
  ADC_INDIRECT_X = 0x61,

  ADC_ZERO_PAGE = 0x65,
  ROR_ZERO_PAGE = 0x66,

  PLA_IMPLIED = 0x68,
  ADC_IMMEDIATE = 0x69,
  ROR_ACCUMULATOR = 0x6A,

  JMP_INDIRECT = 0x6C,
  ADC_ABSOLUTE = 0x6D,
  ROR_ABSOLUTE = 0x6E,

  BVS_RELATIVE = 0x70,
  ADC_INDIRECT_Y = 0x71,

  ADC_ZERO_PAGE_X = 0x75,
  ROR_ZERO_PAGE_X = 0x76,

  SEI_IMPLIED = 0x78,
  ADC_ABSOLUTE_Y = 0x79,

  ADC_ABSOLUTE_X = 0x7D,
  ROR_ABSOLUTE_X = 0x7E,

  STA_INDIRECT_X = 0x81,

  STY_ZERO_PAGE = 0x84,
  STA_ZERO_PAGE = 0x85,
  STX_ZERO_PAGE = 0x86,

  DEY_IMPLIED = 0x88,

  TXA_IMPLIED = 0x8A,

  STY_ABSOLUTE = 0x8C,
  STA_ABSOLUTE = 0x8D,
  STX_ABSOLUTE = 0x8E,

  BCC_RELATIVE = 0x90,
  STA_INDIRECT_Y = 0x91,

  STY_ZERO_PAGE_X = 0x94,
  STA_ZERO_PAGE_X = 0x95,
  STX_ZERO_PAGE_Y = 0x96,

  TYA_IMPLIED = 0x98,
  STA_ABSOLUTE_Y = 0x99,
  TXS_IMPLIED = 0x9A,

  STA_ABSOLUTE_X = 0x9D,

  LDY_IMMEDIATE = 0xA0,
  LDA_INDIRECT_X = 0xA1,
  LDX_IMMEDIATE = 0xA2,

  LDY_ZERO_PAGE = 0xA4,
  LDA_ZERO_PAGE = 0xA5,
  LDX_ZERO_PAGE = 0xA6,

  TAY_IMPLIED = 0xA8,
  LDA_IMMEDIATE = 0xA9,
  TAX_IMPLIED = 0xAA,

  LDY_ABSOLUTE = 0xAC,
  LDA_ABSOLUTE = 0xAD,
  LDX_ABSOLUTE = 0xAE,

  BCS_RELATIVE = 0xB0,
  LDA_INDIRECT_Y = 0xB1,

  LDY_ZERO_PAGE_X = 0xB4,
  LDA_ZERO_PAGE_X = 0xB5,
  LDX_ZERO_PAGE_Y = 0xB6,

  CLV_IMPLIED = 0xB8,
  LDA_ABSOLUTE_Y = 0xB9,
  TSX_IMPLIED = 0xBA,

  LDY_ABSOLUTE_X = 0xBC,
  LDA_ABSOLUTE_X = 0xBD,
  LDX_ABSOLUTE_Y = 0xBE,

  CPY_IMMEDIATE = 0xC0,
  CMP_INDIRECT_X = 0xC1,

  CPY_ZERO_PAGE = 0xC4,
  CMP_ZERO_PAGE = 0xC5,
  DEC_ZERO_PAGE = 0xC6,

  INY_IMPLIED = 0xC8,
  CMP_IMMEDIATE = 0xC9,
  DEX_IMPLIED = 0xCA,

  CPY_ABSOLUTE = 0xCC,
  CMP_ABSOLUTE = 0xCD,
  DEC_ABSOLUTE = 0xCE,

  BNE_RELATIVE = 0xD0,
  CMP_INDIRECT_Y = 0xD1,

  CMP_ZERO_PAGE_X = 0xD5,
  DEC_ZERO_PAGE_X = 0xD6,

  CLD_IMPLIED = 0xD8,
  CMP_ABSOLUTE_Y = 0xD9,

  CMP_ABSOLUTE_X = 0xDD,
  DEC_ABSOLUTE_X = 0xDE,

  CPX_IMMEDIATE = 0xE0,
  SBC_INDIRECT_X = 0xE1,

  CPX_ZERO_PAGE = 0xE4,
  SBC_ZERO_PAGE = 0xE5,
  INC_ZERO_PAGE = 0xE6,

  INX_IMPLIED = 0xE8,
  SBC_IMMEDIATE = 0xE9,
  NOP_IMPLIED = 0xEA,

  CPX_ABSOLUTE = 0xEC,
  SBC_ABSOLUTE = 0xED,
  INC_ABSOLUTE = 0xEE,

  BEQ_RELATIVE = 0xF0,
  SBC_INDIRECT_Y = 0xF1,

  SBC_ZERO_PAGE_X = 0xF5,
  INC_ZERO_PAGE_X = 0xF6,

  SED_IMPLIED = 0xF8,
  SBC_ABSOLUTE_Y = 0xF9,

  SBC_ABSOLUTE_X = 0xFD,
  INC_ABSOLUTE_X = 0xFE,

};

class CPU {
 private:
  class InstructionSet {
   private:
    CPU& mCpu;

    // ADC
    void mReadADC();

    // AND
    void mReadAND();

    // ASL
    void mReadASL();
    void mModifyASL();
    void mWriteASL();
    void mReadASLAccumulator();

    // BCC
    bool mCheckBCC();

    // BCS
    bool mCheckBCS();

    // BEQ
    bool mCheckBEQ();

    // BIT
    void mReadBIT();

    // BMI
    bool mCheckBMI();

    // BNE
    bool mCheckBNE();

    // BPL
    bool mCheckBPL();

    // BRK does not use any addressing mode functions. It is a special case

    // BVC
    bool mCheckBVC();

    // BVS
    bool mCheckBVS();

    // CLC
    void mExecuteCLC();

    // CLD
    void mExecuteCLD();

    // CLI
    void mExecuteCLI();

    // CLV
    void mExecuteCLV();

    // CMP
    void mReadCMP();

    // CPX
    void mReadCPX();

    // CPY
    void mReadCPY();

    // DEC
    void mReadDEC();
    void mModifyDEC();
    void mWriteDEC();

    // DEX
    void mExecuteDEX();

    // DEY
    void mExecuteDEY();

    // EOR
    void mReadEOR();

    // INC
    void mReadINC();
    void mModifyINC();
    void mWriteINC();

    // INX
    void mExecuteINX();

    // INY
    void mExecuteINY();

    // JMP does not use any addressing mode functions. It is a special case

    // JSR does not use any addressing mode functions. It is a special case

    // LDA
    void mReadLDA();

    // LDX
    void mReadLDX();

    // LDY
    void mReadLDY();

    // LSR
    void mReadLSR();
    void mModifyLSR();
    void mWriteLSR();
    void mReadLSRAccumulator();

    // NOP
    void mExecuteNOP();

    // ORA
    void mReadORA();

    // PHA does not use any addressing mode functions. It is a special case

    // PHP does not use any addressing mode functions. It is a special case

    // PLA does not use any addressing mode functions. It is a special case

    // PLP does not use any addressing mode functions. It is a special case

    // ROL
    void mReadROL();
    void mModifyROL();
    void mWriteROL();
    void mReadROLAccumulator();

    // ROR
    void mReadROR();
    void mModifyROR();
    void mWriteROR();
    void mReadRORAccumulator();

    // RTI does not use any addressing mode functions. It is a special case

    // RTS does not use any addressing mode functions. It is a special case

    // SBC
    void mReadSBC();

    // SEC
    void mExecuteSEC();

    // SED
    void mExecuteSED();

    // SEI
    void mExecuteSEI();

    // STA
    void mWriteSTA();

    // STX
    void mWriteSTX();

    // STY
    void mWriteSTY();

    // TAX
    void mExecuteTAX();

    // TAY
    void mExecuteTAY();

    // TSX
    void mExecuteTSX();

    // TXA
    void mExecuteTXA();

    // TXS
    void mExecuteTXS();

    // TYA
    void mExecuteTYA();

    // Addressing modes
    void mExecuteImplied(void (InstructionSet::*action)());
    void mExecuteAccumulator(void (InstructionSet::*read)() = nullptr,
                             void (InstructionSet::*modify)() = nullptr,
                             void (InstructionSet::*write)() = nullptr);
    void mExecuteImmediate(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPage(void (InstructionSet::*read)() = nullptr,
                          void (InstructionSet::*modify)() = nullptr,
                          void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPageX(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPageY(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsolute(void (InstructionSet::*read)() = nullptr,
                          void (InstructionSet::*modify)() = nullptr,
                          void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsoluteX(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsoluteY(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    // void mExecuteIndirect(void (InstructionSet::*read)() =  nullptr,
    //                       void (InstructionSet::*modify)() = nullptr,
    //                       void (InstructionSet::*write)() = nullptr);
    void mExecuteIndirectX(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteIndirectY(void (InstructionSet::*read)() = nullptr,
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteRelative(bool (InstructionSet::*condition)());

    // Execute instruction
    void mExecute(int startCycle, void (InstructionSet::*read)() = nullptr,
                  void (InstructionSet::*modify)() = nullptr,
                  void (InstructionSet::*write)() = nullptr);

   public:
    InstructionSet(CPU& cpu) : mCpu(cpu) {};

    // ADC
    void ADCImmediate();
    void ADCZeroPage();
    void ADCZeroPageX();
    void ADCAbsolute();
    void ADCAbsoluteX();
    void ADCAbsoluteY();
    void ADCIndirectX();
    void ADCIndirectY();

    // AND
    void ANDImmediate();
    void ANDZeroPage();
    void ANDZeroPageX();
    void ANDAbsolute();
    void ANDAbsoluteX();
    void ANDAbsoluteY();
    void ANDIndirectX();
    void ANDIndirectY();

    // ASL
    void ASLAccumulator();
    void ASLZeroPage();
    void ASLZeroPageX();
    void ASLAbsolute();
    void ASLAbsoluteX();

    // BCC
    void BCCRelative();

    // BCS
    void BCSRelative();

    // BEQ
    void BEQRelative();

    // BIT
    void BITZeroPage();
    void BITAbsolute();

    // BMI
    void BMIRelative();

    // BNE
    void BNERelative();

    // BPL
    void BPLRelative();

    // BRK
    void BRKImplied();

    // BVC
    void BVCRelative();

    // BVS
    void BVSRelative();

    // CLC
    void CLCImplied();

    // CLD
    void CLDImplied();

    // CLI
    void CLIImplied();

    // CLV
    void CLVImplied();

    // CMP
    void CMPImmediate();
    void CMPZeroPage();
    void CMPZeroPageX();
    void CMPAbsolute();
    void CMPAbsoluteX();
    void CMPAbsoluteY();
    void CMPIndirectX();
    void CMPIndirectY();

    // CPX
    void CPXImmediate();
    void CPXZeroPage();
    void CPXAbsolute();

    // CPY
    void CPYImmediate();
    void CPYZeroPage();
    void CPYAbsolute();

    // DEC
    void DECZeroPage();
    void DECZeroPageX();
    void DECAbsolute();
    void DECAbsoluteX();

    // DEX
    void DEXImplied();

    // DEY
    void DEYImplied();

    // EOR
    void EORImmediate();
    void EORZeroPage();
    void EORZeroPageX();
    void EORAbsolute();
    void EORAbsoluteX();
    void EORAbsoluteY();
    void EORIndirectX();
    void EORIndirectY();

    // INC
    void INCZeroPage();
    void INCZeroPageX();
    void INCAbsolute();
    void INCAbsoluteX();

    // INX
    void INXImplied();

    // INY
    void INYImplied();

    // JMP
    void JMPAbsolute();
    void JMPIndirect();

    // JSR
    void JSRAbsolute();

    // LDA
    void LDAImmediate();
    void LDAZeroPage();
    void LDAZeroPageX();
    void LDAAbsolute();
    void LDAAbsoluteX();
    void LDAAbsoluteY();
    void LDAIndirectX();
    void LDAIndirectY();

    // LDX
    void LDXImmediate();
    void LDXZeroPage();
    void LDXZeroPageY();
    void LDXAbsolute();
    void LDXAbsoluteY();

    // LDY
    void LDYImmediate();
    void LDYZeroPage();
    void LDYZeroPageX();
    void LDYAbsolute();
    void LDYAbsoluteX();

    // LSR
    void LSRAccumulator();
    void LSRZeroPage();
    void LSRZeroPageX();
    void LSRAbsolute();
    void LSRAbsoluteX();

    // NOP
    void NOPImplied();

    // ORA
    void ORAImmediate();
    void ORAZeroPage();
    void ORAZeroPageX();
    void ORAAbsolute();
    void ORAAbsoluteX();
    void ORAAbsoluteY();
    void ORAIndirectX();
    void ORAIndirectY();

    // PHA
    void PHAImplied();

    // PHP
    void PHPImplied();

    // PLA
    void PLAImplied();

    // PLP
    void PLPImplied();

    // ROL
    void ROLAccumulator();
    void ROLZeroPage();
    void ROLZeroPageX();
    void ROLAbsolute();
    void ROLAbsoluteX();

    // ROR
    void RORAccumulator();
    void RORZeroPage();
    void RORZeroPageX();
    void RORAbsolute();
    void RORAbsoluteX();

    // RTI
    void RTIImplied();

    // RTS
    void RTSImplied();

    // SBC
    void SBCImmediate();
    void SBCZeroPage();
    void SBCZeroPageX();
    void SBCAbsolute();
    void SBCAbsoluteX();
    void SBCAbsoluteY();
    void SBCIndirectX();
    void SBCIndirectY();

    // SEC
    void SECImplied();

    // SED
    void SEDImplied();

    // SEI
    void SEIImplied();

    // STA
    void STAZeroPage();
    void STAZeroPageX();
    void STAAbsolute();
    void STAAbsoluteX();
    void STAAbsoluteY();
    void STAIndirectX();
    void STAIndirectY();

    // STX
    void STXZeroPage();
    void STXZeroPageY();
    void STXAbsolute();

    // STY
    void STYZeroPage();
    void STYZeroPageX();
    void STYAbsolute();

    // TAX
    void TAXImplied();

    // TAY
    void TAYImplied();

    // TSX
    void TSXImplied();

    // TXA
    void TXAImplied();

    // TXS
    void TXSImplied();

    // TYA
    void TYAImplied();
  };

  Memory& mMemory;
  InstructionSet mInstructionSet;

  // General purpose registers
  uint16_t mProgramCounter;
  uint8_t mStackPointer;
  uint8_t mAccumulator;
  uint8_t mXIndex;
  uint8_t mYIndex;
  uint8_t mStatus;

  // Stack offset
  static const uint8_t M_STACK_OFFSET = 0x0100;

  // Other registers and abstractions
  Instruction mInstruction;
  uint16_t mAddress;
  uint8_t mBuffer;

  uint8_t mCycle;

  void mFetchInstruction();

  // Getters and setters for program counter high and low bytes
  inline uint8_t mGetProgramCounterHigh() { return mProgramCounter >> 8; }
  inline uint8_t mGetProgramCounterLow() { return mProgramCounter & 0xFF; }
  inline void mSetProgramCounterHigh(uint8_t value) {
    mProgramCounter = (mProgramCounter & 0x00FF) | (value << 8);
  }
  inline void mSetProgramCounterLow(uint8_t value) {
    mProgramCounter = (mProgramCounter & 0xFF00) | value;
  }

  // Getters and setters for address high and low bytes
  inline uint8_t mGetAddressHigh() { return mAddress >> 8; }
  inline uint8_t mGetAddressLow() { return mAddress & 0xFF; }
  inline void mSetAddressHigh(uint8_t value) {
    mAddress = (mAddress & 0x00FF) | (value << 8);
  }
  inline void mSetAddressLow(uint8_t value) {
    mAddress = (mAddress & 0xFF00) | value;
  }

  // Read and write memory
  inline uint8_t mReadMemory() { return mMemory.read(mAddress); }
  inline void mWriteMemory(uint8_t value) { mMemory.write(mAddress, value); }

  void mPushStack(uint8_t value);
  uint8_t mPopStack();

  // Getters and setters for status flags
  inline void mSetFlag(uint8_t flags) { mStatus |= flags; };
  inline void mClearFlag(uint8_t flags) { mStatus &= ~flags; };
  inline bool mCheckFlag(uint8_t flags) { return mStatus & flags; };

  // Method for automatically setting or clearing zero and negative flags
  void mSetZeroAndNegative(uint8_t value);

  struct OperationOutput {
    uint8_t value;
    bool overflow;
    bool carry;
  };

  // Arithmetic and logical operations affecting status flags
  OperationOutput mSum(uint8_t a, uint8_t b, bool c = 0);
  OperationOutput mAnd(uint8_t a, uint8_t b);
  OperationOutput mOr(uint8_t a, uint8_t b);
  OperationOutput mEor(uint8_t a, uint8_t b);
  OperationOutput mShiftRight(uint8_t a);

 public:
  CPU(Memory& memory)
      : mMemory(memory),
        mInstructionSet(*this),
        mProgramCounter(0x400),
        mStackPointer(0xFF),
        mAccumulator(0),
        mXIndex(0),
        mYIndex(0),
        mStatus(INTERRUPT_DISABLE),
        mCycle(1) {};
  ~CPU() {};

  void doCycle();

  void dumpRegisters() {  // For debugging purposes only
    printf("PC: %04X Instruction: %02X Cycle: %d SP: %02X A: %02X X: %02X Y: %02X P: ",
           mProgramCounter, mInstruction, mCycle, mStackPointer, mAccumulator, mXIndex,
           mYIndex);

    if (mCheckFlag(NEGATIVE)) {
      printf("N");
    } else {
      printf("n");
    }

    if (mCheckFlag(OVERFLOW)) {
      printf("V");
    } else {
      printf("v");
    }

    printf("-");

    if (mCheckFlag(BREAK)) {
      printf("B");
    } else {
      printf("b");
    }

    printf("d");

    if (mCheckFlag(INTERRUPT_DISABLE)) {
      printf("I");
    } else {
      printf("i");
    }

    if (mCheckFlag(ZERO)) {
      printf("Z");
    } else {
      printf("z");
    }

    if (mCheckFlag(CARRY)) {
      printf("C");
    } else {
      printf("c");
    }

    printf(" Address: %04X ", mAddress);

    printf("\n");
  }
};