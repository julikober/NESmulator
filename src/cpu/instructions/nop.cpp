#include "cpu.hpp"

void CPU::InstructionSet::mExecuteNOP() {}

void CPU::InstructionSet::NOPImplied() {
  mExecuteImplied(&InstructionSet::mExecuteNOP);
}
