CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++0x
BINDIR=../bin
#BINS=ejercicio1 ejercicio2 ejercicio3
#BINS=exacto goloso grasp pexacto busqueda_local  
BINS= exacto pexacto goloso pgoloso busqueda_local_1opt busqueda_local_2opt grasp

.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/goloso
	rm $(BINDIR)/exacto
	rm $(BINDIR)/grasp
	rm $(BINDIR)/pexacto
