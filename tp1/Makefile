CXX=g++
CXXFLAGS=-Wall -g -Werror -pedantic
OBJ=bin/ej1.o bin/ej2.o bin/ej3.o 

tp:
	make -C src

#bin/%.o: src/%.cpp 
#	$(CC) -c -o $@ $< $(CFLAGS)
#bin/ej1: bin/ej1.o
#	$(CXX) $(CXXFLAGS) -o bin/ej1
#bin/ej2: bin/ej2.o
#	$(CXX) $(CXXFLAGS) -o bin/ej2
#bin/ej3: bin/ej3.o
#	$(CXX) $(CXXFLAGS) -o bin/ej3

all: bin/ej1 bin/ej2 bin/ej3

clean: 
	rm bin/ejercicio1 bin/ejercicio2 bin/ejercicio3
