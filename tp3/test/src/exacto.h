#include "kpmp.h"

/* Sirve para saber si ya encontre una solución.  */
bool hay_una;

/**
* Indica si la sub-solución (al agregarle un elemento) sigue 
*	siendo solución. Es decir, si el peso total resultante de
*	agregar al nuevo elemento supera el de la solución obtenida
*	anteriormente.
**/
bool es_solucion(vector<conjunto>& res, vector<conjunto>& ss, conjunto& p, nodo n, vector<vector<int> > mz_ady){
	if (!hay_una) return true;
	int cota_max = suma_total(res);
	int acumulado = suma_total(ss);
	int peso_agregado = peso_asociado(p, mz_ady, n);
	return cota_max > acumulado + peso_agregado;
}


/**
* Calcula la partición (de tamaño maximo bolsas.size) que optimiza
*	(minimiza) la suma de pesos totales.
**/
void mejor_particion(vector<conjunto>& res, vector<conjunto>& bolsas, list<nodo> candidatos, vector<vector<int> >& mz_ady) {
	if (candidatos.size() == 0) {
		res = bolsas;
		hay_una = true;
	}else {
		nodo elegido = *candidatos.begin();
		candidatos.pop_front();
		for (unsigned int i = 0; i < bolsas.size(); i++){
			bolsas[i].elementos.push_back(elegido);
			/* Si sigue siendo una solución, exploro la rama.*/
			if (es_solucion(res, bolsas, bolsas[i], elegido, mz_ady)){
				bolsas[i].peso += peso_asociado(bolsas[i], mz_ady, elegido);
				mejor_particion(res, bolsas, candidatos, mz_ady);
				bolsas[i].peso -= peso_asociado(bolsas[i], mz_ady, elegido);
			}
			bolsas[i].elementos.pop_back();
		}
	}
}



/**
* Calcula la partición (de tamaño maximo bolsas.size) que optimiza
*	(minimiza) la suma de pesos totales.
**/
void mejor_particion_poda(vector<conjunto>& res, vector<conjunto>& bolsas, list<nodo> candidatos, vector<vector<int> >& mz_ady) {
	if (candidatos.size() == 0) {
		res = bolsas;
		hay_una = true;
	}else {
		nodo elegido = *candidatos.begin();
		candidatos.pop_front();
		for (unsigned int i = 0; i < bolsas.size(); i++){
			bolsas[i].elementos.push_back(elegido);
			int tam = bolsas[i].elementos.size();
			/* Si sigue siendo una solución, exploro la rama.*/
			if (es_solucion(res, bolsas, bolsas[i], elegido, mz_ady)){
				bolsas[i].peso += peso_asociado(bolsas[i], mz_ady, elegido);
				mejor_particion(res, bolsas, candidatos, mz_ady);
				bolsas[i].peso -= peso_asociado(bolsas[i], mz_ady, elegido);
			}
			bolsas[i].elementos.pop_back();
			/* Poda para no repetir soluciones. */
			if (tam == 1) i = bolsas.size();
		}
	}
}


vector<int> iniciar_exacto(list<arista> aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);

	/* Creo la partición resultado, y la particion parcial. */
	vector<conjunto> res(k);
	vector<conjunto> bolsas(k);

	/* Creacion de la lista de nodos. */
	list<nodo> ns;
	for (int i = 0; i < n; i++) ns.push_back(i);

	/* Este flag es necesario para la función es_solucion. */
	hay_una = false;

	/* Funcion que resuelve el ejercicio. */
	mejor_particion(res, bolsas, ns, mz_ady);

	vector<int> posiciones(n);
	
	/* Preparacion del resultado. */
	establecer_posiciones(res, posiciones);
	
	return posiciones;
}

vector<int> iniciar_exacto_poda(list<arista> aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);

	/* Creo la partición resultado, y la particion parcial. */
	vector<conjunto> res(k);
	vector<conjunto> bolsas(k);

	/* Creacion de la lista de nodos. */
	list<nodo> ns;
	for (int i = 0; i < n; i++) ns.push_back(i);

	/* Este flag es necesario para la función es_solucion. */
	hay_una = false;

	/* Funcion que resuelve el ejercicio. */
	mejor_particion_poda(res, bolsas, ns, mz_ady);

	vector<int> posiciones(n);
	
	/* Preparacion del resultado. */
	establecer_posiciones(res, posiciones);
	
	return posiciones;
}

int peso_de_exacto_poda(list<arista> aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);

	/* Creo la partición resultado, y la particion parcial. */
	vector<conjunto> res(k);
	vector<conjunto> bolsas(k);

	/* Creacion de la lista de nodos. */
	list<nodo> ns;
	for (int i = 0; i < n; i++) ns.push_back(i);

	/* Este flag es necesario para la función es_solucion. */
	hay_una = false;

	/* Funcion que resuelve el ejercicio. */
	mejor_particion_poda(res, bolsas, ns, mz_ady);
	
	return suma_total(res);
}
