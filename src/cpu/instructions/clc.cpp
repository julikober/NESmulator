#include "cpu.hpp"

void CPU::InstructionSet::CLCImplied() { mCpu.mClearFlag(CARRY); }