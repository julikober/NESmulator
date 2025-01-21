#include "ppu/ppu.hpp"

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

  switch (mPPUCTRL & PPUCTRL_BACKGROUND_TABLE) {
    case 0:
      address = PATTERNTABLE_0_START;
      break;
    case 1:
      address = PATTERNTABLE_1_START;
      break;
  }

  return address;
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

void PPU::doCycle() {
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

  if (mPosV >= 0 && mPosV <= 239) {  // Visible scanlines
    mDoPixel();
  } else if (mPosV == 240) {                  // Post-render scanline
  } else if (mPosV >= 241 && mPosV <= 260) {  // Vertical blanking lines
  } else if (mPosV == 261) {                  // Pre-render scanline
  }
}

void PPU::mDoPixel() {
  if (mPosH == 0) {                         // Idle Cycle
  } else if (mPosH >= 1 && mPosH <= 256) {  // Tile fetching
    // Fetch data
    switch ((mPosH - 1) % 8) {
      case 0:
        // Fetch name table byte
        mAddress =
            mGetBaseNameTableAddress() + (mPosV / 8) * 32 + (mPosH - 1) / 8;

        // Push data to shift registers
        mPushTileShiftLow(mLowTileData);
        mPushTileShiftHigh(mHighTileData);

        
        break;
      case 1:
        mNameTableData = mReadMemory();
        break;
      case 2:
        // Fetch attribute table byte
        mAddress =
            mGetAttributeTableAddress() + (mPosV / 32) * 8 + (mPosH - 1) / 32;
        break;
      case 3:
        // Fetch attribute table byte
        mAttributeData = mReadMemory();

        break;
      case 4:
        // Fetch pattern table low byte
        mAddress = mGetBasePatternTableAddress() + mNameTableData * 16;
        break;
      case 5:
        // Fetch pattern table low byte
        mLowTileData = mReadMemory();
        break;
      case 6:
        // Fetch pattern table high byte
        mAddress = mGetBasePatternTableAddress() + mNameTableData * 16 + 8;
        break;
      case 7:
        // Fetch pattern table high byte
        mHighTileData = mReadMemory();
        break;
    }
  } else if (mPosH >= 257 && mPosH <= 320) {  // Sprite evaluation
  } else if (mPosH >= 321 && mPosH <= 336) {
  } else if (mPosH >= 337 && mPosH <= 340) {
  }
}