#include "kpmp.h"

struct nodo_p{
	int nro;
	int peso;
	nodo_p(): nro(-1), peso(0) {}
	nodo_p(int n, int p): nro(n), peso(p) {}
	bool operator<(const nodo_p& a) const{
		return this->peso >= a.peso || (this->peso == a.peso && this->nro >= a.nro);
	}
};

int peso_nodo(int nodo, vector<vector<int> >& mz_ady, int n){
	int res = 0;
	for(int i = 0; i < n; i++){
		if(mz_ady[nodo][i] != -1){
			res += mz_ady[nodo][i]; 
		}
	}
	return res;
}


list<int> ordenar_nodos(list<int>& nodos, vector<vector<int> >& mz_ady){
	int n = nodos.size();
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




/* Ubica el vertice u en el conjunto que menos peso sume al agregarlo */
void ubicar_en_menor(int u, vector<conjunto>& partes, int k, vector<vector<int> >& mz_ady, vector<int>& vistos){
	
	int n_part;
	int min = MAX_INT;
	
	/* Trato de ubicar el vertice u, si es que no lo ubique previamente */
	for (int i = 0; i<k; i++){																						//O(K)*
		int peso_nuevo = peso_asociado(partes[i],  mz_ady, u);							//O(N)
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


vector<conjunto> heuristica_golosa(vector<vector<int> >& mz_ady, vector<conjunto>& partes, list<int>& candidatos, int k, vector<int>& vistos){
				
	while(!candidatos.empty()){    																						//O(N) *
		int elegido = candidatos.front();
		candidatos.pop_front();
		ubicar_en_menor(elegido, partes, k, mz_ady, vistos);						//O(K*N)
	}
	return partes;
}


vector<int> iniciar_golosa(list<arista>& aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;
	vector<int> vistos(n);
	vector<conjunto> partes(k);
	
	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	/* Llamo a la herística propiamente dicha. */
	vector<conjunto> res = heuristica_golosa(mz_ady, partes, candidatos, k, vistos);	
	
	return vistos;
}

vector<int> iniciar_golosa_ordenada(list<arista>& aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;
	vector<int> vistos(n);
	vector<conjunto> partes(k);
	
	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	/* Llamo a la herística propiamente dicha. */
	list<int> candidatos_ordenados = ordenar_nodos(candidatos, mz_ady);
	vector<conjunto> res = heuristica_golosa(mz_ady, partes, candidatos_ordenados, k, vistos);	
	
	return vistos;
}

int peso_de_golosa_ordenada(list<arista>& aristas, int n, int k){

	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	list<int> candidatos;
	vector<int> vistos(n);
	vector<conjunto> partes(k);
	
	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	/* Llamo a la herística propiamente dicha. */
	list<int> candidatos_ordenados = ordenar_nodos(candidatos, mz_ady);
	vector<conjunto> res = heuristica_golosa(mz_ady, partes, candidatos_ordenados, k, vistos);	
	
	return suma_total(res);
}

vector<conjunto> golosa_para_local(vector<vector<int> > mz_ady, int n, int k){
	list<int> candidatos;
	vector<int> vistos(n);
	vector<conjunto> partes(k);
	
	for(int i = 0; i < n; i++){
		candidatos.push_back(i);
	}

	/* Llamo a la herística propiamente dicha. */
	list<int> candidatos_ordenados = ordenar_nodos(candidatos, mz_ady);
	vector<conjunto> res = heuristica_golosa(mz_ady, partes, candidatos_ordenados, k, vistos);	
	return res;
}
