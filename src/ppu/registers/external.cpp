#include "ppu/ppu.hpp"

uint8_t PPU::getPPUCTRL() {
  if (mRegisterAccess.mPPUCTRL == READ ||
      mRegisterAccess.mPPUCTRL == READ_WRITE) {
    return mPPUCTRL;
  } else {
    throw InvalidAccessTypeException("PPUCTRL register cannot be read");
  }
}

void PPU::setPPUCTRL(uint8_t value) {
  if (mRegisterAccess.mPPUCTRL == WRITE ||
      mRegisterAccess.mPPUCTRL == READ_WRITE) {
    mPPUCTRL = value;
  } else {
    throw InvalidAccessTypeException("PPUCTRL register cannot be written to");
  }
}

uint8_t PPU::getPPUMASK() {
  if (mRegisterAccess.mPPUMASK == READ ||
      mRegisterAccess.mPPUMASK == READ_WRITE) {
    return mPPUMASK;
  } else {
    throw InvalidAccessTypeException("PPUMASK register cannot be read");
  }
}

void PPU::setPPUMASK(uint8_t value) {
  if (mRegisterAccess.mPPUMASK == WRITE ||
      mRegisterAccess.mPPUMASK == READ_WRITE) {
    mPPUMASK = value;
  } else {
    throw InvalidAccessTypeException("PPUMASK register cannot be written to");
  }
}

uint8_t PPU::getPPUSTATUS() {
  if (mRegisterAccess.mPPUSTATUS == READ ||
      mRegisterAccess.mPPUSTATUS == READ_WRITE) {
    // Clear W register
    mClearW();

    return mPPUSTATUS;
  } else {
    throw InvalidAccessTypeException("PPUSTATUS register cannot be read");
  }
}

void PPU::setPPUSTATUS(uint8_t value) {
  if (mRegisterAccess.mPPUSTATUS == WRITE ||
      mRegisterAccess.mPPUSTATUS == READ_WRITE) {
    mPPUSTATUS = value;
  } else {
    throw InvalidAccessTypeException("PPUSTATUS register cannot be written to");
  }
}

uint8_t PPU::getOAMADDR() {
  if (mRegisterAccess.mOAMADDR == READ ||
      mRegisterAccess.mOAMADDR == READ_WRITE) {
    return mOAMADDR;
  } else {
    throw InvalidAccessTypeException("OAMADDR register cannot be read");
  }
}

void PPU::setOAMADDR(uint8_t value) {
  if (mRegisterAccess.mOAMADDR == WRITE ||
      mRegisterAccess.mOAMADDR == READ_WRITE) {
    mOAMADDR = value;
  } else {
    throw InvalidAccessTypeException("OAMADDR register cannot be written to");
  }
}

uint8_t PPU::getOAMDATA() {
  if (mRegisterAccess.mOAMDATA == READ ||
      mRegisterAccess.mOAMDATA == READ_WRITE) {
    return mOAMDATA;
  } else {
    throw InvalidAccessTypeException("OAMDATA register cannot be read");
  }
}

void PPU::setOAMDATA(uint8_t value) {
  if (mRegisterAccess.mOAMDATA == WRITE ||
      mRegisterAccess.mOAMDATA == READ_WRITE) {
    mOAMDATA = value;

    // Increment OAMADDR
    mOAMADDR++;
  } else {
    throw InvalidAccessTypeException("OAMDATA register cannot be written to");
  }
}

uint8_t PPU::getPPUSCROLL() {
  if (mRegisterAccess.mPPUSCROLL == READ ||
      mRegisterAccess.mPPUSCROLL == READ_WRITE) {
    return mPPUSCROLL;
  } else {
    throw InvalidAccessTypeException("PPUSCROLL register cannot be read");
  }
}

void PPU::setPPUSCROLL(uint8_t value) {
  if (mRegisterAccess.mPPUSCROLL == WRITE ||
      mRegisterAccess.mPPUSCROLL == READ_WRITE) {
    // W determines which byte is being written
    // High byte is written first
    if (!mW) {
      mPPUSCROLL = (mPPUSCROLL & 0x00FF) | (value << 8);
    } else {
      mPPUSCROLL = (mPPUSCROLL & 0xFF00) | value;
    }

    // Flip W register
    mFlipW();
  } else {
    throw InvalidAccessTypeException("PPUSCROLL register cannot be written to");
  }
}

uint8_t PPU::getPPUADDR() {
  if (mRegisterAccess.mPPUADDR == READ ||
      mRegisterAccess.mPPUADDR == READ_WRITE) {
    return mPPUADDR;
  } else {
    throw InvalidAccessTypeException("PPUADDR register cannot be read");
  }
}

void PPU::setPPUADDR(uint8_t value) {
  if (mRegisterAccess.mPPUADDR == WRITE ||
      mRegisterAccess.mPPUADDR == READ_WRITE) {
    // W determines which byte is being written
    // High byte is written first
    if (!mW) {
      mPPUADDR = (mPPUADDR & 0x00FF) | (value << 8);
    } else {
      mPPUADDR = (mPPUADDR & 0xFF00) | value;
    }

    // Flip W register
    mFlipW();
  } else {
    throw InvalidAccessTypeException("PPUADDR register cannot be written to");
  }
}

uint8_t PPU::getPPUDATA() {
  if (mRegisterAccess.mPPUDATA == READ ||
      mRegisterAccess.mPPUDATA == READ_WRITE) {
    uint8_t data = mPPUDATAReadBuffer;
    mPPUDATAReadBuffer = mPPUDATA;
    return data;
  } else {
    throw InvalidAccessTypeException("PPUDATA register cannot be read");
  }
}

void PPU::setPPUDATA(uint8_t value) {
  if (mRegisterAccess.mPPUDATA == WRITE ||
      mRegisterAccess.mPPUDATA == READ_WRITE) {
    mPPUDATA = value;
    mWriteMemory();

    // Increment PPUADDR
    if (mPPUCTRL & PPUCTRL_VRAM_INCREMENT) {
      mPPUADDR += 32;
    } else {
      mPPUADDR += 1;
    }
  } else {
    throw InvalidAccessTypeException("PPUDATA register cannot be written to");
  }
}

uint8_t PPU::getOAMDMA() {
  if (mRegisterAccess.mOAMDMA == READ ||
      mRegisterAccess.mOAMDMA == READ_WRITE) {
    return mOAMDMA;
  } else {
    throw InvalidAccessTypeException("OAMDMA register cannot be read");
  }
}

void PPU::setOAMDMA(uint8_t value) {
  if (mRegisterAccess.mOAMDMA == WRITE ||
      mRegisterAccess.mOAMDMA == READ_WRITE) {
    mOAMDMA = value;
  } else {
    throw InvalidAccessTypeException("OAMDMA register cannot be written to");
  }
}
