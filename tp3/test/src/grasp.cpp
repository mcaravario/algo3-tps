#include "grasp.h"
#include <chrono>

int main(int argc, char** argv){
	
	if (argc < 7) {
		cout << "Se necesitan como parámetros: semilla, modo de uso de grasp, modo de uso del goloso aleatorio, cantidad de iteraciones para grasp, el parametro aleatorio del goloso y iteraciones para el test.." << endl;
		return 0;
	}

	int n, m, k, u, v, w, semilla, m_uso_grasp, m_uso_gol, it_grasp, cant_elegir, iteraciones_test;
	cin >> n;
	cin >> m;
	cin >> k;
	list<arista> aristas;
	semilla = atoi(argv[1]);
	m_uso_grasp	= atoi(argv[2]);
	m_uso_gol	= atoi(argv[3]);
	it_grasp	= atoi(argv[4]);
	cant_elegir	= atoi(argv[5]);


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
		iniciar_grasp(aristas, n, k, semilla, m_uso_grasp, m_uso_gol, it_grasp, cant_elegir);
		auto t_final = reloj.now();
		
		auto t_total = duration_cast<microseconds>(t_final - t_inicial).count();
		
		if ((unsigned int) t_total < minimo) minimo = t_total;
		iteraciones_test--; 
	}

	cout << n << " " << k << " " << minimo << endl;	

	return 0;
}
