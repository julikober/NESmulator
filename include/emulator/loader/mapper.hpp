#pragma once

#include "cartridge/mapper/mappers/mappers.hpp"

Mapper* createMapper(uint8_t mapperID, NameTablesMemory& nametableMemory,
                     uint8_t prgRomBanks, uint8_t chrRomBanks,
                     MirroringMode mirroringMode, bool hasBatteryBackedRam,
                     bool hasTrainer, bool hasAlternativeMirroring);
