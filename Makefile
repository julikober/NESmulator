SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

all: clean $(BUILDDIR)/main

$(BUILDDIR)/cpu/cpu.o: $(SRCDIR)/cpu/cpu.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/cpu.o $(SRCDIR)/cpu/cpu.cpp

$(BUILDDIR)/cpu/instructions.o: $(SRCDIR)/cpu/instructions.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/instructions.o $(SRCDIR)/cpu/instructions.cpp

$(BUILDDIR)/cpu/operations.o: $(SRCDIR)/cpu/operations.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/operations.o $(SRCDIR)/cpu/operations.cpp

$(BUILDDIR)/cpu/instructions/adc.o: $(SRCDIR)/cpu/instructions/adc.cpp
	g++ $(CPPFLAGS) -c -o $(BUILDDIR)/cpu/instructions/adc.o $(SRCDIR)/cpu/instructions/adc.cpp

$(BUILDDIR)/cpu.a: $(INCLUDEDIR)/cpu.hpp $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(BUILDDIR)/cpu/operations.o $(BUILDDIR)/cpu/instructions/adc.o
	ar rcs $(BUILDDIR)/cpu.a $(BUILDDIR)/cpu/cpu.o $(BUILDDIR)/cpu/instructions.o $(BUILDDIR)/cpu/operations.o $(BUILDDIR)/cpu/instructions/adc.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a
	g++ $(CPPFLAGS) -o $(BUILDDIR)/main $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.a

run: all
	$(BUILDDIR)/main