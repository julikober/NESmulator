#pragma once

#include <cstdint>

#include "./memory/memorymap.hpp"
#include "memory/exceptions.hpp"

#define SCANLINES 262
#define PIXELS 341

enum PPUCTRLFlag {
  PPUCTRL_NAMETABLE = 1 | 1 << 1,
  PPUCTRL_VRAM_INCREMENT = 1 << 2,
  PPUCTRL_SPRITE_TABLE = 1 << 3,
  PPUCTRL_BACKGROUND_TABLE = 1 << 4,
  PPUCTRL_SPRITE_SIZE = 1 << 5,
  PPUCTRL_MASTER_SLAVE = 1 << 6,
  PPUCTRL_NMI = 1 << 7
};

enum PPUSTATUSFlag {
  PPUSTATUS_SPRITE_OVERFLOW = 1 << 5,
  PPUSTATUS_SPRITE_ZERO_HIT = 1 << 6,
  PPUSTATUS_VBLANK = 1 << 7
};

enum VRAMAddrFlag {
  VRAMADDR_COARSE_X = 0b000000000001111,
  VRAMADDR_COARSE_Y = 0b000000111110000,
  VRAMADDR_NAMETABLE = 0b000001000000000,
  VRAMADDR_FINE_Y = 0b011110000000000,
};

class PPU {
 private:
  uint16_t mPosH;
  uint16_t mPosV;

  // Registers
  uint8_t mPPUCTRL;
  uint8_t mPPUMASK;
  uint8_t mPPUSTATUS;
  uint8_t mOAMADDR;
  uint8_t mOAMDATA;
  uint8_t mPPUSCROLL;
  unsigned int mPPUADDR : 14;
  uint8_t mPPUDATA;
  uint8_t mOAMDMA;

  uint8_t mPPUDATAReadBuffer;

  struct RegisterAccess {
    AccessType mPPUCTRL;
    AccessType mPPUMASK;
    AccessType mPPUSTATUS;
    AccessType mOAMADDR;
    AccessType mOAMDATA;
    AccessType mPPUSCROLL;
    AccessType mPPUADDR;
    AccessType mPPUDATA;
    AccessType mOAMDMA;
  } mRegisterAccess;

  // Internal registers
  unsigned int mV : 15;
  unsigned int mT : 15;
  unsigned int mX : 3;
  unsigned int mW : 1;

  // Latches
  uint8_t mNameTableData;
  uint8_t mAttributeData;
  uint8_t mLowTileData;
  uint8_t mHighTileData;

  // Shift registers
  uint16_t mTileShiftLow;
  uint16_t mTileShiftHigh;

  uint16_t mAttributeShiftLow;
  uint16_t mAttributeShiftHigh;

  // OAM
  std::array<uint8_t, 256> mOAM;
  std::array<uint8_t, 32> mSecOAM;

  // Sprite evaluation
  uint8_t mSpriteN;
  uint8_t mSpriteM;

  uint8_t mSecOAMSpriteCount;
  bool mSpriteInRange;
  bool mSpriteEvalFinished;

  struct Sprite {
    uint8_t y;
    uint8_t tile;
    uint8_t attribute;
    uint8_t x;
  } mCurrentSprite;

  struct SpriteOutput {
    uint8_t tileLow;
    uint8_t tileHigh;
    uint8_t attribute;
    uint8_t x;
  };

  struct BackgroundPixel {
    unsigned int color : 2;
    unsigned int palette : 2;
  };

  struct SpritePixel {
    unsigned int color : 2;
    unsigned int palette : 2;
    unsigned int priority : 1;
  };

  struct MergedPixel {
    unsigned int color : 2;
    unsigned int palette : 2;
    enum Type { BACKGROUND, SPRITE } type;
  };

  std::array<SpriteOutput, 8> mSpriteOutputs;

  // Name Tables
  NameTablesMemory mNameTableMemory;

  // Memory
  PPUMemoryMap mMemory;

  // Internal register methods
  void mClearW();
  void mFlipW();

  // Background rendering
  uint16_t mGetBaseNameTableAddress();
  uint16_t mGetAttributeTableAddress();
  uint16_t mGetBasePatternTableAddress();

  uint8_t mGetCoarseX();
  uint8_t mGetCoarseY();

