#include <sstream>

#include "cpu/memory/memorymap.hpp"
#include "logger/logger.hpp"

uint8_t CPUMemoryMap::IOSection::read(uint16_t address) {
  try {
    switch (mResolveMirrors(address)) {
      case ADDR_PPUCTRL:
        mPPU.getPPUCTRL();
        break;
      case ADDR_PPUMASK:
        mPPU.getPPUMASK();
        break;
      case ADDR_PPUSTATUS:
        mPPU.getPPUSTATUS();
        break;
      case ADDR_OAMADDR:
        mPPU.getOAMADDR();
        break;
      case ADDR_OAMDATA:
        mPPU.getOAMDATA();
        break;
      case ADDR_PPUSCROLL:
        mPPU.getPPUSCROLL();
        break;
      case ADDR_PPUADDR:
        mPPU.getPPUADDR();
        break;
      case ADDR_PPUDATA:
        mPPU.getPPUDATA();
        break;
      case ADDR_OAMDMA:
        mPPU.getOAMDMA();
        break;

      default:
        std::stringstream exceptionMessage;

        exceptionMessage << "Address 0x" << std::hex << address
                         << " is not a valid IO register";

        throw InvalidAddressException(exceptionMessage.str());
    }
  } catch (InvalidAccessTypeException& e) {
    Logger& logger = Logger::getInstance();

    logger.log(e.what(), WARNING);
    return 0;
  }
}

void CPUMemoryMap::IOSection::write(uint16_t address, uint8_t value) {
  try {
    switch (mResolveMirrors(address)) {
      case ADDR_PPUCTRL:
        mPPU.setPPUCTRL(value);
        break;
      case ADDR_PPUMASK:
        mPPU.setPPUMASK(value);
        break;
      case ADDR_PPUSTATUS:
        mPPU.setPPUSTATUS(value);
        break;
      case ADDR_OAMADDR:
        mPPU.setOAMADDR(value);
        break;
      case ADDR_OAMDATA:
        mPPU.setOAMDATA(value);
        break;
      case ADDR_PPUSCROLL:
        mPPU.setPPUSCROLL(value);
        break;
      case ADDR_PPUADDR:
        mPPU.setPPUADDR(value);
        break;
      case ADDR_PPUDATA:
        mPPU.setPPUDATA(value);
        break;
      case ADDR_OAMDMA:
        mPPU.setOAMDMA(value);
        break;

      default:
        std::stringstream exceptionMessage;

        exceptionMessage << "Address 0x" << std::hex << address
                         << " is not a valid IO register";

        throw InvalidAddressException(exceptionMessage.str());
    }
  } catch (InvalidAccessTypeException& e) {
    Logger& logger = Logger::getInstance();

    logger.log(e.what(), WARNING);
  }
}
