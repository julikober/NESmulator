#pragma once

#include <cstdint>

#include "memory.hpp"

enum StatusFlag {
  CARRY = 1 << 0,
  ZERO = 1 << 1,
  INTERRUPT_DISABLE = 1 << 2,
  DECIMAL_MODE = 1 << 3,
  BREAK = 1 << 4,
  OVERFLOW = 1 << 6,
  NEGATIVE = 1 << 7
};

enum Instruction {
  BRK = 0x00,
  ORA_INDIRECT_X = 0x01,
  ORA_ZERO_PAGE = 0x05,
  ASL_ZERO_PAGE = 0x06,

  ADC_ZERO_PAGE = 0x65,

  ADC_IMMEDIATE = 0x69,

};

class CPU {
 private:
  class ALU {
   private:
    CPU& mCpu;

   public:
    ALU(CPU& cpu) : mCpu(cpu){};
    uint8_t SUM(uint8_t a, uint8_t b, bool addCarry = false);
    uint8_t AND(uint8_t a, uint8_t b);
    uint8_t OR(uint8_t a, uint8_t b);
    uint8_t EOR(uint8_t a, uint8_t b);
    uint8_t SR(uint8_t a);
  };

  class InstructionSet {
   private:
    CPU& mCpu;

   public:
    InstructionSet(CPU& cpu) : mCpu(cpu){};

    // ADC
    void ADCImmediate();
    void ADCZeroPage();
    // void ADCZeroPageX();
    // void ADCAbsolute();
    // void ADCAbsoluteX();
    // void ADCAbsoluteY();
    // void ADCIndirectX();
    // void ADCIndirectY();

    // ASL
    void ASLZeroPage();

    // ORA
    void ORAZeroPage();
    void ORAIndirectX();
  };

  Memory& mMemory;
  ALU mAlu;
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

  // Getters and setters for status flags
  inline void mSetFlag(uint8_t flags) { mStatus = flags; };
  inline void mClearFlag(uint8_t flags) { mStatus &= ~flags; };
  inline bool mCheckFlag(uint8_t flags) { return mStatus & flags; };

  // Read and write memory

  inline uint8_t mReadMemory() { return mMemory.read(mAddress); }
  inline void mWriteMemory(uint8_t value) {
    mMemory.write(mAddress, value);
  }

 public:
  CPU(Memory& memory)
      : mMemory(memory),
        mAlu(*this),
        mInstructionSet(*this),
        mProgramCounter(0),
        mStackPointer(0xFF),
        mAccumulator(0),
        mXIndex(0),
        mYIndex(0),
        mStatus(0),
        mCycle(1){};
  ~CPU(){};

  void do_cycle();
};