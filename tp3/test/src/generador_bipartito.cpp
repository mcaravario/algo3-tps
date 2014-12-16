#include <iostream>
#include <list>
#include <algorithm>
#include <random>


#define MAX_PESO 100
using namespace std;

struct arista{
	int n1;
	int n2;
	int peso;
	arista(int a, int b, int c): n1(a), n2(b), peso(c) {}
	arista() : n1(0), n2(0), peso(0) {}
};

ostream& operator<<(ostream& os, arista a){
	os << a.n1 << " " << a.n2 << " " << a.peso << endl;
	return os;
}

/**
* Crea un grafo bipartito de forma aleatoria.
**/
void generar_bipartito(int n, int k){
	/* Aristas que forman el grafo.*/
	list<arista> aristas;

	/* Determino el tamaño de los conjuntos. */	
	int c1 = rand() % n;
	if (c1 == 0 || c1 == n-1) c1 = n/2;

	
	/* Armo las aristas de forma aleatoria. */
	for (int i = 0; i < c1; i++){
		for (int j = c1; j < n; j++){
			int moneda = rand();
			if (moneda % 2) aristas.push_back(arista(i+1, j+1, moneda % MAX_PESO));
		}
	}
			
	cout << n << " " << aristas.size() << " " << k << endl;

	for(auto it = aristas.begin(); it != aristas.end(); it++){
		cout << *it;
	}
}

/* Recibe la cantidad de nodos (n), cantidad de aristas (m) , cantidad de conjuntos (k) y una semilla */
int main(int argc, char** argv){
	if (argc < 4) {
		cout << "Se necesitan más parámetros." << endl;
		return 0;
	}

	int cant_nodos, semilla, k;
	cant_nodos = atoi(argv[1]);

	if (cant_nodos < 2) {
		cout << "La cantidad de nodos debe ser al menos 2." << endl;
		return 0;
	}
	
	k = atoi(argv[2]);
	semilla = atoi(argv[3]);
	srand(semilla);
	generar_bipartito(cant_nodos, k);
	
	return 0;
}
