#include "cpu.hpp"

void CPU::InstructionSet::mWriteSAX() {
  mCpu.mWriteMemory(mCpu.mAccumulator & mCpu.mXIndex);
}

void CPU::InstructionSet::SAXZeroPage() {
  mExecuteZeroPage(nullptr, nullptr, &InstructionSet::mWriteSAX);
}

void CPU::InstructionSet::SAXZeroPageY() {
  mExecuteZeroPageY(nullptr, nullptr, &InstructionSet::mWriteSAX);
}

void CPU::InstructionSet::SAXAbsolute() {
  mExecuteAbsolute(nullptr, nullptr, &InstructionSet::mWriteSAX);
}

void CPU::InstructionSet::SAXIndirectX() {
  mExecuteIndirectX(nullptr, nullptr, &InstructionSet::mWriteSAX);
}
