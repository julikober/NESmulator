#include "cpu.hpp"
#include "memory.hpp"

CPU& cpu = CPU::get_instance();
Memory& memory = Memory::get_instance();

void CPU::Instructions::ASL::zero_page() {
  switch (cpu._cycle) {
    case 2:
      cpu._address = cpu._program_counter;
      cpu._address = cpu._read_memory();
      cpu._program_counter++;
      break;

    case 3:
      cpu._buffer = cpu._read_memory();
      break;

    case 4:
      _carry = cpu._buffer >> 7;
      cpu._buffer <<= 1;
      memory.write(cpu._address, cpu._buffer);
      _set_flags();

    default:
      cpu._cycle = 1;
      break;
  }
}

void CPU::Instructions::ASL::_set_flags() {
  if (cpu._buffer == 0) {
    cpu._set_flag(ZERO);
  } else {
    cpu._clear_flag(ZERO);
  }

  if (cpu._buffer >> 7) {
    cpu._set_flag(NEGATIVE);
  } else {
    cpu._clear_flag(NEGATIVE);
  }

  if (_carry) {
    cpu._set_flag(CARRY);
  } else {
    cpu._clear_flag(CARRY);
  }
}
