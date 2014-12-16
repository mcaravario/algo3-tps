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
* Crea un arbol de forma aleatoria.
**/
void generar_arbol(int n, int k){
	/* Aristas que forman el grafo.*/
	list<arista> aristas;

	int nodo_actual = 0;
	int contador = 1;
	
	for (int i = 0; i < n-1; i++){
		aristas.push_back(arista(nodo_actual+1, contador+1, rand() % MAX_PESO));
		if (rand() % 2) nodo_actual = contador;
		contador++;
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
	generar_arbol(cant_nodos, k);
	
	return 0;
}
