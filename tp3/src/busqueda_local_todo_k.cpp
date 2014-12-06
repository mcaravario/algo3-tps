#include <vector>
#include <list>
#include <iostream>
#include "goloso.h"
using namespace std;

#define CANT_BOLSAS 3

/*Busca la particion mas costosa no vista. Si todas las particiones 
fueron vistas entonces devuelve un -1*/
int partCostosa(/*vector<bool>& p_vistas, */  vector<particion>& res, int k){
	int i = 0;
	int j = 0;
	int pos = 0;
	while(i < k){
	//	if(!p_vistas[i]){
			if(j < res[i].peso){
				j = res[i].peso;
				pos = i;
			}
//		}
		i++;
	}
	return pos;
}


/*Busca la arista mas costosa de la particion y devuelve un iterador al nodo que se encuentra primero en la
lista de elementos*/
list<int>::iterator nodoDeAristaCostosa(particion& part, vector<vector<int> >& mz_ady, vector<bool>& n_vistos){
	list<int>::iterator it1 = part.elementos.begin();
	list<int>::iterator it3 = part.elementos.begin();
	int peso_mayor = -1;
	while(it1 != part.elementos.end()){
		list<int>::iterator it2 = it1;
		it2++;
		while(it2 != part.elementos.end()){
			if(peso_mayor < mz_ady[*it1][*it2] && !(n_vistos[*it1] && n_vistos[*it2])){
				if(n_vistos[*it1]){
					it3 = it2;
				}else{
					it3 = it1;
				}
				peso_mayor = mz_ady[*it1][*it2];
			}
			it2++;
		}
		it1++;
	}
	return it3;
}

/*Calcula el costo nuevo de la particion con el nuevo nodo agregado*/
int costoNuevoCon(vector<particion>& res, int pos, int nodo,vector<vector<int> >& mz_ady){
	list<int>::iterator it = res[pos].elementos.begin();
	int i = res[pos].peso;
	for(it; it != res[pos].elementos.end(); it++ ){
		if(mz_ady[nodo][*it] >= 0) i += mz_ady[nodo][*it];
	}
	return i;
}

/*Calcula el costo de la particion que se le saco el nodo*/
int costoNuevoSin(vector<particion>& res, int pos, int nodo,vector<vector<int> >& mz_ady){
	list<int>::iterator it = res[pos].elementos.begin();
	int i = res[pos].peso;
	for(it; it != res[pos].elementos.end(); it++ ){
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

void nuevoPeso(particion& p, vector<vector<int> > mz_ady){
	p.peso = 0;
	list<int>::iterator it1 = p.elementos.begin();
	list<int>::iterator tope = p.elementos.end();
	tope--;
	for(it1; it1 != tope; it1++){
		list<int>::iterator it2 = it1;
		it2++;
		while(it2 != p.elementos.end()){
			if(mz_ady[*it1][*it2] != -1) p.peso += mz_ady[*it1][*it2];
			it2++;
		}
	}
}

vector<particion> modificarRes(vector<particion>& res,int k, int pos, int i, int nodo, vector<vector<int> > mz_ady){
vector<particion> result = res;
	result[i].elementos.push_back(nodo);
	nuevoPeso(result[i], mz_ady);
	result[pos].elementos.remove(nodo);
	nuevoPeso(result[pos], mz_ady);
return result;
}

int costoTotal(vector<particion> p, int k){
int res = 0;
	for(int i = 0; i<k; i++){
			res = res + p[i].peso;
	}
return res;
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
								res_vecino = modificarRes(res, k,i,m,*itNodo, mz_ady);
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

int main() {
	
	int n,m,k,u,v,w;
  cin >> n;
  cin >> m;
  cin >> k;
  vector<vector<int> > mz_ady(n, vector<int>(n));
  list<tuple<int,int,int> > aristas;
  vector<int> vistos(n);
	vector<bool> p_vistas(n,false);

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

    if(mz_ady[u][v] == -1 || mz_ady[v][u] == -1){
      mz_ady[u][v] = w;
      mz_ady[v][u] = w;
      aristas.push_back(make_tuple(u,v,w));
    }
  }
  
/* Inicializo los no vistos nunca en -2 */
  for(int i = 0; i<n ; i++){
    vistos[i] = -1;
  }

	/*Como Goloso modifica la matriz de adyacencia creamos 
		una copia*/
	vector<vector<int> > mz_ady2 = mz_ady;
	
	/* Funcion que resuelve el ejercicio */
	vector<particion> res(k,particion());
	for (int i=0; i<5; i++) res[0].elementos.push_back(i);
//	for (int i=5; i<7; i++) res[1].elementos.push_back(i);
//	for (int i=7; i<11; i++) res[2].elementos.push_back(i);
	nuevoPeso(res[0],mz_ady);
//	nuevoPeso(res[1],mz_ady);
//	nuevoPeso(res[2],mz_ady);
	int c = costoTotal(res, k);
	busquedaLocal(res,k,mz_ady,n,c,false);
	if( costoTotal(res, k) <= c) cout<< "Merry Christmas"<< endl << "costo encontrado " << costoTotal(res,k) << endl << "costo viejo " << c << endl;
	return 0;
}
