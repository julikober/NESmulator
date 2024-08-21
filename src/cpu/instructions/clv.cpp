#include "cpu.hpp"

void CPU::InstructionSet::CLVImplied() { mCpu.mClearFlag(OVERFLOW); }