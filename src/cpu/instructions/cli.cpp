#include "cpu.hpp"

void CPU::InstructionSet::CLIImplied() { mCpu.mClearFlag(INTERRUPT_DISABLE); }