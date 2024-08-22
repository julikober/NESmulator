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
  ASL_ZERO_PAGE = 0x06,

  ASL_ACCUMULATOR = 0x0A,

  ASL_ABSOLUTE = 0x0E,

  BPL_RELATIVE = 0x10,

  ASL_ZERO_PAGE_X = 0x16,

  CLC_IMPLIED = 0x18,

  ASL_ABSOLUTE_X = 0x1E,

  AND_INDIRECT_X = 0x21,

  BIT_ZERO_PAGE = 0x24,
  AND_ZERO_PAGE = 0x25,

  AND_IMMEDIATE = 0x29,

  BIT_ABSOLUTE = 0x2C,
  AND_ABSOLUTE = 0x2D,

  BMI_RELATIVE = 0x30,
  AND_INDIRECT_Y = 0x31,

  AND_ZERO_PAGE_X = 0x35,

  AND_ABSOLUTE_Y = 0x39,

  AND_ABSOLUTE_X = 0x3D,

  BVC_RELATIVE = 0x50,

  CLI_IMPLIED = 0x58,

  ADC_INDIRECT_X = 0x61,

  ADC_ZERO_PAGE = 0x65,

  ADC_IMMEDIATE = 0x69,

  ADC_ABSOLUTE = 0x6D,

  BVS_RELATIVE = 0x70,
  ADC_INDIRECT_Y = 0x71,

  ADC_ZERO_PAGE_X = 0x75,

  ADC_ABSOLUTE_Y = 0x79,

  ADC_ABSOLUTE_X = 0x7D,

  BCC_RELATIVE = 0x90,

  BCS_RELATIVE = 0xB0,

  CLV_IMPLIED = 0xB8,

  BNE_RELATIVE = 0xD0,

  CLD_IMPLIED = 0xD8,

  BEQ_RELATIVE = 0xF0

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

    // Addressing modes
    void mExecuteImplied(void (InstructionSet::*action)());
    void mExecuteAccumulator(void (InstructionSet::*read)(),
                             void (InstructionSet::*modify)() = nullptr,
                             void (InstructionSet::*write)() = nullptr);
    void mExecuteImmediate(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPage(void (InstructionSet::*read)(),
                          void (InstructionSet::*modify)() = nullptr,
                          void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPageX(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteZeroPageY(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsolute(void (InstructionSet::*read)(),
                          void (InstructionSet::*modify)() = nullptr,
                          void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsoluteX(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteAbsoluteY(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    // void mExecuteIndirect(void (InstructionSet::*read)(),
    //                       void (InstructionSet::*modify)() = nullptr,
    //                       void (InstructionSet::*write)() = nullptr);
    void mExecuteIndirectX(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteIndirectY(void (InstructionSet::*read)(),
                           void (InstructionSet::*modify)() = nullptr,
                           void (InstructionSet::*write)() = nullptr);
    void mExecuteRelative(bool (InstructionSet::*condition)());

    // Execute instruction
    void mExecute(int startCycle, void (InstructionSet::*read)(),
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

    // ORA
    void ORAZeroPage();
    void ORAIndirectX();
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

  // Arithmatic and logical operations affecting status flags
  OperationOutput mSum(uint8_t a, uint8_t b, bool checkCarry = false);
  OperationOutput mAnd(uint8_t a, uint8_t b);
  OperationOutput mOr(uint8_t a, uint8_t b);
  OperationOutput mEor(uint8_t a, uint8_t b);
  OperationOutput mShiftRight(uint8_t a);

 public:
  CPU(Memory& memory)
      : mMemory(memory),
        mInstructionSet(*this),
        mProgramCounter(0),
        mStackPointer(0xFF),
        mAccumulator(0),
        mXIndex(0),
        mYIndex(0),
        mStatus(0),
        mCycle(1) {};
  ~CPU() {};

  void doCycle();

  void dumpRegisters() {  // For debugging purposes only
    printf("PC: %04X SP: %02X A: %02X X: %02X Y: %02X P: ", mProgramCounter,
           mStackPointer, mAccumulator, mXIndex, mYIndex);

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