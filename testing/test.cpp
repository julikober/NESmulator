#include <cstdint>
#include <iostream>

#include "cartridge/mapper/mappers/000.hpp"
#include "cpu/cpu.hpp"
#include "cpu/memory/memorymap.hpp"
#include "logger/logger.hpp"
#include "ppu/memory/memorymap.hpp"

int main(void) {
  Logger& Logger = Logger::getInstance();

  NameTablesMemory nameTablesMemory = NameTablesMemory();

  Mapper* mapper =
      new Mapper000(nameTablesMemory, 1, 1, VERTICAL, false, false, false);

  PPU ppu = PPU(&mapper);

  CPUMemoryMap cpuMemory = CPUMemoryMap(&mapper, ppu);
  CPU cpu = CPU(cpuMemory);

  // Test simple background sprite
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUDATA, 0b10000000);

  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x01);
  // cpuMemory.write(ADDR_PPUDATA, 0b01000000);

  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x02);
  // cpuMemory.write(ADDR_PPUDATA, 0b00100000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x03);
  // cpuMemory.write(ADDR_PPUDATA, 0b00010000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x04);
  // cpuMemory.write(ADDR_PPUDATA, 0b00001000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x05);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000100);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x06);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000010);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x07);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000001);
  

  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x08);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x09);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0A);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0B);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0C);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0D);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0E);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);
  
  // cpuMemory.write(ADDR_PPUADDR, 0x00);
  // cpuMemory.write(ADDR_PPUADDR, 0x0F);
  // cpuMemory.write(ADDR_PPUDATA, 0b00000000);

  uint8_t data[] = {
    0b10000100,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,

    0b00001100,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
  };

  mapper->loadCHRROM(data, 16);

  for (int i = 0; i < 24; i++) {
    ppu.doCycle();
  }

  return 0;
}