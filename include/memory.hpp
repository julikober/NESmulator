#pragma once

#include <cstdint>

class Memory {
 private:
  uint8_t _memory[0xFFFF];

 public:
  Memory() {
    for (int i = 0; i < 0xFFFF; i++) {
      _memory[i] = 0;
    }
  };
  ~Memory(){};

  inline uint8_t read(uint16_t address) { return _memory[address]; };

  inline void write(uint16_t address, uint8_t value) {
    _memory[address] = value;
  };
};