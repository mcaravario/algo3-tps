#include "grasp.h"
#include <chrono>

int main(int argc, char** argv){
	
	if (argc < 6) {
		cout << "Se necesitan como parámetros: semilla, modo de uso de grasp, modo de uso del goloso aleatorio, cantidad de iteraciones para grasp, y el parametro aleatorio del goloso." << endl;
		return 0;
	}

	int n, m, k, u, v, w, semilla, m_uso_grasp, m_uso_gol, it_grasp, cant_elegir;
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

	auto t_i = reloj.now();
	int peso = 	peso_grasp(aristas, n, k, semilla, m_uso_grasp, m_uso_gol, it_grasp, cant_elegir);
	auto t_f = reloj.now();

	cout << n << " " << peso << " " << duration_cast<microseconds>(t_f - t_i).count() << endl;	

	return 0;
}
