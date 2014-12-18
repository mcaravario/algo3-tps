struct {
	
	bool operator() (tuple<int,int> a, tuple<int,int> b) {
			return get<1>(a) < get<1>(b);
	}

} claseComp;

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

void ubicar_en_menor(int u, vector<conjunto>& partes, int k, vector<vector<int> >& mz_ady, vector<int>& vistos){
	
	int n_part;
	int min = MAX_INT;
	
	for (int i = 0; i<k; i++){																		
		int peso_nuevo = peso_asociado(partes[i],  mz_ady, u);
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

/** 
 * Este algoritmo elige donde ubicar al nodo u de forma golosa y aleatoria,
 * es decir, entre las mejores cant_elegir opciones (conjuntos) elige una
 * al azar y luego ubica al nodo allí.
 **/
void ubicar_en_menor_rand(int u, vector<conjunto>& partes, int k, vector<vector<int> >& mz_ady, vector<int>& vistos, int cant_elegir){
	
	vector<tuple<int,int> > pesos(k);
	
	/* Creo un arreglo que contegna a una bolsa y el peso de agregar a u a dicha bolsa. */
	for (int i = 0; i<k; i++){																			
		get<0>(pesos[i]) = i;
		get<1>(pesos[i]) = peso_asociado(partes[i], mz_ady, u);
	}
	
	/* Ordeno el arreglo para luego quedarme con los mejores.  */
	sort(pesos.begin(), pesos.end(), claseComp);
	
	/* Eligo de forma aleatoria el conjunto donde ubicar el nodo. */
	int conj_elegido = rand() % cant_elegir;
	partes[get<0>(pesos[conj_elegido])].elementos.push_back(u);
	partes[get<0>(pesos[conj_elegido])].peso += get<1>(pesos[conj_elegido]);
	vistos[u] = get<0>(pesos[conj_elegido]);
}

/* Devuelve el nodo ganador y lo elimina de la lista. */
int nodo_ganador(list<int>& l, int nro){
	if ((unsigned int)nro >= l.size()){
		nro = nro % l.size();
	}
	auto it = l.begin();
	while (nro > 0){
		it++;
		nro--;
	}
	int res = *it;
	l.erase(it);
	return res;
}

vector<conjunto> golosa_aleatorizada(vector<vector<int> >& mz_ady, list<int> candidatos, int k, vector<int>& vistos, int cant_elegir, int semilla, int modo_uso_goloso){
	/* Inicializo la semilla pues es utilizada en ubicar_menor. */			
	srand(semilla);

	/* Creo la partición vacía. */
	vector<conjunto> partes(k);

	/* Ordeno los nodos por peso. */
	ordenar_nodos(candidatos, mz_ady);
		
	if (modo_uso_goloso){
		while (!candidatos.empty()) {
			if ((unsigned int) cant_elegir > candidatos.size()) cant_elegir = candidatos.size();
			int ganador = rand() % cant_elegir;
			int nodo = nodo_ganador(candidatos, ganador);
			ubicar_en_menor(nodo, partes, k, mz_ady, vistos);	
		}
	} else {
		while(!candidatos.empty()){    																			
			int elegido = candidatos.front();
			candidatos.pop_front();
			ubicar_en_menor_rand(elegido, partes, k, mz_ady, vistos, cant_elegir);
		}
	}

	return partes;
}
