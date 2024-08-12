#include "cpu.hpp"

#include "memory.hpp"

namespace {
CPU& cpu = CPU::get_instance();
Memory& memory = Memory::get_instance();
}  // namespace

void CPU::_fetch_instruction() {
  _instruction = (Instruction)memory.read(_program_counter);
}

void CPU::do_cycle() {
  if (_cycle == 1) {
    _fetch_instruction();

  } else {
    switch (_instruction) {
      case Instruction::BRK:
        break;

      case Instruction::ORA_INDIRECT_X:
        Instructions::ORA::indirect_x();
        break;

      default:
        _cycle = 1;
        break;
    }
  }
  _cycle++;
}