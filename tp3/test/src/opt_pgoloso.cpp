#include "goloso.h"
#include <chrono>

int main(){
	int n,m,k,u,v,w;
	cin >> n;
	cin >> m;
	cin >> k;

	list<arista> aristas;

	/* Creo la lista de aristas */
	for (int i = 0; i < m; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		u--;
		v--;
		aristas.push_back(arista(u,v,w));
	}
	
	using namespace std::chrono;
	high_resolution_clock reloj;
	
	auto t_inicial = reloj.now();
	/* Llamo a la función que resuelve el ejercicio. */
	int peso = peso_de_golosa_ordenada(aristas, n, k);
	auto t_final = reloj.now();

	auto t_total = duration_cast<microseconds>(t_final - t_inicial).count();

  cout << n << " " << peso << " " << t_total << endl; 	
	return 0;
}
