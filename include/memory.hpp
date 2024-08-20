#pragma once

#include <cstdint>
#include <cstdio>

class Memory {
 private:
  uint8_t mMemory[0xFFFF];

 public:
  Memory() {
    for (int i = 0; i < 0xFFFF; i++) {
      mMemory[i] = 0;
    }
  };
  ~Memory(){};

  inline uint8_t read(uint16_t address) { return mMemory[address]; };

  inline void write(uint16_t address, uint8_t value) {
    mMemory[address] = value;
  };

  void loadFile(const char* filename) { // Currently for debugging purposes only
    FILE* file = fopen(filename, "rb");
    if (file == nullptr) {
      printf("Error: Could not open file %s\n", filename);
      return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(mMemory, size, 1, file);
    fclose(file);
  }

  void dumpMemory() {
    // Print first page of memory
    for (int i = 0; i <= 0x0F; i++) {
      printf("\n%02X: ", i * 0x10);
      for (int j = 0; j <= 0x0F; j++) {
        printf("%02X ", mMemory[i * 0x10 + j]);
      }
    }
    printf("\n");
  }
};