#include "cpu.hpp"
#include "memory.hpp"

namespace {
CPU& cpu = CPU::get_instance();
Memory& memory = Memory::get_instance();
}  // namespace

void CPU::Instructions::ORA::zero_page() {
  switch (cpu._cycle) {
    case 2:
      cpu._address = cpu._program_counter;
      cpu._address = cpu._read_memory();
      cpu._program_counter++;
      break;

    case 3:
      cpu._accumulator |= cpu._read_memory();
      _set_flags();

    default:
      cpu._cycle = 1;
      break;
  }
}

void CPU::Instructions::ORA::indirect_x() {
  switch (cpu._cycle) {
    case 2:
      cpu._address = cpu._program_counter;
      cpu._address = cpu._read_memory();
      cpu._program_counter++;
      break;

    case 3:
      cpu._address = (cpu._address + cpu._index_x) % 0xFF;
      break;

    case 4:
      cpu._buffer = cpu._read_memory();
      break;

    case 5:
      cpu._set_address_high(cpu._address + 1);
      cpu._set_address_low(cpu._buffer);
      break;

    case 6:
      cpu._accumulator |= cpu._read_memory();
      _set_flags();

    default:
      cpu._cycle = 1;
      break;
  }
}

void CPU::Instructions::ORA::_set_flags() {
  if (cpu._accumulator == 0) {
    cpu._set_flag(ZERO);
  } else {
    cpu._clear_flag(ZERO);
  }

  if (cpu._accumulator >> 7) {
    cpu._set_flag(NEGATIVE);
  } else {
    cpu._clear_flag(NEGATIVE);
  }
}
