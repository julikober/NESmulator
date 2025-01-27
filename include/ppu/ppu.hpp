#include <cstdint>

#include "./memory/memorymap.hpp"
#include "memory/exceptions.hpp"

#define SCANLINES 262
#define PIXELS 341

enum PPUCTRLFlags {
  PPUCTRL_NAMETABLE = 1 | 1 << 1,
  PPUCTRL_INCREMENT = 1 << 2,
  PPUCTRL_SPRITE_TABLE = 1 << 3,
  PPUCTRL_BACKGROUND_TABLE = 1 << 4,
  PPUCTRL_SPRITE_SIZE = 1 << 5,
  PPUCTRL_MASTER_SLAVE = 1 << 6,
  PPUCTRL_NMI = 1 << 7
};

enum VRAMAddrFlags {
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
  uint16_t mPPUADDR;
  uint8_t mPPUDATA;
  uint8_t mOAMDMA;

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
  uint16_t mV;
  uint16_t mT;
  uint8_t mX;
  uint8_t mW;

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

  uint8_t mSpriteN;
  uint8_t mSpriteM;

  uint8_t mSecOAMSpriteCount;

  // Name Tables
  NameTablesMemory mNameTableMemory;

  // Memory
  PPUMemoryMap mMemory;

  uint16_t mGetBaseNameTableAddress();
  uint16_t mGetAttributeTableAddress();
  uint16_t mGetBasePatternTableAddress();

  uint8_t mGetCoarseX();
  uint8_t mGetCoarseY();

  uint8_t mGetAttributeQuadrant();

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
      : mMemory(mapper),
        mPPUCTRL(0),
        mPPUMASK(0),
        mPPUSTATUS(0),
        mOAMADDR(0),
        mOAMDATA(0),
        mPPUSCROLL(0),
        mPPUADDR(0),
        mPPUDATA(0),
        mOAMDMA(0),
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
  };

  ~PPU() {};

  uint8_t getPPUCTRL() const;
  void setPPUCTRL(uint8_t value);

  uint8_t getPPUMASK() const;
  void setPPUMASK(uint8_t value);

  uint8_t getPPUSTATUS() const;
  void setPPUSTATUS(uint8_t value);

  uint8_t getOAMADDR() const;
  void setOAMADDR(uint8_t value);

  uint8_t getOAMDATA() const;
  void setOAMDATA(uint8_t value);

  uint8_t getPPUSCROLL() const;
  void setPPUSCROLL(uint8_t value);

  uint8_t getPPUADDR() const;
  void setPPUADDR(uint8_t value);

  uint8_t getPPUDATA() const;
  void setPPUDATA(uint8_t value);

  uint8_t getOAMDMA() const;
  void setOAMDMA(uint8_t value);

  // Read and write memory
  inline uint8_t mReadMemory() { return mPPUDATA = mMemory.read(mPPUADDR); }
  inline void mWriteMemory() { mMemory.write(mPPUADDR, mPPUDATA); }

  inline uint8_t mReadOAM() { return mOAMDATA = mOAM[mOAMADDR]; }
  inline void mWriteOAM() { mOAM[mOAMADDR] = mOAMDATA; }

  void doCycle();
};
