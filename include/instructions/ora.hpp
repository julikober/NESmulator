#include "cpu.hpp"
#include "memory.hpp"

namespace {
CPU& cpu = CPU::get_instance();
Memory& memory = Memory::get_instance();
}  // namespace

namespace Instructions {
struct ORA {
  static void indirect_x() {
    switch (cpu._current_cycle) {
      case 2:
        cpu._address = memory.read(cpu._program_counter);
        cpu._program_counter++;
        break;

      case 3:
        cpu._address += cpu._index_x;
        break;

      case 4:
        cpu._buffer = memory.read(cpu._address);
        break;

      case 5:
        cpu._set_address_high(cpu._address + 1);
        cpu._set_address_low(cpu._buffer);
        break;

      case 6:
        cpu._accumulator |= memory.read(cpu._address);
        cpu._set_flag(StatusFlag::ZERO, cpu._accumulator == 0);

      default:
        cpu._current_cycle = 1;
        break;
    }
  }
};
}  // namespace Instructions