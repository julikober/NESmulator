#include <fstream>
#include <iostream>

#include "cpu.hpp"
#include "json/json.h"
#include "memory.hpp"

// This is a test runner for the CPU. It reads a JSON file with test cases and
// For this to work the cpu registers must be public.

int main(void) {
  Json::Value root;
  std::ifstream ifs;

  ifs.open("testing/ProcessorTests/nes6502/v1/53.json");
  ifs >> root;
  ifs.close();

  Memory memory = Memory();
  CPU cpu = CPU(memory);

  auto& test = root[0];
  bool failed = false;

  for (auto& test : root) {
    printf("Running test %s:\n", test["name"].asCString());

    auto& state = test["initial"];

    cpu.loadState(state["pc"].asInt(), state["s"].asInt(), state["a"].asInt(),
                  state["x"].asInt(), state["y"].asInt(), state["p"].asInt());

    memory.clear();

    auto& memoryState = state["ram"];
    for (auto& mem : memoryState) {
      memory.write(mem[0].asInt(), mem[1].asInt());
    }

    do {
      cpu.doCycle();
      cpu.dumpRegisters();
    } while (cpu.mCycle != 1);

    auto& finalState = test["final"];

    if (finalState["pc"].asInt() != cpu.mProgramCounter) {
      printf("PC: %04X != %04X\n", finalState["pc"].asInt(),
             cpu.mProgramCounter);

      failed = true;
    }

    if (finalState["s"].asInt() != cpu.mStackPointer) {
      printf("S: %02X != %02X\n", finalState["s"].asInt(), cpu.mStackPointer);

      failed = true;
    }

    if (finalState["a"].asInt() != cpu.mAccumulator) {
      printf("A: %02X != %02X\n", finalState["a"].asInt(), cpu.mAccumulator);

      failed = true;
    }

    if (finalState["x"].asInt() != cpu.mXIndex) {
      printf("X: %02X != %02X\n", finalState["x"].asInt(), cpu.mXIndex);

      failed = true;
    }

    if (finalState["y"].asInt() != cpu.mYIndex) {
      printf("Y: %02X != %02X\n", finalState["y"].asInt(), cpu.mYIndex);

      failed = true;
    }

    if (finalState["p"].asInt() != cpu.mStatus) {
      printf("P: %02X != %02X\n", finalState["p"].asInt(), cpu.mStatus);

      failed = true;
    }

    auto& finalMemoryState = finalState["ram"];

    for (auto& mem : finalMemoryState) {
      if (mem[1].asInt() != memory.read(mem[0].asInt())) {
        printf("Memory at %04X: %02X != %02X\n", mem[0].asInt(), mem[1].asInt(),
               memory.read(mem[0].asInt()));

        failed = true;
      }
    }

    if (failed) {
      break;
    }
  }

  if (failed) {
    printf("Test failed\n");
  } else {
    printf("All tests passed\n");
  }

  return 0;
}