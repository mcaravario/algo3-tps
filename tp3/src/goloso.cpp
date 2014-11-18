#include <vector>
#include <list>
#include <iostream>
#include <tuple>

using namespace std;

struct particion{
	list<int> elementos;
	int peso;
};

list<tuple<int,int,int> >::iterator elegir_mayor(list<tuple<int,int,int> > aristas){
	list<tuple<int,int,int> >::iterator res;
	int max = 0;
	for(auto it = aristas.begin(); it != aristas.end(); it++){
		if(get<2>(*it) >= max){
			max = get<2>(*it);
			res = it;
		}		
	}
	
	/*
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(get<0>(mz_ady[i][j]) && get<1>(mz_ady[i][j]) > max){
				max = get<1>(mz_ady[i][j]);
				get<0>(res) = i;
				get<1>(res) = j;
			}
		}
	}
	*/



	return res;

}
/* Devuelve la suma total de pesos */
int suma_total(vector<particion>& partes, int k){
	int res = 0;
	for (int i = 0; i<k ; i++){
		res += partes[i].peso;
	}
	return res;	
}

/* Devuelve el peso asociado del nodo v, al conjunto i */
int peso_asociado(int v, vector<particion>& partes, int i,  vector<vector<tuple<bool,int> > > mz_ady){
	int res = 0;
	for (auto it = partes[i].elementos.begin(); it != partes[i].elementos.end(); it++){
		if(get<0>(mz_ady[v][*it])){
			res += get<1>(mz_ady[v][*it]);
		}
	}
	return res;
}

/* Ubica los vertices u y v en el conjunto que menos peso sume al agregarlos */
void ubicar_en_menor(int u, int v, vector<particion>& partes, int k, int pesomax, vector<vector<tuple<bool,int> > > mz_ady){
	int max = pesomax;
	/*aca guardo el numero de particion */
	int res;
	/*Ciclo para ubicar el primer vertice (u)*/
	for (int i = 0; i<k; i++){
		partes[i].elementos.push_front(u);
		partes[i].peso += peso_asociado(u, partes, i, mz_ady);
		if(suma_total(partes,k) < max){
			res = i;
			max = suma_total(partes,k);
		}
		partes[i].elementos.pop_front();
		partes[i].peso -= peso_asociado(u, partes, i, mz_ady);
	}
	
	/* En res tengo el numero de particion donde menos peso suma */
	partes[res].elementos.push_front(u);
	partes[res].peso += peso_asociado(u, partes, res, mz_ady);
	
	int res_v;
	
	/* Ciclo para ubicar el segundo vertice (v) */
	for (int j = 0; j < k; j++){	
		partes[j].elementos.push_front(v);
		partes[j].peso += peso_asociado(v, partes, j, mz_ady);
		if(suma_total(partes,k) < max && j != res){
			res_v = j;
			max = suma_total(partes,k);
		}
		partes[j].elementos.pop_front();
		partes[j].peso -= peso_asociado(v, partes, j, mz_ady);
	}
	partes[res_v].elementos.push_front(v);
	partes[res_v].peso += peso_asociado(v, partes, res_v, mz_ady);

}
/* Calcula el peso maximo que puede tener una particion, tener en cuenta que en la lista de aristas
 * no debe haber aristas repetidas */
int calcular_peso_max(list<tuple<int,int,int> >& aristas){
	int res = 0;
	for (auto it = aristas.begin(); it != aristas.end(); it++){
		res += get<2>(*it);
	}
	return res;
}

vector<particion> heuristica_golosa(vector<vector<tuple<bool,int> > > mz_ady, vector<particion>& partes, list<tuple<int,int,int> >& aristas, int k){
	int pesomax = calcular_peso_max(aristas);
				
	while(!aristas.empty()){
		/* Elijo arista de mayor peso */
		auto arista = elegir_mayor(aristas);
		int u = get<0>(*arista);
		int v = get<1>(*arista);
		ubicar_en_menor(u, v, partes, k, pesomax, mz_ady);
		/* Una vez analizada la arista la saco de la matriz de adyacencia y de
		 * mi lista de aristas restantes */
		get<0>(mz_ady[u][v]) = false;	
		aristas.erase(arista);				
	}
	return partes;
}


int main(){

return 0;
}
