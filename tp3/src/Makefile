CXXFLAGS=-Wall -Wextra -Werror -pedantic -ggdb -std=c++0x
BINDIR=../bin
#BINS=ejercicio1 ejercicio2 ejercicio3
BINS=exacto goloso grasp 


.PHONY: all clean

all: $(BINS)
	mv $(BINS) $(BINDIR)

clean:
	rm $(BINDIR)/goloso
	rm $(BINDIR)/exacto
	rm $(BINDIR)/grasp