  uint8_t mGetAttributeQuadrant();

  BackgroundPixel mGetBackgroundPixel();

  // Sprite evaluation
  SpritePixel mGetSpritePixel();

  // Pixel multiplexer
  MergedPixel mGetMergedPixel();

  // Shift register methods
  void mShiftRegisters();
  void mShiftTileRegisters();
  void mShiftAttributeRegisters();

  void mPushTileShiftLow(uint8_t value);
  void mPushTileShiftHigh(uint8_t value);

  uint8_t mFetchTileShiftLow();
  uint8_t mFetchTileShiftHigh();

  void mPushAttributeShiftLow(uint8_t value);
  void mPushAttributeShiftHigh(uint8_t value);

  uint8_t mFetchAttributeShiftLow();
  uint8_t mFetchAttributeShiftHigh();

  void mDoPixel();

 public:
  PPU(Mapper** mapper)
      : mPosH(0),
        mPosV(0),

        mPPUCTRL(0),
        mPPUMASK(0),
        mPPUSTATUS(0),
        mOAMADDR(0),
        mOAMDATA(0),
        mPPUSCROLL(0),
        mPPUADDR(0),
        mPPUDATA(0),
        mOAMDMA(0),

        mPPUDATAReadBuffer(0),

        mV(0),
        mT(0),
        mX(0),
        mW(0),

        mNameTableData(0),
        mAttributeData(0),
        mLowTileData(0),
        mHighTileData(0),

        mTileShiftLow(0),
        mTileShiftHigh(0),

        mAttributeShiftLow(0),
        mAttributeShiftHigh(0),

        mSpriteN(0),
        mSpriteM(0),

        mSecOAMSpriteCount(0),
        mSpriteInRange(false),
        mSpriteEvalFinished(false),

        mSpriteOutputs(),

        mNameTableMemory(),

        mMemory(mapper),
        mRegisterAccess() {
    mRegisterAccess.mPPUCTRL = WRITE;
    mRegisterAccess.mPPUMASK = WRITE;
    mRegisterAccess.mPPUSTATUS = READ;
    mRegisterAccess.mOAMADDR = WRITE;
    mRegisterAccess.mOAMDATA = READ_WRITE;
    mRegisterAccess.mPPUSCROLL = WRITE;
    mRegisterAccess.mPPUADDR = WRITE;
    mRegisterAccess.mPPUDATA = READ_WRITE;
    mRegisterAccess.mOAMDMA = WRITE;

    mCurrentSprite = {0, 0, 0, 0};
  };

  ~PPU() {};

  uint8_t getPPUCTRL();
  void setPPUCTRL(uint8_t value);

  uint8_t getPPUMASK();
  void setPPUMASK(uint8_t value);

  uint8_t getPPUSTATUS();
  void setPPUSTATUS(uint8_t value);

  uint8_t getOAMADDR();
  void setOAMADDR(uint8_t value);

  uint8_t getOAMDATA();
  void setOAMDATA(uint8_t value);

  uint8_t getPPUSCROLL();
  void setPPUSCROLL(uint8_t value);

  uint8_t getPPUADDR();
  void setPPUADDR(uint8_t value);

  uint8_t getPPUDATA();
  void setPPUDATA(uint8_t value);

  uint8_t getOAMDMA();
  void setOAMDMA(uint8_t value);

  uint16_t mIncreasePPUADDR();

  // Status register
  inline void mSetStatusFlag(PPUSTATUSFlag flag) { mPPUSTATUS |= flag; };
  inline void mclearStatusFlag(PPUSTATUSFlag flag) { mPPUSTATUS &= ~flag; };
  inline bool mCheckStatusFlag(PPUSTATUSFlag flag) {
    return mPPUSTATUS & flag;
  };

  // Get Nametable Memory
  inline NameTablesMemory& getNameTablesMemory() { return mNameTableMemory; }

  // Read and write memory
  inline uint8_t mReadMemory() { return mPPUDATA = mMemory.read(mPPUADDR); }
  inline void mWriteMemory() { mMemory.write(mPPUADDR, mPPUDATA); }

  inline uint8_t mReadOAM() { return mOAMDATA = mOAM[mOAMADDR]; }
  inline void mWriteOAM() { mOAM[mOAMADDR] = mOAMDATA; }

  void doCycle();
};
