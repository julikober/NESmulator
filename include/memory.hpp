#pragma once

#include <cstdint>

class Memory {
 private:
  uint8_t _memory[0xFFFF];

  Memory() {
    for (int i = 0; i < 0xFFFF; i++) {
      _memory[i] = 0;
    }
  };

 public:
  static Memory& get_instance() {
    static Memory instance;
    return instance;
  };

  Memory(Memory const&) = delete;
  void operator=(Memory const&) = delete;

  inline uint8_t read(uint16_t address) { return _memory[address]; };

  inline void write(uint16_t address, uint8_t value) { _memory[address] = value; };
};