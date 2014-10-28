#include "string.h"
#include <iostream>
#include <list>
#include <vector>
#include "trie.h"
typedef hora int;
typedef vuelo_id int;

struct vuelo{
	string ori;
	string des;
	hora salida;
	hora llegada;
	vuelo_id id;
}



int ruta_de_vuelo(list<int> res, list<vuelo> vuelos, string origen, string destino);
