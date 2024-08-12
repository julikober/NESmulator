SRCDIR = src
BUILDDIR = build
INCLUDEDIR = include

CPPFLAGS = -Wall -std=c++17 -I $(INCLUDEDIR)

all: clean $(BUILDDIR)/main

$(BUILDDIR)/cpu.o: $(SRCDIR)/cpu.cpp
	g++ $(CPPFLAGS) -c $(SRCDIR)/cpu.cpp -o $(BUILDDIR)/cpu.o

$(BUILDDIR)/main: $(SRCDIR)/main.cpp $(BUILDDIR)/cpu.o
	g++ $(CPPFLAGS) $(BUILDDIR)/cpu.o -o $(BUILDDIR)/main

clean:
	rm -rf $(BUILDDIR)/*

run: all
	$(BUILDDIR)/main