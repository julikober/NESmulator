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
  if (mPosH == 0) {  // Idle Cycle
  }
  if (mPosH >= 1 && mPosH <= 256) {  // Tile fetching
    // Fetch data
    switch ((mPosH - 1) % 8) {
      case 0:
        // Fetch name table byte
        mPPUADDR =
            mGetBaseNameTableAddress() + (mPosV / 8) * 32 + (mPosH - 1) / 8;

        // Push data to shift registers
        mPushTileShiftLow(mLowTileData);
        mPushTileShiftHigh(mHighTileData);

        mPushAttributeShiftLow((mAttributeData >> mGetAttributeQuadrant()) &
                               0x01);
        mPushAttributeShiftHigh(
            (mAttributeData >> (mGetAttributeQuadrant() + 1)) & 0x01);

        break;
      case 1:
        mNameTableData = mReadMemory();
        break;
      case 2:
        // Fetch attribute table byte
        mPPUADDR =
            mGetAttributeTableAddress() + (mPosV / 32) * 8 + (mPosH - 1) / 32;
        break;
      case 3:
        // Fetch attribute table byte
        mAttributeData = mReadMemory();

        break;
      case 4:
        // Fetch pattern table low byte
        mPPUADDR = mGetBasePatternTableAddress() + mNameTableData * 16;
        break;
      case 5:
        // Fetch pattern table low byte
        mLowTileData = mReadMemory();
        break;
      case 6:
        // Fetch pattern table high byte
        mPPUADDR = mGetBasePatternTableAddress() + mNameTableData * 16 + 8;
        break;
      case 7:
        // Fetch pattern table high byte
        mHighTileData = mReadMemory();
        break;
    }
  }

  if (mPosH >= 1 && mPosH <= 64) {  // Initalize secondary OAM with 0xFF
    mSecOAM[mPosH - 1] = 0xFF;
  }

  if (mPosH >= 65 && mPosH <= 256) {                 // Sprite evaluation
    if ((mPosH % 2 == 1) && !mSpriteEvalFinished) {  // Odd cycles
      if (mSecOAMSpriteCount < 8) {
        // Read from OAM
        mOAMADDR = mSpriteN * 4 + mSpriteM;
        mReadOAM();

        // Check if sprite is in range
        if (!mSpriteInRange) {
          if (mPosV - mOAMDATA < 8) {
            mSpriteInRange = true;

            mSpriteM++;
          } else {
            mSpriteN++;
          }
        } else {
          mSpriteM++;
        }

      } else {
        if (!mSpriteInRange) {
          if (mPosV - mOAMDATA < 8) {
            mSpriteInRange = true;

            mSetStatusFlag(PPUSTATUS_SPRITE_OVERFLOW);
            mSpriteM++;
          } else {
            mSpriteM++;  // Hardware bug
            mSpriteN++;

            if (mSpriteM > 3) {  // Overflow m without incrementing n
              mSpriteM = 0;
            }

            if (mSpriteN > 63) {
              mSpriteEvalFinished = true;
            }

            return;  // Skip default overflow check
          }
        } else {
          mSpriteM++;
        }
      }

      // M overflow
      if (mSpriteM > 3) {
        mSpriteM = 0;
        mSpriteN++;
        mSpriteInRange = false;
      }
      // N overflow
      if (mSpriteN > 63) {
        mSpriteN = 0;
        mSpriteEvalFinished = true;
      }

    } else {  // Even cycles and sprite evaluation finished
      // Write to secondary OAM
      if (mSecOAMSpriteCount < 8) {
        mSecOAM[mSecOAMSpriteCount * 4 + mSpriteM] = mOAMDATA;
      } else {
      }
    }
  }

  if (mPosH >= 257 && mPosH <= 320) {  // Sprite loading
    // Set OAMADDR to 0
    mOAMADDR = 0;

    switch ((mPosH - 257) % 8) {
      case 0:
        mCurrentSprite.mY = mSecOAM[mPosH - 257];
        break;

      case 1:
        mCurrentSprite.mTile = mSecOAM[mPosH - 257];
        break;

      case 2:
        mCurrentSprite.mAttribute = mSecOAM[mPosH - 257];
        break;

      case 3:
        mCurrentSprite.mX = mSecOAM[mPosH - 257];
        break;

      case 4:
        // Fetch pattern table low byte
        mPPUADDR = mGetBasePatternTableAddress() + mCurrentSprite.mTile * 16;
        break;

      case 5:
        // Fetch pattern table low byte
        mLowTileData = mReadMemory();
        break;

      case 6:
        // Fetch pattern table high byte
        mPPUADDR =
            mGetBasePatternTableAddress() + mCurrentSprite.mTile * 16 + 8;
        break;

      case 7:
        // Fetch pattern table high byte
        mHighTileData = mReadMemory();
        break;
    }
  }
}