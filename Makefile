SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

all: clean $(BUILDDIR)/main

# Instructions
# ADC
$(BUILDDIR)/instructions/adc.o: $(SRCDIR)/cpu/instructions/adc.cpp
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu/instructions/adc.cpp -o $(BUILDDIR)/instructions/adc.o

# ASL
$(BUILDDIR)/instructions/asl.o: $(SRCDIR)/cpu/instructions/asl.cpp
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu/instructions/asl.cpp -o $(BUILDDIR)/instructions/asl.o

# ORA
$(BUILDDIR)/instructions/ora.o: $(SRCDIR)/cpu/instructions/ora.cpp
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu/instructions/ora.cpp -o $(BUILDDIR)/instructions/ora.o


# CPU
$(BUILDDIR)/cpu.o: $(SRCDIR)/cpu.cpp $(BUILDDIR)/instructions/adc.o $(BUILDDIR)/instructions/asl.o $(BUILDDIR)/instructions/ora.o
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu.cpp -o $(BUILDDIR)/cpu.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.o
	g++ $(CPPFLAGS) $(BUILDDIR)/cpu.o -o $(BUILDDIR)/main

clean:
	rm -rf $(BUILDDIR)/*

run: all
	$(BUILDDIR)/main