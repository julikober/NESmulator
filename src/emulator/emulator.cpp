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

void Emulator::tick() {
  if (mCPUCounter == 12) {
    mCPU->doCycle();
    mCPUCounter = 0;
  }

  if (mPPUCounter == 4) {
    mPPU->doCycle();
    mPPUCounter = 0;
  }

  mCPUCounter++;
  mPPUCounter++;
}