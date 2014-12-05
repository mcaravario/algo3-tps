#include <vector>
#include <list>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <time.h>

using namespace std;

struct particion{
	list<int> elementos;
	int peso;
	particion():elementos(), peso(0){}
};

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

/*TODO*/
/*BORRAR*/
void busqueda_local(vector<particion>) {

}

void  grasp(vector<vector<int> >& mz_ady, vector<particion>& partes, list<int>& candidatos, int k, vector<int>& vistos, int iteraciones, int cant_elegir){
	
	vector<particion> res = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir);
	busqueda_local(res);
	iteraciones--;
	
	while(iteraciones != 0){
		vector<particion> res_2 = golosa_aleatorizada(mz_ady, partes, candidatos, k, vistos, cant_elegir);
		busqueda_local(res);
	
		if(suma_total(res_2) < suma_total(res)) res = res_2;
		iteraciones--;	
	}
}

int main(int argc, char** argv){
	
	if(argc < 2) return 0;
				
	int n,m,k,u,v,w,iteraciones,cant_elegir;
	cin >> n;
	cin >> m;
	cin >> k;
	vector<vector<int> > mz_ady(n, vector<int>(n));
	list<int> candidatos;
	vector<int> vistos(n);
	
	iteraciones = atoi(argv[0]);
	cant_elegir = atoi(argv[1]);

	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	/* Inicializo matriz de adyacencias */
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mz_ady[i][j] = -1;
		}
	}

	/* Inicializacion de estructuras */
	for (int i = 0; i < m; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		/* Resto uno para que no haya problemas con los bordes. Los nodos estan numerados de 0 a n-1*/
		u--;
		v--;

		mz_ady[u][v] = w; 
		mz_ady[v][u] = w; 
	}
	/* Inicializo los no vistos nunca en -2 */
	for(int i = 0; i<n ; i++){
		vistos[i] = -1;
	}

	/* Funcion que resuelve el ejercicio */
	vector<particion> partes(k);
	grasp(mz_ady, partes, candidatos, k, vistos, iteraciones, cant_elegir);

	for(int i = 0; i < n ; i++){
		cout << vistos[i] << " "; 
	}

	return 0;
}
