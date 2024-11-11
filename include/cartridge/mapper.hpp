#pragma once
#include <cstdint>

enum MirroringMode {
  HORIZONTAL,
  VERTICAL,
  FOUR_SCREEN,
  SINGLE_SCREEN

  // TODO: Add more mirroring modes
};

class Mapper {
 private:
  MirroringMode mMirroringMode;

 public:
  Mapper() {};
  virtual ~Mapper() {};

  uint8_t map(uint16_t address);
};
