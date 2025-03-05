#include "emulator/emulator.hpp"

Emulator::Emulator() {
  mCPU = new CPU(&mMapper, mPPU);
  mPPU = new PPU(&mMapper, mCPU);
  mMapper = nullptr;
}

Emulator::~Emulator() {
  delete mCPU;
  delete mPPU;
  delete mMapper;
}
