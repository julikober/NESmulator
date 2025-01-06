#include <cstdint>

#include "./memory/memorymap.hpp"
#include "memory/exceptions.hpp"

class PPU {
 private:
  uint16_t mCycle;
  uint16_t mPosH;
  uint16_t mPosV;

  // Registers
  uint8_t mPPUCTRL;
  uint8_t mPPUMASK;
  uint8_t mPPUSTATUS;
  uint8_t mOAMADDR;
  uint8_t mOAMDATA;
  uint8_t mPPUSCROLL;
  uint8_t mPPUADDR;
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

  // Latches
  uint8_t mPatternData;
  uint8_t mAttributeData;
  uint8_t mLowTileData;
  uint8_t mHighTileData;

  // Shift registers
  uint16_t mTileShiftLow;
  uint16_t mTileShiftHigh;

  uint8_t mAttributeShiftLow;
  uint8_t mAttributeShiftHigh;

  // OAM
  std::array<uint8_t, 256> mOAM;
  std::array<uint8_t, 32> mSecOAM;

  // Name Tables
  NameTablesMemory mNameTableMemory;

  // Memory
  PPUMemoryMap mMemory;

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
};
