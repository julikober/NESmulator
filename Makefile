SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include
TESTDIR = testing

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR) -g

INSTRUCTION_FILES = $(wildcard $(SRCDIR)/cpu/instructions/*.cpp)
INSTRUCTION_OBJS = $(patsubst $(SRCDIR)/cpu/instructions/%.cpp, $(BUILDDIR)/cpu/instructions/%.o, $(INSTRUCTION_FILES))

all: $(BUILDDIR)/main

$(BUILDDIR)/memory.o: $(SRCDIR)/memory.cpp $(INCLUDEDIR)/memory.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/memory.o $(SRCDIR)/memory.cpp

$(BUILDDIR)/cpu/cpu_memory.o: $(SRCDIR)/cpu/cpu_memory.cpp $(INCLUDEDIR)/cpu/cpu_memory.hpp $(INCLUDEDIR)/memory.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/cpu_memory.o $(SRCDIR)/cpu/cpu_memory.cpp

$(BUILDDIR)/cpu/cpu.o: $(SRCDIR)/cpu/cpu.cpp $(INCLUDEDIR)/cpu/cpu.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/cpu.o $(SRCDIR)/cpu/cpu.cpp

$(BUILDDIR)/cpu/instructions.o: $(SRCDIR)/cpu/instructions.cpp $(INCLUDEDIR)/cpu/cpu.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/instructions.o $(SRCDIR)/cpu/instructions.cpp

$(BUILDDIR)/cpu/instructions/%.o: $(SRCDIR)/cpu/instructions/%.cpp $(INCLUDEDIR)/cpu/cpu.hpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/cpu/operations.o: $(SRCDIR)/cpu/operations.cpp $(INCLUDEDIR)/cpu/cpu.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/operations.o $(SRCDIR)/cpu/operations.cpp

$(BUILDDIR)/cpu.a: $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(INSTRUCTION_OBJS) $(BUILDDIR)/cpu/operations.o $(BUILDDIR)/cpu/cpu_memory.o $(BUILDDIR)/memory.o
	ar rcs $(BUILDDIR)/cpu.a $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(INSTRUCTION_OBJS) $(BUILDDIR)/cpu/operations.o $(BUILDDIR)/cpu/cpu_memory.o $(BUILDDIR)/memory.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a
	g++ $(CPPFLAGS) -o $(BUILDDIR)/main $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a

$(BUILDDIR)/test: $(TESTDIR)/test.cpp $(BUILDDIR)/cpu.a
	g++ $(CPPFLAGS) -ljsoncpp -o $(BUILDDIR)/test $(TESTDIR)/test.cpp $(BUILDDIR)/cpu.a

test: $(BUILDDIR)/test
	$(BUILDDIR)/test

clean:
	rm -rf $(BUILDDIR)/* && mkdir -p $(BUILDDIR)/cpu/instructions

run: all
	$(BUILDDIR)/main