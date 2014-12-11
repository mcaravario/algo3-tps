#include <vector>
#include <list>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

#define MAX_INT 2147483647                                                                 
typedef int nodo;
 
struct conjunto{                                                   
	list<int> elementos;                                              
	int peso;                                                         
	conjunto(): elementos(), peso(0) {}                              
};

struct arista{
	int u;
	int v;
	int peso;
	arista(int a, int b, int c): u(a), v(b), peso(c) {}
};

vector<vector<int> > crear_adyacencias(list<arista>& aristas, int n){
	vector<vector<int> > res(n, vector<int>(n));

	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			res[i][j] = -1;
		}
	}

	for (auto it = aristas.begin(); it != aristas.end(); it++){
		res[it->u][it->v] = it->peso; 
		res[it->v][it->u] = it->peso; 
	}

	return res;
}

/* Devuelve el peso asociado del nodo v, al conjunto c. */
int peso_asociado(conjunto& c, vector<vector<int> >& mz_ady, int v){
	int res = 0;
	for (auto it = c.elementos.begin(); it != c.elementos.end(); it++){				//O(N)
		if(mz_ady[v][*it] != -1){
			res += mz_ady[v][*it];
		}
	}
	return res;
}


/* Devuelve la suma total de pesos */
int suma_total(vector<conjunto>& partes) {
	int res = 0;
	for (unsigned int i = 0; i < partes.size(); i++){
		res += partes[i].peso;
	}
	return res;	
}


void pesoParticion(conjunto& p, vector<vector<int> >& mz_ady){
	p.peso = 0;
	auto tope = p.elementos.end();
	tope--;
	for(auto it1 = p.elementos.begin(); it1 != tope; it1++){
		auto it2 = it1;
		it2++;
		while(it2 != p.elementos.end()){
			if(mz_ady[*it1][*it2] != -1) p.peso += mz_ady[*it1][*it2];
			it2++;
		}
	}
}

	
vector<conjunto> crearResultado(vector<vector<int> >& mz_ady, int n, int k) {
	vector<conjunto> res (k, conjunto());
	int j = 0;
	for(int i = 0; i<n; i++){
		res[j].elementos.push_back(i);
		if (j == (k-1)) j = 0;
		j++;
	}
	
	for(int i = 0; i<k; i++){
		pesoParticion(res[i], mz_ady);
	}

	return res;
} 


void establecer_posiciones(vector<conjunto>& particion, vector<int>& posiciones){
	int n_part = 0;
	for (auto it = particion.begin(); it != particion.end(); it++){
		for (auto nd = it->elementos.begin(); nd != it->elementos.end(); nd++){
			posiciones[*nd] = n_part;
		}
		n_part++;
	}
}


/* Muestra el resultado por la salida estandar. */
void mostrar_res(vector<int> res){
	for (auto it = res.begin(); it != res.end(); it++) cout << *it << " ";
	cout << endl;
}
