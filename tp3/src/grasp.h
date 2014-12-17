#include "busqueda_local_aleatorio.h"
#include "goloso_rand.h"


void  grasp(vector<vector<int> >& mz_ady, vector<conjunto>& partes, list<int>& candidatos, vector<int>& vistos, int k, int semilla, int modo_uso_grasp, int modo_uso_goloso, int it_grasp, int cant_elegir){

	vector<conjunto> res(k);	
	/* Esto es para que la primer iteración funcione. */
	res[0].peso = MAX_INT;
	
	if(modo_uso_grasp){
		
		int contador = it_grasp;
		while(contador != 0){
			vector<conjunto> res_2 = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir, semilla, modo_uso_goloso);
			busquedaLocal_1opt(res_2, mz_ady, k);
	
			if(suma_total(res_2) < suma_total(res)) {
				contador = it_grasp;
			} else {
				contador--;
			}
		}
	} else {

		while(it_grasp != 0){
			vector<conjunto> res_2 = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir, semilla, modo_uso_goloso);
			busquedaLocal_1opt(res_2, mz_ady, k);
	
			if(suma_total(res_2) < suma_total(res)) {
 				res = res_2;
			}
			it_grasp--;
		}
	}
}

/**
* Inicializa las estructuras necesarias para grasp y llama a la funcion que hace el trabajo.
*	 Forma de uso:
*		- modo_uso_grasp = 0 --> k iteraciones fijas (it_grasp)
*		- modo_uso_grasp = 1 --> no hay mejora en k iteraciones (it_grasp)
*		- modo_uso_goloso = 0 --> elegir random entre bolsas
*		- modo_uso_goloso = 1 --> elegir random entre nodos
**/
vector<int> iniciar_grasp(list<arista>& aristas, int n, int k, int semilla, int modo_uso_grasp, int modo_uso_goloso, int it_grasp, int cant_elegir){

	vector<int> vistos(n);
	vector<conjunto> partes(k);
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;

	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	grasp(mz_ady, partes, candidatos, vistos, k, semilla, modo_uso_grasp, modo_uso_goloso, it_grasp, cant_elegir);
	
	return vistos;
}
