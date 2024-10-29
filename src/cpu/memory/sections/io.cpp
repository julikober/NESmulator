#include "cpu/memory/cpu_memory.hpp"

#define PPU_CTRL_1 0x2000
#define PPU_CTRL_2 0x2001
#define PPU_STATUS 0x2002
#define SPR_RAM_ADDR 0x2003
#define SPR_RAM_IO 0x2004
#define VRAM_ADDR_1 0x2005
#define VRAM_ADDR_2 0x2006
#define VRAM_IO 0x2007

uint8_t& CPUMemory::IO::getRegister(uint16_t address) {
  switch (mResolveMirrors(address)) {
    case PPU_CTRL_1:
      return mPPURegisters.ppuCtrl1;
    case PPU_CTRL_2:
      return mPPURegisters.ppuCtrl2;
    case PPU_STATUS:
      return mPPURegisters.ppuStatus;
    case SPR_RAM_ADDR:
      return mPPURegisters.sprRamAddr;
    case SPR_RAM_IO:
      return mPPURegisters.sprRamIO;
    case VRAM_ADDR_1:
      return mPPURegisters.vramAddr1;
    case VRAM_ADDR_2:
      return mPPURegisters.vramAddr2;
    case VRAM_IO:
      return mPPURegisters.vramIO;
  }
}

uint8_t CPUMemory::IO::read(uint16_t address) { return getRegister(address); }

void CPUMemory::IO::write(uint16_t address, uint8_t value) {
  getRegister(address) = value;
}
