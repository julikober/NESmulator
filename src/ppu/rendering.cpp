#include "ppu/ppu.hpp"

void PPU::mDoScanline() {
  // Render pipeline
  mShiftRegisters();
  mGetMergedPixel();

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
        mPPUADDR =
            mGetBasePatternTableAddress() + mNameTableData * 16 + mPosV % 8;
        break;
      case 5:
        // Fetch pattern table low byte
        mLowTileData = mReadMemory();
        break;
      case 6:
        // Fetch pattern table high byte
        mPPUADDR =
            mGetBasePatternTableAddress() + mNameTableData * 16 + 8 + mPosV % 8;
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

            mSetPPUSTATUSFlag(PPUSTATUS_SPRITE_OVERFLOW);
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
        mCurrentSprite.y = mSecOAM[mPosH - 257];
        break;

      case 1:
        mCurrentSprite.tile = mSecOAM[mPosH - 257];
        break;

      case 2:
        mCurrentSprite.attribute = mSecOAM[mPosH - 257];
        break;

      case 3:
        mCurrentSprite.x = mSecOAM[mPosH - 257];
        break;

      case 4:
        // Fetch pattern table low byte
        mPPUADDR = mGetBasePatternTableAddress() + mCurrentSprite.tile * 16;
        break;

      case 5:
        // Fetch pattern table low byte
        mLowTileData = mReadMemory();
        break;

      case 6:
        // Fetch pattern table high byte
        mPPUADDR = mGetBasePatternTableAddress() + mCurrentSprite.tile * 16 + 8;
        break;

      case 7:
        // Fetch pattern table high byte
        mHighTileData = mReadMemory();
        break;
    }
  }
}

void PPU::mDoPostRenderScanline() {
  // Do nothing
}

void PPU::mDoVerticalBlankingLine() {
  // Set VBlank on tick 1
  if (mPosH == 1) {
    // Set VBlank flag
    mSetPPUSTATUSFlag(PPUSTATUS_VBLANK);

    if (mCheckPPUCTRLFlag(PPUCTRL_NMI_ENABLE)) {
      mCPU->requestNMI();
    }
  }

  // Do nothing
}
