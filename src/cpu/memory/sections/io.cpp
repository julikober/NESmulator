#include "cpu/memory/cpu_memory.hpp"
#include <stdexcept>

#define ADDR_PPUCTRL 0x2000
#define ADDR_PPUMASK 0x2001
#define ADDR_PPUSTATUS 0x2002
#define ADDR_OAMADDR 0x2003
#define ADDR_OAMDATA 0x2004
#define ADDR_PPUSCROLL 0x2005
#define ADDR_PPUADDR 0x2006
#define ADDR_PPUDATA 0x2007
#define ADDR_OAMDMA 0x4014

uint8_t &CPUMemory::IO::getRegister(uint16_t address) {
  switch (mResolveMirrors(address)) {
  case ADDR_PPUCTRL:
    return mPPURegisters.PPUCTRL;
  case ADDR_PPUMASK:
    return mPPURegisters.PPUMASK;
  case ADDR_PPUSTATUS:
    return mPPURegisters.PPUSTATUS;
  case ADDR_OAMADDR:
    return mPPURegisters.OAMADDR;
  case ADDR_OAMDATA:
    return mPPURegisters.OAMDATA;
  case ADDR_PPUSCROLL:
    return mPPURegisters.PPUSCROLL;
  case ADDR_PPUADDR:
    return mPPURegisters.PPUADDR;
  case ADDR_PPUDATA:
    return mPPURegisters.PPUDATA;
  case ADDR_OAMDMA:
    return mPPURegisters.OAMDMA;

  default:
    throw std::runtime_error("Invalid address");
  }
}

uint8_t CPUMemory::IO::read(uint16_t address) { return getRegister(address); }

void CPUMemory::IO::write(uint16_t address, uint8_t value) {
  getRegister(address) = value;
}
