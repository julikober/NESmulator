#include "cpu.hpp"

void CPU::InstructionSet::CLDImplied() { mCpu.mClearFlag(DECIMAL); }