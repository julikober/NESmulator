SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include
TESTDIR = testing

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

# All
all: dirs main

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

$(BUILDDIR)/$(CPU)/instructions.o: $(SRCDIR)/$(CPU)/instructions.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(INSTRUCTIONS)/%.o: $(SRCDIR)/$(INSTRUCTIONS)/%.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.o: $(SRCDIR)/$(CPU)/cpu.cpp $(INCLUDEDIR)/$(CPU)/cpu.hpp
	g++ $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/$(CPU)/cpu.a: $(BUILDDIR)/$(CPU)/cpu.o $(BUILDDIR)/$(CPU_MEMORY)/cpu_memory.o $(CPU_MEMORY_SECTIONS_OBJS) $(BUILDDIR)/$(CPU)/operations.o $(BUILDDIR)/$(CPU)/instructions.o $(INSTRUCTION_OBJS)
	ar rcs $@ $^

# Main
main: $(SRCDIR)/main.cpp $(BUILDDIR)/$(CPU)/cpu.a
	g++ $(CPPFLAGS) $^ -o $(BUILDDIR)/main

# Test
test: testing/test.cpp $(BUILDDIR)/$(CPU)/cpu.a
	$(BUILDDIR)/test

# Clean
clean:
	rm -rf $(BUILDDIR)/*

# Dirs
dirs: 
	mkdir -p $(BUILDDIR)/$(MEMORY) $(BUILDDIR)/$(CPU) $(BUILDDIR)/$(CPU_MEMORY) $(BUILDDIR)/$(CPU_MEMORY_SECTIONS) $(BUILDDIR)/$(INSTRUCTIONS)

# Run
run: all
	$(BUILDDIR)/main