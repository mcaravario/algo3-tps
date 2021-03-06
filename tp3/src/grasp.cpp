#include "grasp.h"
#include <chrono>

int main(int argc, char** argv){
	
	if (argc < 7) {
		cout << "Se necesitan como parámetros: semilla, modo de uso de grasp, modo de uso del goloso aleatorio, cantidad de iteraciones para grasp, y el parametro aleatorio del goloso." << endl;
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

	mostrar_res(iniciar_grasp(aristas, n, k, semilla, m_uso_grasp, m_uso, gol, it_grasp, cant_elegir));

	return 0;
}
