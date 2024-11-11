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

# CPU
CPU = cpu
CPU_MEMORY = $(CPU)/memory

CPU_MEMORY_SECTIONS = $(CPU_MEMORY)/sections
CPU_MEMORY_SECTIONS_FILES = $(wildcard $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/*.cpp)
CPU_MEMORY_SECTIONS_OBJS = $(patsubst $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/%.cpp, $(BUILDDIR)/$(CPU_MEMORY_SECTIONS)/%.o, $(CPU_MEMORY_SECTIONS_FILES))

INSTRUCTIONS = $(CPU)/instructions
INSTRUCTION_FILES = $(wildcard $(SRCDIR)/$(INSTRUCTIONS)/*.cpp)
INSTRUCTION_OBJS = $(patsubst $(SRCDIR)/$(INSTRUCTIONS)/%.cpp, $(BUILDDIR)/$(INSTRUCTIONS)/%.o, $(INSTRUCTION_FILES))

$(BUILDDIR)/$(CPU_MEMORY)/cpu_memory.o: $(SRCDIR)/$(CPU_MEMORY)/cpu_memory.cpp $(INCLUDEDIR)/$(CPU_MEMORY)/cpu_memory.hpp $(BUILDDIR)/$(MEMORY)/memory.o
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU_MEMORY_SECTIONS)/%.o: $(SRCDIR)/$(CPU_MEMORY_SECTIONS)/%.cpp $(INCLUDEDIR)/$(CPU_MEMORY)/cpu_memory.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/operations.o: $(SRCDIR)/$(CPU)/operations.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/addressing.o: $(SRCDIR)/$(CPU)/addressing.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(INSTRUCTIONS)/%.o: $(SRCDIR)/$(INSTRUCTIONS)/%.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.o: $(SRCDIR)/$(CPU)/cpu.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.a: $(BUILDDIR)/$(CPU)/cpu.o $(BUILDDIR)/$(CPU_MEMORY)/cpu_memory.o $(CPU_MEMORY_SECTIONS_OBJS) $(BUILDDIR)/$(CPU)/operations.o $(BUILDDIR)/$(CPU)/addressing.o $(INSTRUCTION_OBJS)
	ar rcs $@ $^

# PPU
PPU = ppu

$(BUILDDIR)/$(PPU)/registers.o: $(SRCDIR)/$(PPU)/registers.cpp $(INCLUDEDIR)/$(PPU)/ppu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU)/ppu.o: $(SRCDIR)/$(PPU)/ppu.cpp $(INCLUDEDIR)/$(PPU)/ppu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(PPU)/ppu.a: $(BUILDDIR)/$(PPU)/ppu.o $(BUILDDIR)/$(PPU)/registers.o
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
	mkdir -p $(BUILDDIR)/$(MEMORY) $(BUILDDIR)/$(CPU) $(BUILDDIR)/$(CPU_MEMORY) $(BUILDDIR)/$(CPU_MEMORY_SECTIONS) $(BUILDDIR)/$(INSTRUCTIONS) $(BUILDDIR)/$(PPU) $(BUILDDIR)/$(LOGGER)

# Main
$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/$(CPU)/cpu.a $(BUILDDIR)/$(PPU)/ppu.a $(BUILDDIR)/$(LOGGER)/logger.o
	g++ $(CPPFLAGS) $^ -o $@

# Run
run: all
	$(BUILDDIR)/main

# Test
$(BUILDDIR)/test: $(TESTDIR)/test.cpp $(BUILDDIR)/$(CPU)/cpu.a $(BUILDDIR)/$(LOGGER)/logger.o
	g++ $(CPPFLAGS) $^ -o $@

test: $(BUILDDIR)/test
	$(BUILDDIR)/test
