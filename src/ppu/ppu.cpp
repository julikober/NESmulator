#include "ppu/ppu.hpp"

PPU::PPU(Mapper** mapper, CPU* cpu)
    : mCPU(cpu),

      mMemory(mapper),

      mPosH(0),
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
}

uint16_t PPU::mGetBaseNameTableAddress() {
  uint16_t address;

  switch (mPPUCTRL & PPUCTRL_NAMETABLE) {
    case 0:
      address = NAMETABLE_0_START;
      break;
    case 1:
      address = NAMETABLE_1_START;
      break;
    case 2:
      address = NAMETABLE_2_START;
      break;
    case 3:
      address = NAMETABLE_3_START;
      break;
  }

  return address;
}

uint16_t PPU::mGetAttributeTableAddress() {
  return mGetBaseNameTableAddress() + 0x03C0;
}

uint16_t PPU::mGetBasePatternTableAddress() {
  uint16_t address;

  if (!(mPPUCTRL & PPUCTRL_BACKGROUND_TABLE)) {
    address = PATTERNTABLE_0_START;
  } else {
    address = PATTERNTABLE_1_START;
  }

  return address;
}

uint8_t PPU::mGetCoarseX() { return (mV & VRAMADDR_COARSE_X) >> 0; }
uint8_t PPU::mGetCoarseY() { return (mV & VRAMADDR_COARSE_Y) >> 5; }

uint8_t PPU::mGetAttributeQuadrant() {
  return (mGetCoarseX() & 0b10) | ((mGetCoarseY() >> 1) & 0b01);
}

PPU::BackgroundPixel PPU::mGetBackgroundPixel() {
  BackgroundPixel pixel;
  pixel.color = 0;
  pixel.palette = 0;

  pixel.color = (mFetchTileShiftLow() >> (7 - mX)) & 0x01;
  pixel.color |= ((mFetchTileShiftHigh() >> (7 - mX)) & 0x01) << 1;

  pixel.palette = (mFetchAttributeShiftLow() >> (7 - mX)) & 0x01;
  pixel.palette |= ((mFetchAttributeShiftHigh() >> (7 - mX)) & 0x01) << 1;

  return pixel;
}

PPU::SpritePixel PPU::mGetSpritePixel() {
  SpritePixel pixel;
  pixel.color = 0;
  pixel.palette = 0;
  pixel.priority = 0;

  for (SpriteOutput sprite : mSpriteOutputs) {
    if (sprite.x - mX < 8) {
      pixel.color = (sprite.tileLow >> (7 - (mX - sprite.x))) & 0x01;
      pixel.color |= ((sprite.tileHigh >> (7 - (mX - sprite.x))) & 0x01) << 1;

      pixel.palette = sprite.attribute & 0b11;

      pixel.priority = (sprite.attribute >> 5) & 0x01;

      break;
    }
  }

  return pixel;
}

PPU::MergedPixel PPU::mGetMergedPixel() {
  BackgroundPixel background = mGetBackgroundPixel();
  SpritePixel sprite = mGetSpritePixel();

  MergedPixel pixel;

  if (background.color == 0 && sprite.color == 0) {
    // Transparent pixel
    // Use fallback color
    pixel.color = 0;
    pixel.palette = 0;
    pixel.type = MergedPixel::Type::BACKGROUND;
  } else if (background.color == 0 && sprite.color != 0) {
    // Select sprite pixel
    pixel.color = sprite.color;
    pixel.palette = sprite.palette;
    pixel.type = MergedPixel::Type::SPRITE;
  } else if (background.color != 0 && sprite.color == 0) {
    // Select background pixel
    pixel.color = background.color;
    pixel.palette = background.palette;
    pixel.type = MergedPixel::Type::BACKGROUND;

  } else if (background.color != 0 && sprite.color != 0) {
    if (sprite.priority) {
      // Select sprite pixel
      pixel.color = sprite.color;
      pixel.palette = sprite.palette;
      pixel.type = MergedPixel::Type::SPRITE;
    } else {
      // Select background pixel
      pixel.color = background.color;
      pixel.palette = background.palette;
      pixel.type = MergedPixel::Type::BACKGROUND;
    }
  }

  std::cout << "Color: " << pixel.color << " Palette: " << pixel.palette
            << " Type: " << pixel.type << std::endl;

  return pixel;
}

void PPU::mShiftRegisters() {
  mShiftTileRegisters();
  mShiftAttributeRegisters();
}

void PPU::mShiftTileRegisters() {
  mTileShiftLow = (mTileShiftLow << 1) | 0x01;
  mTileShiftHigh = (mTileShiftHigh << 1) | 0x01;
}

void PPU::mShiftAttributeRegisters() {
  mAttributeShiftLow = (mAttributeShiftLow << 1) | 0x01;
  mAttributeShiftHigh = (mAttributeShiftHigh << 1) | 0x01;
}

void PPU::mPushTileShiftLow(uint8_t value) {
  mTileShiftLow = (mTileShiftLow & 0xFF00) | value;
}

void PPU::mPushTileShiftHigh(uint8_t value) {
  mTileShiftHigh = (mTileShiftHigh & 0xFF00) | value;
}

uint8_t PPU::mFetchTileShiftLow() { return mTileShiftLow >> 8; }
uint8_t PPU::mFetchTileShiftHigh() { return mTileShiftHigh >> 8; }

void PPU::mPushAttributeShiftLow(uint8_t value) {
  mAttributeShiftLow = (mAttributeShiftLow & 0xFF00) | ((value & 0x01) * 0xFF);
}

void PPU::mPushAttributeShiftHigh(uint8_t value) {
  mAttributeShiftHigh =
      (mAttributeShiftHigh & 0xFF00) | ((value & 0x01) * 0xFF);
}

uint8_t PPU::mFetchAttributeShiftLow() { return mAttributeShiftLow >> 8; }
uint8_t PPU::mFetchAttributeShiftHigh() { return mAttributeShiftHigh >> 8; }

uint16_t PPU::mIncreasePPUADDR() {
  if (mPPUCTRL & PPUCTRL_VRAM_INCREMENT) {
    mPPUADDR += 32;
  } else {
    mPPUADDR += 1;
  }
}

void PPU::doCycle() {
  if (mPosV >= 0 && mPosV <= 239) {  // Visible scanlines
    mDoScanline();
  } else if (mPosV == 240) {  // Post-render scanline
    mDoPostRenderScanline();
  } else if (mPosV >= 241 && mPosV <= 260) {  // Vertical blanking lines
    mDoVerticalBlankingLine();
  } else if (mPosV == 261) {  // Pre-render scanline
  }

  mPosH++;

  // Reset Pixel and increment scanline
  if (mPosH >= PIXELS) {
    mPosH = 0;
    mPosV++;

    // Reset scanline
    if (mPosV >= SCANLINES) {
      mPosV = 0;
    }
  }
}
