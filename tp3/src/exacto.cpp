#include "grafo.h"


/**
* Este contador refleja la cantidad de elementos ubicados,
*	sirve para saber cuando la solución está vacía.
**/
int cant_elementos = 0;

/* Inicializado en el main*/
vector<vector<int> > *mz_ady_ptr;

/* Foward Declaration. */
bool es_solucion(vector<particion>& res, vector<particion>& ss, particion& p, nodo n);

// BORRAR
void mostrar_particion(vector<particion>&);

/**
* Calcula la partición (de tamaño maximo bolsas.size) que optimiza
*	(minimiza) la suma de pesos totales.
**/
void mejor_particion(vector<particion>& res, vector<particion>& bolsas, list<nodo>& candidatos) {
	if (candidatos.size() == 0) {
		cout << "         ANTES" << endl;
		mostrar_particion(res);
		res = bolsas;
		cout << "         DESPUES" << endl;
		mostrar_particion(res);
	}else {
		nodo elegido = *candidatos.begin();
		cout << "ARMANDO SOL" << endl;
		mostrar_particion(bolsas);
		candidatos.pop_front();
		for (unsigned int i = 0; i < bolsas.size(); i++){
			bolsas[i].elementos.push_back(elegido);
			cant_elementos++;
			int tam = bolsas[i].elementos.size();
			/* Si sigue siendo una solución, exploro la rama.*/
			if (es_solucion(res, bolsas, bolsas[i], elegido)){
				bolsas[i].peso += peso_asociado(elegido, bolsas[i], *mz_ady_ptr);
				mejor_particion(res, bolsas, candidatos);
				bolsas[i].peso -= peso_asociado(elegido, bolsas[i], *mz_ady_ptr);
			}
			bolsas[i].elementos.pop_back();
			cant_elementos--;
			/* Poda para no repetir soluciones. */
			if (tam == 1) i = bolsas.size();
		}
	}
}


/**
* Indica si la sub-solución (al agregarle un elemento) sigue 
*	siendo solución. Es decir, si el peso total resultante de
*	agregar al nuevo elemento supera el de la solución obtenida
*	anteriormente.
**/
bool es_solucion(vector<particion>& res, vector<particion>& ss, particion& p, nodo n){
	if (cant_elementos == 0) return true;
	int cota_max = suma_total(res);
	int acumulado = suma_total(ss);
	int peso_agregado = peso_asociado(n, p, *mz_ady_ptr);
	return cota_max > acumulado + peso_agregado;
}

/**
*  Recorre linealmente la partición pasada como parámetro,
*	y para cada elemento i de la partición, asigna en 
* posiciones[i] el número del conjunto de la partición
*	en donde está i.
**/
void establecer_posiciones(vector<particion>& bolsas, vector<int>& posiciones){
	cout << "Número de conjuntos en la parcición: " << bolsas.size() << endl;
	int n_part = 0;
	for (auto it = bolsas.begin(); it != bolsas.end(); it++){
		cout << "Cantidad de elementos: " << it->elementos.size() << endl;
		for (auto nd = it->elementos.begin(); nd != it->elementos.end(); nd++){
			posiciones[*nd] = n_part;
			cout << "Partición:" << n_part << endl;
		}
		n_part++;
	}
}


/* Muestra el resultado por la salida estandar. */
void mostrar_res(vector<int> res){
	for (auto it = res.begin(); it != res.end(); it++) cout << *it << " ";
	cout << endl;
}

int main(){
	int n,m,k,u,v,w;
	cin >> n;
	cin >> m;
	cin >> k;
	vector<vector<int> > mz_ady(n, vector<int>(n));
	vector<nodo> posiciones(n);
	

	/* Inicializo matriz de adyacencias */
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			mz_ady[i][j] = -1;
		}
	}

	/* Inicializo el puntero global a la matriz */
	mz_ady_ptr = &mz_ady;

	/* Completado de matriz de adyacencias */
	for (int i = 0; i < m; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		u--;
		v--;

		if(mz_ady[u][v] == -1 || mz_ady[v][u] == -1){
			mz_ady[u][v] = w; 
			mz_ady[v][u] = w; 
		} 	
	}

	/* Creo la partición resultado, y la particion parcial. */
	vector<particion> res(k);
	vector<particion> bolsas(k);

	/* Creacion de la lista de nodos. */
	list<nodo> ns {};
	for (int i = 0; i < n; i++) ns.push_back(i);

	/* Funcion que resuelve el ejercicio. */
	mejor_particion(res, bolsas, ns);
	
	/* Preparacion del resultado. */
	establecer_posiciones(res, posiciones);
	
	/* Muestra por salida estandar el resultado. */
	mostrar_res(posiciones);

	return 0;
}

// Borrar antes de entregar

void mostrar_particion(vector<particion>& p){
	cout << ">>> Partición: " << endl;
	for (int i = 0; i < p.size(); i++){
		cout << "   >> Bolsa " << i << ": ";
		for (auto it = p[i].elementos.begin(); it != p[i].elementos.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}

}
