#include "cpu.hpp"

void CPU::InstructionSet::mExecuteCLI() { mCpu.mClearFlag(INTERRUPT_DISABLE); }

void CPU::InstructionSet::CLIImplied() {
  mExecuteImmediate(&InstructionSet::mExecuteCLI);
}