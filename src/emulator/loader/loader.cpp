#include "emulator/emulator.hpp"
#include "emulator/loader/mapper.hpp"

void Emulator::loadROMFile(const char* filename) {
  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }

  // Get file size
  file.seekg(0, std::ios::end);
  size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  ROMHeader header;

  // Read header
  file.read(reinterpret_cast<char*>(&header), HEADER_SIZE);

  // Check if first 4 bytes are the standardized starting string of an nes file,
  // which is "NES" followed by 0x1A
  if (header.NesString[0] != 'N' || header.NesString[1] != 'E' ||
      header.NesString[2] != 'S' || header.NesString[3] != 0x1A) {
    throw std::runtime_error("Invalid ROM file");
  }

  if (mMapper != nullptr) {
    delete mMapper;
  }

  // Create new mapper
  mMapper = createMapper(header.flags6 >> 4, mPPU->getNameTablesMemory(),
                         header.PrgRomSize, header.ChrRomSize,
                         static_cast<MirroringMode>(header.flags6 & 1),
                         header.flags6 & (1 << 1), header.flags6 & (1 << 3),
                         header.flags6 & (1 << 4));

  // Read trainder if present
  if (header.flags6 & (1 << 2)) {
    uint8_t trainer[512];

    file.read((char*)trainer, TRAINER_SIZE);

    // ToDo: Implement trainer
  }

  // Read PRG ROM
  uint8_t* prgRom = new uint8_t[header.PrgRomSize * PRG_ROM_BANK_SIZE];
  file.read((char*)(prgRom), header.PrgRomSize * PRG_ROM_BANK_SIZE);

  mMapper->loadPRGROM(prgRom, header.PrgRomSize * PRG_ROM_BANK_SIZE);

  // Read CHR ROM if present
  if (header.ChrRomSize) {
    uint8_t* chrRom = new uint8_t[header.ChrRomSize * CHR_ROM_BANK_SIZE];
    file.read((char*)(chrRom), header.ChrRomSize * CHR_ROM_BANK_SIZE);

    mMapper->loadCHRROM(chrRom, header.ChrRomSize * CHR_ROM_BANK_SIZE);
  }
}
