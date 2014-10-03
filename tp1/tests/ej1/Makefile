CXXFLAGS=-Wall -Wextra -Werror -pedantic -ggdb

all: ejercicio1

%: src/%.cpp src/%.h
	$(CXX) $(CXXFLAGS) -o $@ $<
	mv $@ bin/
