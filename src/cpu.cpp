#include "cpu.hpp"

#include "memory.hpp"

namespace {
Memory& memory = Memory::get_instance();
}  // namespace

uint8_t CPU::_read_memory() { return memory.read(_address); }

void CPU::do_cycle() {
  if (_cycle == 1) {
    _address = _program_counter;
    _instruction = (Instruction)_read_memory();
    _program_counter++;

  } else {
    switch (_instruction) {
      case Instruction::BRK:
        break;

      case Instruction::ORA_INDIRECT_X:
        Instructions::ORA::indirect_x();
        break;

      case Instruction::ORA_ZERO_PAGE:
        Instructions::ORA::zero_page();
        break;

      default:
        _cycle = 1;
        break;
    }
  }
  _cycle++;
}