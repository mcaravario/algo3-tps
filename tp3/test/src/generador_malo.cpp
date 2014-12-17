#include "kpmp.h"
#define PESO_MAX 100

int main (int argc, char **argv) {
	
	if (argc < 4) {
		cout << "Se deben usar al menos 3 parámetros: cantidad de centrales y satélites, cantidad de  conjuntos, y la semilla." << endl;
		return 0;
	}

	int c = atoi(argv[1]);
	int satelites = atoi(argv[2]);
	int k = atoi(argv[3]);
	int s = atoi(argv[4]);

  /* Inicializo la semilla. */	
	srand(s);

	int peso_min = rand() % PESO_MAX;

	list<arista> aristas;

	/* Conecto los centrales entre ellos. */
	for (int i = 1; i < c+1; i++) {
		for (int j = i+1; j < c+1; j++) {
			aristas.push_back(arista(i, j, peso_min));
 		}
	}

	/*Conecto a los satélites con los centrales. */
	for (int i = c+1; i < satelites + c + 1; i++){
		for (int j = 1; j < c+1; j++){
			aristas.push_back(arista(i, j, rand() % PESO_MAX));
		}
	}


	cout << c + satelites << " " << aristas.size() << " " << k << endl;
	mostrar_aristas(aristas);

	return 0;
}
