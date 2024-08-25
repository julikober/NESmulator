SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

INSTRUCTION_FILES = $(wildcard $(SRCDIR)/cpu/instructions/*.cpp)
INSTRUCTION_OBJS = $(patsubst $(SRCDIR)/cpu/instructions/%.cpp, $(BUILDDIR)/cpu/instructions/%.o, $(INSTRUCTION_FILES))

all: clean $(BUILDDIR)/main

$(BUILDDIR)/cpu/cpu.o: $(SRCDIR)/cpu/cpu.cpp $(INCLUDEDIR)/cpu.hpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/cpu.o $(SRCDIR)/cpu/cpu.cpp

$(BUILDDIR)/cpu/instructions.o: $(SRCDIR)/cpu/instructions.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/instructions.o $(SRCDIR)/cpu/instructions.cpp

$(BUILDDIR)/cpu/instructions/%.o: $(SRCDIR)/cpu/instructions/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/cpu/operations.o: $(SRCDIR)/cpu/operations.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/operations.o $(SRCDIR)/cpu/operations.cpp

$(BUILDDIR)/cpu.a: $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(INSTRUCTION_OBJS) $(BUILDDIR)/cpu/operations.o
	ar rcs $(BUILDDIR)/cpu.a $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(INSTRUCTION_OBJS) $(BUILDDIR)/cpu/operations.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a
	g++ $(CPPFLAGS) -o $(BUILDDIR)/main $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a

run: all
	$(BUILDDIR)/main