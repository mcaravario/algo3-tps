#include "kpmp.h"
#define PESO_MAX 100

int main (int argc, char **argv) {
	
	if (argc < 3) {
		cout << "Se deben usar al menos 3 parámetros: cantidad de nodos, cantidad de  conjuntos, y la semilla." << endl;
		return 0;
	}

	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	int s = atoi(argv[3]);

	if (n < 4) {
		cout << "La cantidad de nodos debe ser mayor a 3." << endl;
		return 0;
	}

  /* Inicializo la semilla. */	
	srand(s);

	/**
	 * 	Los nodos A y B van a ser los nodos pesados de cada subgrafo.
	 * Para ver la definición del grafo, mirar el informe.
	 * */
	int A = 0;
	int B = 1;
	int peso_min = rand() % PESO_MAX;

	/* Primero necesito que existan al menos 2 aristas para cada nodo central,
	 * una que una los nodos centrales (C), y otra adyacente a cada uno de ellos 
	 * (cuyo peso sea menor a la C).
	 **/

	list<arista> aristas;
	aristas.push_back(arista(A, B, peso_min));
	for (int i_nodo = 2; i_nodo < n; i_nodo++) {
		aristas.push_back(arista(i_nodo, A, (rand() % PESO_MAX) + peso_min));
		aristas.push_back(arista(i_nodo, B, (rand() % PESO_MAX) + peso_min));
	}

	cout << n << " " << aristas.size() << " " << k << endl;
	mostrar_aristas(aristas);

	return 0;
}
