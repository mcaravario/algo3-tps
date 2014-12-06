#include <vector>
#include <list>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

#define MAX_INT 2147483647

struct nodo_p{
	int nro;
	int peso;
	nodo_p(): nro(-1), peso(0) {}
	nodo_p(int n, int p): nro(n), peso(p) {}
	bool operator<(const nodo_p& a) const{
		return this->peso < a.peso || (this->peso == a.peso && this->nro < a.nro);
	}
};

struct particion{
	list<int> elementos;
	int peso;
	particion(): elementos(), peso(0) {}
};

int peso_nodo(int nodo, vector<vector<int> > mz_ady, int n){
	int res = 0;
	for(int i = 0; i < n; i++){
		if(mz_ady[nodo][i] != -1){
			res += mz_ady[nodo][i]; 
		}
	}
	return res;
}



list<int> ordenar_nodos(list<int> nodos, vector<vector<int> > mz_ady, int n){
	auto it = nodos.begin();
	list<int> res;
	vector<nodo_p> res_parcial(n);
	for(int i = 0; i < n; i++){
		int peso = peso_nodo(*it, mz_ady, n);
		res_parcial[i] = nodo_p(*it, peso);
		it++;
	}
	
	sort(res_parcial.begin(), res_parcial.end());
	for(auto it = res_parcial.begin(); it != res_parcial.end(); it++){
		res.push_back(it->nro);
	}

	return res;
}

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

/* Devuelve el peso asociado del nodo v, al conjunto i */
int peso_asociado(int v, vector<particion>& partes, int i,  vector<vector<int> >& mz_ady){
	int res = 0;
	for (auto it = partes[i].elementos.begin(); it != partes[i].elementos.end(); it++){				//O(N)
		if(mz_ady[v][*it] != -1){
			res += mz_ady[v][*it];
		}
	}
	return res;
}

/* Ubica el vertice u en el conjunto que menos peso sume al agregarlo */
void ubicar_en_menor(int u, vector<particion>& partes, int k, vector<vector<int> >& mz_ady, vector<int>& vistos){
	
	int n_part;
	int min = MAX_INT;
	
	/* Trato de ubicar el vertice u, si es que no lo ubique previamente */
	if(vistos[u] == -1){
		for (int i = 0; i<k; i++){																						//O(K)*
			int peso_nuevo = peso_asociado(u, partes, i, mz_ady);							//O(N)
			if (peso_nuevo < min) {
				min = peso_nuevo;
				n_part = i;
			}
		}
		/**
		 * En n_part tengo el conjunto donde va u.
		 **/
		partes[n_part].elementos.push_front(u);
		partes[n_part].peso += min;
		/* Actualizo el arreglo donde tengo los vertices que ya ubique */
		vistos[u] = n_part;
	}
}


/*
 * Las estructuras que se utilizaran en el algoritmo principal y sus funciones seran:
 * matriz de adyacencias : si hay arista entre u y v se guarda el peso de la arista, sino -1 
 * vector(particion) partes : vector donde se almacenara la respuesta, en cada particion se guardan los elementos y el peso respectivo de la particion.
 * lista(tupla(int.int.int)) aristas : representa todas las aristas del grafo, los primeros dos ints indican los nodos sobre los que incide y el tercer int, es el peso.
 * vector(int) vistos: la posicion i indica en que particion se encuentra el nodo i. si no fue ubicado en ninguna particion tiene el valor -2
*/

vector<particion> heuristica_golosa(vector<vector<int> >& mz_ady, vector<particion>& partes, list<int>& candidatos, int k, vector<int>& vistos){
				
	while(!candidatos.empty()){    																						//O(N) *
		int elegido = candidatos.front();
		candidatos.pop_front();
		ubicar_en_menor(elegido, partes, k, mz_ady, vistos);						//O(K*N)
	}
	return partes;
}


int main(){
	int n,m,k,u,v,w;
	cin >> n;
	cin >> m;
	cin >> k;
	vector<vector<int> > mz_ady(n, vector<int>(n));
	list<int> candidatos;
	vector<int> vistos(n);
	
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
	vector<particion> res = heuristica_golosa(mz_ady, partes, candidatos, k, vistos);
	
	/* Preparacion del resultado */

	for(int i = 0; i < n ; i++){
		cout << vistos[i] << " "; 
	}

	return 0;
}
