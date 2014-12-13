CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++0x
BINDIR=../bin
BINS= exacto pexacto goloso pgoloso busqueda_local_1opt_aleatorio busqueda_local_2opt_aleatorio grasp generador_grafo

.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/goloso
	rm $(BINDIR)/exacto
	rm $(BINDIR)/grasp
	rm $(BINDIR)/pexacto
	rm $(BINDIR)/generador_grafo
