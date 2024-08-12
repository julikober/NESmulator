SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

all: clean $(BUILDDIR)/main

$(BUILDDIR)/instructions/ora.o: $(SRCDIR)/instructions/ora.cpp
	g++ $(CPPFLAGS) -c $(SRCDIR)/instructions/ora.cpp -o $(BUILDDIR)/instructions/ora.o

$(BUILDDIR)/cpu.o: $(SRCDIR)/cpu.cpp $(BUILDDIR)/instructions/ora.o
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu.cpp -o $(BUILDDIR)/cpu.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.o
	g++ $(CPPFLAGS) $(BUILDDIR)/cpu.o -o $(BUILDDIR)/main

clean:
	rm -rf $(BUILDDIR)/*

run: all
	$(BUILDDIR)/main