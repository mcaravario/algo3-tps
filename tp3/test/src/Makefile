CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++0x
BINDIR=../bin
BINS= exacto pexacto goloso pgoloso busqueda_local_1opt_aleatorio busqueda_local_2opt_aleatorio grasp generador_grafo generador_malo grafos_completos generador_arbol generador_bipartito generador_grafo_aristas 

.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/exacto
	rm $(BINDIR)/pexacto
	rm $(BINDIR)/goloso
	rm $(BINDIR)/pgoloso
	rm $(BINDIR)/busqueda_local_1opt_aleatorio
	rm $(BINDIR)/busqueda_local_2opt_aleatorio
	rm $(BINDIR)/grasp
	rm $(BINDIR)/generador_grafo
	rm $(BINDIR)/generador_malo
	rm $(BINDIR)/grafos_completos
	rm $(BINDIR)/generador_arbol
	rm $(BINDIR)/generador_bipartito
	rm $(BINDIR)/generador_grafo_aristas
