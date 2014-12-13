#include "busqueda_local_aleatorio.h"
#include "goloso_rand.h"


void  grasp(vector<vector<int> >& mz_ady, vector<conjunto>& partes, list<int>& candidatos, int k, vector<int>& vistos, int iteraciones, int cant_elegir, int semilla){

	vector<conjunto> res(k);	
	/* Esto es para que la primer iteración funcione. */
	res[0].peso = MAX_INT;
	
	while(iteraciones != 0){
		vector<conjunto> res_2 = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir, semilla);
		busquedaLocal_1opt(res_2, mz_ady, k);
	
		if(suma_total(res_2) < suma_total(res)) res = res_2;
		iteraciones--;	
	}
}

/* Inicializa las estructuras necesarias para grasp y llama a la funcion que hace el trabajo*/
vector<int> iniciar_grasp(list<arista>& aristas, int n, int k, int  iteraciones, int cant_elegir, int semilla){

	vector<int> vistos(n);
	vector<conjunto> partes(k);
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;

	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	grasp(mz_ady, partes, candidatos, k, vistos, iteraciones, cant_elegir, semilla);
	
	return vistos;
}
