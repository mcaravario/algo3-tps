CXXFLAGS=-Wall -Wextra -pedantic -ggdb -std=c++0x
BINDIR=../bin
BINS= busqueda_local_1opt_aleatorio busqueda_local_2opt_aleatorio grafos_completos

.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/busqueda_local_1opt_aleatorio
	rm $(BINDIR)/busqueda_local_2opt_aleatorio
	rm $(BINDIR)/grafos_completos
