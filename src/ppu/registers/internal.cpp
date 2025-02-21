#include "ppu/ppu.hpp"

void PPU::mClearW() {
  mW = 0;
}

void PPU::mFlipW() {
  mW &= mW;
}