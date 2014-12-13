#include "goloso.h"
#include <chrono>

int main(int argc, char** argv){

	if (argc < 2){
		cout << "Se necesitan las iteraciones como parámetro." << endl;
		return 0;
	} 

	int n, m, k, u, v, w, iteraciones;
	cin >> n;
	cin >> m;
	cin >> k;
	
	iteraciones = atoi(argv[1]);

	list<arista> aristas;
	
	/* Creo la lista de aristas. */
	for (int i = 0; i < m; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		u--;
		v--;
	 	aristas.push_back(arista(u, v, w));
	}

	using namespace std::chrono;
	high_resolution_clock reloj;
	size_t minimo = MAX_INT;

	while (iteraciones > 0) {
		auto t_inicial = reloj.now();
		iniciar_golosa(aristas, n, k); 
		auto t_final = reloj.now();
		
		auto t_total = duration_cast<microseconds>(t_final - t_inicial).count();
		
		if ((unsigned int) t_total < minimo) minimo = t_total;
		iteraciones--; 
	}
	
	cout << n << " " << k << " " << minimo << endl;

	return 0;
}
