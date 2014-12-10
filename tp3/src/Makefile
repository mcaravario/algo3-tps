CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++0x
BINDIR=../bin
#BINS=ejercicio1 ejercicio2 ejercicio3
#BINS=exacto goloso grasp pexacto busqueda_local_solo_costosa busqueda_local_todo_k  
BINS=exacto goloso grasp pexacto busqueda_local

.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/goloso
	rm $(BINDIR)/exacto
	rm $(BINDIR)/grasp
	rm $(BINDIR)/pexacto
