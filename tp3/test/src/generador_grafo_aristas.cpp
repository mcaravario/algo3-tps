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
* El algoritmo toma elige dos nodos al azar y ubica una arista entre ellos.
* Para solamente cuando m alcanza 0.
**/
void generar_grafo(int n, int m, int k, int s){
	/* Aristas que forman el grafo.*/
	list<arista> aristas;

	/* Las aristas candidatos. */
	int tam = (n*(n-1))/2;
	vector<arista> posibles_aristas(tam);	
	
	/* Completo con los candidatos. */
	int posicion = 0;
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			posibles_aristas[posicion] = arista(i+1, j+1, rand() % MAX_PESO);
			posicion++;
		}
	}

	/* Mezclo las aristas.*/
	shuffle(posibles_aristas.begin(), posibles_aristas.end(), default_random_engine(s));

	for (int i = 0; i < m; i++) {
		aristas.push_back(posibles_aristas[i]);
	}

	cout << n << " " << m << " " << k << endl;

	for(auto it = aristas.begin(); it != aristas.end(); it++){
		cout << *it;
	}
}

/* Recibe la cantidad de nodos (n), cantidad de aristas (m) , cantidad de conjuntos (k) y una semilla */
int main(int argc, char** argv){
	if (argc < 5) {
		cout << "Se necesitan más parámetros." << endl;
		return 0;
	}

	int cant_nodos, semilla, k, cant_aristas;
	cant_nodos = atoi(argv[1]);
	cant_aristas = atoi(argv[2]);
	k = atoi(argv[3]);
	semilla = atoi(argv[4]);
	srand(semilla);
	generar_grafo(cant_nodos, cant_aristas, k, semilla);
	
	return 0;
}
