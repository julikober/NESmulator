SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include
TESTDIR = testing

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

# All
all: dirs $(BUILDDIR)/main

# Memory
MEMORY = memory

$(BUILDDIR)/$(MEMORY)/memory.o: $(SRCDIR)/$(MEMORY)/memory.cpp $(INCLUDEDIR)/$(MEMORY)/memory.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(MEMORY)/exceptions.o: $(SRCDIR)/$(MEMORY)/exceptions.cpp $(INCLUDEDIR)/$(MEMORY)/exceptions.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(MEMORY)/memory.a: $(BUILDDIR)/$(MEMORY)/memory.o $(BUILDDIR)/$(MEMORY)/exceptions.o
	ar rcs $@ $^

# Cartridge
CARTRIDGE = cartridge
CARTRIDGE_MAPPER = $(CARTRIDGE)/mapper
CARTRIDGE_MEMORY = $(CARTRIDGE)/memory

CARTRIDGE_MAPPER_MAPPERS = $(CARTRIDGE_MAPPER)/mappers
CARTRIDGE_MAPPER_MAPPERS_FILES = $(wildcard $(SRCDIR)/$(CARTRIDGE_MAPPER_MAPPERS)/*.cpp)
CARTRIDGE_MAPPER_MAPPERS_OBJS = $(patsubst $(SRCDIR)/$(CARTRIDGE_MAPPER_MAPPERS)/%.cpp, $(BUILDDIR)/$(CARTRIDGE_MAPPER_MAPPERS)/%.o, $(CARTRIDGE_MAPPER_MAPPERS_FILES))

$(BUILDDIR)/$(CARTRIDGE_MEMORY)/ram.o: $(SRCDIR)/$(CARTRIDGE_MEMORY)/ram.cpp $(INCLUDEDIR)/$(CARTRIDGE_MEMORY)/ram.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CARTRIDGE_MEMORY)/rom.o: $(SRCDIR)/$(CARTRIDGE_MEMORY)/rom.cpp $(INCLUDEDIR)/$(CARTRIDGE_MEMORY)/rom.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CARTRIDGE_MAPPER)/mapper.o: $(SRCDIR)/$(CARTRIDGE_MAPPER)/mapper.cpp $(INCLUDEDIR)/$(CARTRIDGE_MAPPER)/mapper.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CARTRIDGE_MAPPER)/exceptions.o: $(SRCDIR)/$(CARTRIDGE_MAPPER)/exceptions.cpp $(INCLUDEDIR)/$(CARTRIDGE_MAPPER)/exceptions.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CARTRIDGE_MAPPER_MAPPERS)/%.o: $(SRCDIR)/$(CARTRIDGE_MAPPER_MAPPERS)/%.cpp $(INCLUDEDIR)/$(CARTRIDGE_MAPPER)/mapper.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CARTRIDGE)/cartridge.a: $(BUILDDIR)/$(CARTRIDGE_MEMORY)/ram.o $(BUILDDIR)/$(CARTRIDGE_MEMORY)/rom.o $(BUILDDIR)/$(CARTRIDGE_MAPPER)/mapper.o $(BUILDDIR)/$(CARTRIDGE_MAPPER)/exceptions.o $(CARTRIDGE_MAPPER_MAPPERS_OBJS)
	ar rcs $@ $^



# CPU
CPU = cpu
CPU_MEMORY = $(CPU)/memory

CPU_MEMORY_SECTIONS = $(CPU_MEMORY)/sections
CPU_MEMORY_SECTIONS_FILES = $(wildcard $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/*.cpp)
CPU_MEMORY_SECTIONS_OBJS = $(patsubst $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/%.cpp, $(BUILDDIR)/$(CPU_MEMORY_SECTIONS)/%.o, $(CPU_MEMORY_SECTIONS_FILES))

INSTRUCTIONS = $(CPU)/instructions
INSTRUCTION_FILES = $(wildcard $(SRCDIR)/$(INSTRUCTIONS)/*.cpp)
INSTRUCTION_OBJS = $(patsubst $(SRCDIR)/$(INSTRUCTIONS)/%.cpp, $(BUILDDIR)/$(INSTRUCTIONS)/%.o, $(INSTRUCTION_FILES))

$(BUILDDIR)/$(CPU_MEMORY)/memory.o: $(SRCDIR)/$(CPU_MEMORY)/memory.cpp $(INCLUDEDIR)/$(CPU_MEMORY)/memory.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU_MEMORY)/ram.o: $(SRCDIR)/$(CPU_MEMORY)/ram.cpp $(INCLUDEDIR)/$(CPU_MEMORY)/ram.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU_MEMORY_SECTIONS)/%.o: $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/%.cpp $(INCLUDEDIR)/$(CPU_MEMORY)/memory.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/operations.o: $(SRCDIR)/$(CPU)/operations.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/addressing.o: $(SRCDIR)/$(CPU)/addressing.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(INSTRUCTIONS)/%.o: $(SRCDIR)/$(INSTRUCTIONS)/%.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.o: $(SRCDIR)/$(CPU)/cpu.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.a: $(BUILDDIR)/$(CPU)/cpu.o $(BUILDDIR)/$(CPU_MEMORY)/memory.o $(BUILDDIR)/$(CPU_MEMORY)/ram.o $(CPU_MEMORY_SECTIONS_OBJS) $(BUILDDIR)/$(CPU)/operations.o $(BUILDDIR)/$(CPU)/addressing.o $(INSTRUCTION_OBJS)
	ar rcs $@ $^

# PPU
PPU = ppu
PPU_MEMORY = $(PPU)/memory

$(BUILDDIR)/$(PPU_MEMORY)/memory.o: $(SRCDIR)/$(PPU_MEMORY)/memory.cpp $(INCLUDEDIR)/$(PPU_MEMORY)/memory.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU_MEMORY)/nametables.o : $(SRCDIR)/$(PPU_MEMORY)/nametables.cpp $(INCLUDEDIR)/$(PPU_MEMORY)/nametables.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU)/registers.o: $(SRCDIR)/$(PPU)/registers.cpp $(INCLUDEDIR)/$(PPU)/ppu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU)/ppu.o: $(SRCDIR)/$(PPU)/ppu.cpp $(INCLUDEDIR)/$(PPU)/ppu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU)/ppu.a: $(BUILDDIR)/$(PPU)/ppu.o $(BUILDDIR)/$(PPU_MEMORY)/memory.o $(BUILDDIR)/$(PPU_MEMORY)/nametables.o $(BUILDDIR)/$(PPU)/registers.o
	ar rcs $@ $^

# Logger
LOGGER = logger
$(BUILDDIR)/$(LOGGER)/logger.o: $(SRCDIR)/$(LOGGER)/logger.cpp $(INCLUDEDIR)/$(LOGGER)/logger.hpp
	g++ $(CPPFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR)/*

# Dirs
dirs: 
	mkdir -p $(BUILDDIR)/$(MEMORY) $(BUILDDIR)/$(CARTRIDGE) $(BUILDDIR)/$(CARTRIDGE_MEMORY) $(BUILDDIR)/$(CARTRIDGE_MAPPER) $(BUILDDIR)/$(CARTRIDGE_MAPPER_MAPPERS) $(BUILDDIR)/$(CPU) $(BUILDDIR)/$(CPU_MEMORY) $(BUILDDIR)/$(CPU_MEMORY_SECTIONS) $(BUILDDIR)/$(INSTRUCTIONS) $(BUILDDIR)/$(PPU) $(BUILDDIR)/$(PPU_MEMORY) $(BUILDDIR)/$(LOGGER)

# Main
$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/$(MEMORY)/memory.a $(BUILDDIR)/$(CARTRIDGE)/cartridge.a $(BUILDDIR)/$(CPU)/cpu.a $(BUILDDIR)/$(PPU)/ppu.a $(BUILDDIR)/$(LOGGER)/logger.o
	g++ $(CPPFLAGS) $^ -o $@

# Run
run: all
	$(BUILDDIR)/main

# Test
$(BUILDDIR)/test: $(TESTDIR)/test.cpp $(BUILDDIR)/$(CPU)/cpu.a $(BUILDDIR)/$(LOGGER)/logger.o
	g++ $(CPPFLAGS) $^ -o $@

test: $(BUILDDIR)/test
	$(BUILDDIR)/test
