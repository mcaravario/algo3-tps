#include <iostream>
#include <list>

#define MAX_PESO 100
using namespace std;

struct arista{
	int n1;
	int n2;
	int peso;
	arista(int a, int b, int c): n1(a), n2(b), peso(c) {}
};

ostream& operator<<(ostream& os, arista a){
	os << a.n1 << " " << a.n2 << " " << a.peso << endl;
	return os;
}

void generar_grafo(int cant, int k){
	list<arista> aristas;
	for (int i = 0; i < cant; i++){
		for (int j = i + 1; j < cant; j++){
			if (rand() % 2){
				aristas.push_back(arista(i+1, j+1, rand() % MAX_PESO));
			}
		} 
	}
	
	cout << cant << " " << aristas.size() << " " << k << endl;

	for(auto it = aristas.begin(); it != aristas.end(); it++){
		cout << *it;
	}
}

/* Recibe la cantidad de nodos, k y una semilla */
int main(int argc, char** argv){
	if (argc < 4) {
		cout << "Se necesitan más parámetros." << endl;
		return 0;
	}
	int cant_nodos, semilla, k;
	cant_nodos = atoi(argv[1]);
	k = atoi(argv[2]);
	semilla = atoi(argv[3]);
	srand(semilla);
	generar_grafo(cant_nodos, k);
	
	return 0;
}
