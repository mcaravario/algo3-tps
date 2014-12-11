#include "grasp.h"

int main(int argc, char** argv){
	
	if(argc < 3) return 0;
				
	int n, m, k, u, v, w, iteraciones, cant_elegir, semilla;
	cin >> n;
	cin >> m;
	cin >> k;
	list<arista> aristas;
	iteraciones = atoi(argv[0]);
	cant_elegir = atoi(argv[1]);
	semilla = atoi(argv[2]);


	/* Creo la lista de aristas */
	for (int i = 0; i < m; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		u--;
		v--;
		aristas.push_back(arista(u,v,w));
	}

	/* Funcion que resuelve el ejercicio */
	vector<int> posiciones = iniciar_grasp(aristas, n, k, iteraciones, cant_elegir, semilla);

	/* Imprimo por salida esandar el resulado. */
	mostrar_res(posiciones);
	return 0;
}
