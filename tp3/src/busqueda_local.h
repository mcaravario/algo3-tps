#include <vector>
#include <list>
#include <iostream>
#include <tuple>
#include "generacion_resultados.h"



/*Busca la particion mas costosa no vista. Si todas las particiones 
fueron vistas entonces devuelve un -1*/
int partCostosa(vector<particion>& res, int k){
	int i = 0;
	int j = 0;
	int pos = 0;
	while(i < k){
		if(j < res[i].peso){
			j = res[i].peso;
			pos = i;
		}
		i++;
	}
	return pos;
}


/*Calcula el costo nuevo de la particion con el nuevo nodo agregado*/
int costoNuevoCon(vector<particion>& res, int pos, int nodo, vector<vector<int> >& mz_ady){
	int i = res[pos].peso;
	for(auto it = res[pos].elementos.begin() ; it != res[pos].elementos.end(); it++ ){
		if(mz_ady[nodo][*it] >= 0) i += mz_ady[nodo][*it];
	}
	return i;
}

/*Calcula el costo de la particion que se le saco el nodo*/
int costoNuevoSin(vector<particion>& res, int pos, int nodo,vector<vector<int> >& mz_ady){
	int i = res[pos].peso;
	for(auto it = res[pos].elementos.begin() ; it != res[pos].elementos.end(); it++ ){
		if(mz_ady[nodo][*it] >= 0) i -= mz_ady[nodo][*it];
	}
	return i;
}

/*Calcula el costo de la solucion entera*/
int costoNuevo(vector<particion>&res,int k, int pos, int i, int nodo, vector<vector<int> >& mz_ady){
	int conteo = 0;
	int j= 0;
	while(j < k){
		if(j == pos){
			conteo += costoNuevoSin(res,pos,nodo,mz_ady);
		}else if(j == i){
			conteo += costoNuevoCon(res,i,nodo,mz_ady);
		}else{
			 conteo += res[j].peso;
		}
		j++;
	}
	return conteo;
}

void nuevoPeso(particion& p, vector<vector<int> >& mz_ady){
	p.peso = 0;
	auto tope = p.elementos.end();
	tope--;
	for(auto it1 = p.elementos.begin() ; it1 != tope; it1++){
		auto it2 = it1;
		it2++;
		while(it2 != p.elementos.end()){
			if(mz_ady[*it1][*it2] != -1) p.peso += mz_ady[*it1][*it2];
			it2++;
		}
	}
}

vector<particion> modificarRes(vector<particion>& res, int pos, int i, int nodo, vector<vector<int> >& mz_ady){
	vector<particion> result = res;
	result[i].elementos.push_back(nodo);
	nuevoPeso(result[i], mz_ady);
	result[pos].elementos.remove(nodo);
	nuevoPeso(result[pos], mz_ady);
	return result;
}



void busquedaLocal(vector<particion>& res, int k, vector<vector<int> >& mz_ady, int n, int costoSol, bool encontrado){
	if(!encontrado){
		vector<particion> res_vecino = res;
		int i = 0;
		int costoParcial = costoSol;
		int tope = n*n*k/1.5;
		bool hayMejor = false;
		while(i < k){
			if(res[i].peso > 0){
				list<int>::iterator itNodo = res[i].elementos.begin();
				while(itNodo != res[i].elementos.end()){
					int m = 0;
					int vecinos_vistos = 0;
					while(m < k && vecinos_vistos < tope ){
						if(m!=i){
							if(costoParcial > costoNuevo(res, k, i,m,*itNodo, mz_ady )){
								res_vecino = modificarRes(res, i,m,*itNodo, mz_ady);
								hayMejor = true;
								costoParcial = costoTotal(res_vecino,k);
							}
						}
						m++;
						vecinos_vistos++;
					}
					itNodo++;
				}
			}
			i++;
		}
		if(!hayMejor) encontrado = true;
		res= res_vecino;
		busquedaLocal(res,k,mz_ady,n,costoTotal(res,k),encontrado);
	}
}
