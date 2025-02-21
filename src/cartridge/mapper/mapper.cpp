#include "cartridge/mapper/mapper.hpp"

MemoryLocation Mapper::mMapAlternativeMirrors(uint16_t address) {
  throw MissingNametableMirroringException(
      "Alternative mirroring not implemented for this mapper");
}

MemoryLocation Mapper::mMapNametableMirrors(uint16_t address) {
  if (mHasAlternativeMirroring) {
    try {
      return mMapAlternativeMirrors(address);
    } catch (MissingNametableMirroringException& e) {
      Logger::getInstance().log(e.what(), WARNING);
      Logger::getInstance().log("Falling back to default mirroring", INFO);

      mHasAlternativeMirroring = false;
    }
  }

  if (mMirroringMode == HORIZONTAL) {
    if (address >= NAMETABLE_0_START && address <= NAMETABLE_0_END) {
      // Map nametable 0 to first KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_0_START};
    } else if (address >= NAMETABLE_1_START && address <= NAMETABLE_1_END) {
      // Map nametable 1 to first KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_1_START};
    } else if (address >= NAMETABLE_2_START && address <= NAMETABLE_2_END) {
      // Map nametable 2 to second KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_2_START + NAMETABLE_SIZE};
    } else if (address >= NAMETABLE_3_START && address <= NAMETABLE_3_END) {
      // Map nametable 3 to second KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_3_START + NAMETABLE_SIZE};
    }
  } else if (mMirroringMode == VERTICAL) {
    if (address >= NAMETABLE_0_START && address <= NAMETABLE_0_END) {
      // Map nametable 0 to first KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_0_START};
    } else if (address >= NAMETABLE_1_START && address <= NAMETABLE_1_END) {
      // Map nametable 1 to second KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_1_START + NAMETABLE_SIZE};
    } else if (address >= NAMETABLE_2_START && address <= NAMETABLE_2_END) {
      // Map nametable 2 to first KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_2_START};
    } else if (address >= NAMETABLE_3_START && address <= NAMETABLE_3_END) {
      // Map nametable 3 to second KB of nametable memory
      return {&mNametableMemory, address - NAMETABLE_3_START + NAMETABLE_SIZE};
    }
  } else {
    throw std::invalid_argument("Invalid mirroring mode");
  }
}

uint8_t Mapper::readPRG(uint16_t address) {
  MemoryLocation location = mMapPRG(address);
  return location.memory->read(location.address);
};

void Mapper::writePRG(uint16_t address, uint8_t value) {
  MemoryLocation location = mMapPRG(address);
  location.memory->write(location.address, value);
};

uint8_t Mapper::readCHR(uint16_t address) {
  MemoryLocation location = mMapCHR(address);
  return location.memory->read(location.address);
};

void Mapper::writeCHR(uint16_t address, uint8_t value) {
  MemoryLocation location = mMapCHR(address);
  location.memory->write(location.address, value);
};

void Mapper::loadPRGROM(const uint8_t* data, size_t size) {
  mPrgRom.load(data, size);
}

void Mapper::loadCHRROM(const uint8_t* data, size_t size) {
  mChrMemory->load(data, size);
}
