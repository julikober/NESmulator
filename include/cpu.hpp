#pragma once

#include <cstdint>
#include "ora.hpp"

enum class StatusFlag {
  CARRY = 0,
  ZERO = 1,
  INTERRUPT_DISABLE = 2,
  DECIMAL_MODE = 3,
  BREAK = 4,
  OVERFLOW = 6,
  NEGATIVE = 7
};

enum class Instruction {
  BRK = 0x00,
  ORA_INDIRECT_X = 0x01,

};

class CPU {
 private:
  uint16_t _program_counter;
  uint8_t _stack_pointer;
  uint8_t _accumulator;
  uint8_t _index_x;
  uint8_t _index_y;
  uint8_t _status;
  Instruction _instruction;

  uint16_t _address;
  uint8_t _buffer;

  uint8_t _cycle;

  CPU()
      : _program_counter(0),
        _stack_pointer(0xFF),
        _accumulator(0),
        _index_x(0),
        _index_y(0),
        _status(0),
        _cycle(1){};
  ~CPU(){};

  inline uint8_t _get_program_counter_high() { return _program_counter >> 8; }
  inline uint8_t _get_program_counter_low() { return _program_counter & 0xFF; }
  inline void _set_program_counter_high(uint8_t value) {
    _program_counter = (_program_counter & 0x00FF) | (value << 8);
  }
  inline void _set_program_counter_low(uint8_t value) {
    _program_counter = (_program_counter & 0xFF00) | value;
  }

  inline uint8_t _get_address_high() { return _address >> 8; }
  inline uint8_t _get_address_low() { return _address & 0xFF; }
  inline void _set_address_high(uint8_t value) {
    _address = (_address & 0x00FF) | (value << 8);
  }
  inline void _set_address_low(uint8_t value) {
    _address = (_address & 0xFF00) | value;
  }

  void _fetch_instruction();

 public:
  static CPU& get_instance() {
    static CPU instance;
    return instance;
  }

  CPU(CPU const&) = delete;
  void operator=(CPU const&) = delete;

  void do_cycle();

  friend struct Instructions::ORA;
};