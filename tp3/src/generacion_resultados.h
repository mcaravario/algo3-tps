#include <vector>
#include <list>
#include <iostream>
#include <tuple>

using namespace std;

#define MAX_INT 2147483647                                                                 
 
struct particion{                                                   
	list<int> elementos;                                              
	int peso;                                                         
	particion(): elementos(), peso(0) {}                              
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



void pesoParticion(particion& p, vector<vector<int> >& mz_ady){
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

int costoTotal(vector<particion>& p, int k){
	int res = 0;
	for(int i = 0; i<k; i++){
			res = res + p[i].peso;
	}
	return res;
}

	
vector<particion> crearResultado(int n, int k, vector<vector<int> >& mz_ady){
	vector<particion> res (k, particion());
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
