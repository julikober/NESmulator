#include "ppu/ppu.hpp"

uint16_t PPU::mGetBaseNametableAddress() {
  uint8_t address;

  switch (mPPUCTRL & PPUCTRL_NAMETABLE) {
    case 0:
      address = 0x2000;
      break;
    case 1:
      address = 0x2400;
      break;
    case 2:
      address = 0x2800;
      break;
    case 3:
      address = 0x2C00;
      break;
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
  if (mPosH == 0) {                           // Idle Cycle
  } else if (mPosH >= 1 && mPosH <= 256) {    // Tile fetching
    // Fetch data
    switch ((mPosH - 1) % 8) {
      case 0:
        // Fetch name table byte
        mAddress = mGetBaseNametableAddress() + mPosV * 32 + (mPosH - 1) / 8;
        break;
      case 1:
        // Fetch name table byte
        break;
      case 2:
        // Fetch attribute table byte
        break;
      case 3:
        // Fetch attribute table byte
        break;
      case 4:
        // Fetch pattern table low byte
        break;
      case 5:
        // Fetch pattern table low byte
        break;
      case 6:
        // Fetch pattern table high byte
        break;
      case 7:
        // Fetch pattern table high byte
        break;

    }
  } else if (mPosH >= 257 && mPosH <= 320) {  // Sprite evaluation
  } else if (mPosH >= 321 && mPosH <= 336) {
  } else if (mPosH >= 337 && mPosH <= 340) {
  }
}