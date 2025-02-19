#pragma once

#include <cstdint>
#include <fstream>

#include "./loader/mapper.hpp"
#include "cartridge/mapper/mapper.hpp"
#include "cpu/cpu.hpp"
#include "ppu/ppu.hpp"

#define HEADER_SIZE 16
#define TRAINER_SIZE 512

struct ROMHeader {
  uint8_t NesString[4];
  uint8_t PrgRomSize;
  uint8_t ChrRomSize;
  uint8_t flags6;
  uint8_t flags7;
  uint8_t flags8;
  uint8_t flags9;
  uint8_t flags10;
  uint8_t padding[5];
};

class Emulator {
 private:
  CPU mCPU;
  PPU mPPU;
  Mapper* mMapper;

 public:
  void loadROMFile(const char* filename);
};
