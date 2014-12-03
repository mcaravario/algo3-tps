#include <vector>
#include <list>
#include <iostream>
#include <tuple>

typedef int nodo;
using namespace std;


struct particion{
	list<nodo> elementos;
	int peso;
	particion():elementos(), peso(0) {}
};


/* Devuelve la suma total de pesos */
int suma_total(vector<particion>& partes) {
	int res = 0;
	for (unsigned int i = 0; i < partes.size(); i++){
		res += partes[i].peso;
	}
	return res;	
}

/* Devuelve el peso asociado del nodo v, al conjunto i */
int peso_asociado(nodo v, particion& parte, vector<vector<int> >& mz_ady){
	int res = 0;
	for (auto it = parte.elementos.begin(); it != parte.elementos.end(); it++){
		if(mz_ady[v][*it]){
			res += mz_ady[v][*it];
		}
	}
	return res;
}


