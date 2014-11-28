#include <vector>
#include <list>
#include <iostream>
#include <tuple>

using namespace std;

#define MAX_INT 2147483647

struct particion{
	list<int> elementos;
	int peso;
	particion():peso(0), elementos() {}
};

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
	for (auto it = partes[i].elementos.begin(); it != partes[i].elementos.end(); it++){
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
		cout << "ubique el nodo " << u << "en la particion " << n_part << endl;
	}
}


/*
 * Las estructuras que se utilizaran en el algoritmo principal y sus funciones seran:
 * matriz de adyacencias : si hay arista entre u y v se guarda el peso de la arista, sino -1 
 * vector(particion) partes : vector donde se almacenara la respuesta, en cada particion se guardan los elementos y el peso respectivo de la particion.
 * lista(tupla(int.int.int)) aristas : representa todas las aristas del grafo, los primeros dos ints indican los nodos sobre los que incide y el tercer int, es el peso.
 * vector(int) vistos: la posicion i indica en que particion se encuentra el nodo i. si no fue ubicado en ninguna particion tiene el valor -2
*/

vector<particion> heuristica_golosa(vector<vector<int> >& mz_ady, vector<particion>& partes, list<tuple<int,int,int> >& aristas, int k, vector<int>& vistos){
				
	while(!aristas.empty()){    																						//O(M) *
		/* Elijo arista de mayor peso */
		auto arista = elegir_mayor(aristas);																	//O(M)
		int u = get<0>(*arista);
		int v = get<1>(*arista);
		ubicar_en_menor(u, partes, k, mz_ady, vistos);						//O(K*K + K*N)
		ubicar_en_menor(v, partes, k, mz_ady, vistos);						//O(K*K + K*N)
		/* Una vez analizada la arista la saco de la matriz de adyacencia y de
		 * mi lista de aristas restantes */
		mz_ady[u][v] = -1;	
		mz_ady[v][u] = -1;	
		aristas.erase(arista);				
	}
	return partes;
}


int main(){
	int n,m,k,u,v,w;
	cin >> n;
	cin >> m;
	cin >> k;
	vector<vector<int> > mz_ady(n, vector<int>(n));
	list<tuple<int,int,int> > aristas;
	vector<int> vistos(n);


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

	/* Funcion que resuelve el ejercicio */
	vector<particion> partes(k);
	vector<particion> res = heuristica_golosa(mz_ady, partes, aristas, k, vistos);
	
	/* Preparacion del resultado */

	for(int i = 0; i < n ; i++){
		cout << vistos[i] << " "; 
	}

	return 0;
}
