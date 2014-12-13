#include "grasp.h"
#include <chrono>

int main(int argc, char** argv){
	
	if(argc < 4) {
		cout << "Se necesitan como parámetros: iteraciones, cant_elegir, semilla e iteraciones del test." << endl;
		return 0;
	}

	int n, m, k, u, v, w, iteraciones, cant_elegir, semilla, iteraciones_test;
	cin >> n;
	cin >> m;
	cin >> k;
	list<arista> aristas;
	iteraciones = atoi(argv[0]);
	cant_elegir = atoi(argv[1]);
	semilla = atoi(argv[2]);
	iteraciones_test = atoi(argv[3]);


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
	size_t minimo = MAX_INT;

	while (iteraciones_test > 0) {
		auto t_inicial = reloj.now();
		iniciar_grasp(aristas, n, k, iteraciones, cant_elegir, semilla);
		auto t_final = reloj.now();
		
		auto t_total = duration_cast<microseconds>(t_final - t_inicial).count();
		
		if ((unsigned int) t_total < minimo) minimo = t_total;
		iteraciones_test--; 
	}

	cout << n << " " << k << " " << minimo << endl;	

	return 0;
}
