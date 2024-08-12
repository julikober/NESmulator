#pragma once

#include <cstdint>

enum StatusFlag {
  CARRY = 1 << 0,
  ZERO = 1 << 1,
  INTERRUPT_DISABLE = 1 << 2,
  DECIMAL_MODE = 1 << 3,
  BREAK = 1 << 4,
  OVERFLOW = 1 << 6,
  NEGATIVE = 1 << 7
};

enum class Instruction {
  BRK = 0x00,
  ORA_INDIRECT_X = 0x01,
  ORA_ZERO_PAGE = 0x05,
  ASL_ZERO_PAGE = 0x06,

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

  inline void _set_flag(uint8_t flags) { _status = flags; };
  inline void _clear_flag(uint8_t flags) { _status &= ~flags; };

  uint8_t _read_memory();

 public:
  static CPU& get_instance() {
    static CPU instance;
    return instance;
  }

  CPU(CPU const&) = delete;
  void operator=(CPU const&) = delete;

  void do_cycle();

  struct Instructions {
    struct ASL {
      static void zero_page();

      private:
        static uint8_t _carry;
        static void _set_flags();
    };

    struct ORA {
      static void zero_page();
      static void indirect_x();

     private:
      static void _set_flags();
    };
  };
};