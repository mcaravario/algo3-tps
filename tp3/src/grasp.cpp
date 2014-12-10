#include <vector>
#include <list>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <time.h>
#include "busqueda_local.h"

using namespace std;


struct {
	
	bool operator() (tuple<int,int> a, tuple<int,int> b) {
			return get<1>(a) < get<1>(b);
	}

} claseComp;

list<tuple<int,int,int> >::iterator elegir_mayor(list<tuple<int,int,int> >& aristas){
	list<tuple<int,int,int> >::iterator res;
	int max = 0;
	for(auto it = aristas.begin(); it != aristas.end(); it++){
		if(get<2>(*it) >= max){
			max = get<2>(*it);
			res = it;
		}		
	}
	
	return res;

}

/* Devuelve la suma total de pesos */
int suma_total(vector<particion>& partes) {
	int res = 0;
	for (unsigned int i = 0; i < partes.size(); i++){
		res += partes[i].peso;
	}
	return res;	
}


/* Devuelve el peso asociado del nodo v, al conjunto i */
int peso_asociado(int v, vector<particion>& partes, int i,  vector<vector<int> >& mz_ady){
	int res = 0;
	for (auto it = partes[i].elementos.begin(); it != partes[i].elementos.end(); it++){
		if(mz_ady[v][*it] != -1){
			res += mz_ady[v][*it];
		}
	}
	return res;
}

/** 
 * Este algoritmo elige donde ubicar al nodo u de forma golosa y aleatoria,
 * es decir, entre las mejores cant_elegir opciones (conjuntos) elige una
 * al azar y luego ubica al nodo allí.
 **/
void ubicar_en_menor(int u, vector<particion>& partes, int k, vector<vector<int> >& mz_ady, vector<int>& vistos, int cant_elegir){
	
	vector<tuple<int,int> > pesos(k);
	
	/* Creo un arreglo que contegna a una bolsa y el peso de agregar a u a dicha bolsa. */
	for (int i = 0; i<k; i++){																			
		get<0>(pesos[i]) = i;
		get<1>(pesos[i]) = peso_asociado(u, partes, i, mz_ady);
	}
	
	/* Ordeno el arreglo para luego quedarme con los mejores.  */
	sort(pesos.begin(), pesos.end(), claseComp);
	
	/* Eligo de forma aleatoria el conjunto donde ubicar el nodo. */
	int conj_elegido = rand() % cant_elegir;
	partes[get<0>(pesos[conj_elegido])].elementos.push_back(u);
	partes[get<0>(pesos[conj_elegido])].peso += get<1>(pesos[conj_elegido]);
	vistos[u] = get<0>(pesos[conj_elegido]);
}


vector<particion> golosa_aleatorizada(vector<vector<int> >& mz_ady, vector<particion>& partes, list<int>& candidatos, int k, vector<int>& vistos, int cant_elegir){
	/* Inicializo la semilla pues es utilizada en ubicar_menor. */			
	srand(time(NULL));

	while(!candidatos.empty()){    																						//O(M) *
		int elegido = candidatos.front();
		candidatos.pop_front();
		ubicar_en_menor(elegido, partes, k, mz_ady, vistos, cant_elegir);						//O(K*K + K*N)
	}
	return partes;
}


void  grasp(vector<vector<int> >& mz_ady, vector<particion>& partes, list<int>& candidatos, int k, vector<int>& vistos, int iteraciones, int cant_elegir, int n){
	
	vector<particion> res = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir);
	int c = costoTotal(res,k);
	busquedaLocal(res, k, mz_ady, n, c, false);
	iteraciones--;
	
	while(iteraciones != 0){
		vector<particion> res_2 = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir);
		busquedaLocal(res_2, k, mz_ady, n, c, false);
	
		if(suma_total(res_2) < suma_total(res)) res = res_2;
		iteraciones--;	
	}
}

/* Inicializa las estructuras necesarias para grasp y llama a la funcion que hace el trabajo*/
vector<int> iniciar_grasp(list<arista>& aristas, int n, int k, int  iteraciones, int cant_elegir){

	vector<int> vistos(n);
	vector<particion> partes(k);
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;

	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	grasp(mz_ady, partes, candidatos, k, vistos, iteraciones, cant_elegir, n);
	
	return vistos;
}


int main(int argc, char** argv){
	
	if(argc < 2) return 0;
				
	int n,m,k,u,v,w,iteraciones,cant_elegir;
	cin >> n;
	cin >> m;
	cin >> k;
	list<arista> aristas;
	iteraciones = atoi(argv[0]);
	cant_elegir = atoi(argv[1]);


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
	vector<int> vistos = iniciar_grasp(aristas, n, k, iteraciones, cant_elegir);

	/* Imprimo por salida esandar el resulado. */
	for(int i = 0; i < n ; i++){
		cout << vistos[i] << " "; 
	}

	return 0;
}
