#include "ejercicio1.h"

using namespace std;


/*	Esta función agrega las ciudades a un Trie, donde cada palabra 
 *	 contiene un miembro ID.
 *	La idea es que cada ciudad tenga asociado un número entre 0 y la
 *	cantidad máxima de ciudades -1.
 *
 *	Si se agrega una ciudad dos veces, no se modifica el Trie la segunda vez.
 *	Origen está mapeado con 0.
 *	Destino está mapeado con n-1.
 **/

void mapear_ciudades(Trie* ciudades, list<vuelo>& vuelos, string origen, string destino){
	ciudades->addWord(origen);
	
	for(auto it = vuelos.begin(); it != vuelos.end(); it++){
		
		if(it->ori != destino)ciudades->addWord(it->ori);
		if(it->des != destino)ciudades->addWord(it->des);
	}
	ciudades->addWord(destino);
}


/**
 * Esta función modifica el horario de salida de todo vuelo
 * cuyo ciudad de salida sea origen, restándole 2.
 **/
void	reducir_hora_salida_origen(list<vuelo>& vuelos, Trie* ciudades){
	
	auto it = vuelos.begin();
	while (it != vuelos.end()){
		// Si es origen, le cambio la hora de salida.
		if (ciudades->get_id(it->ori) == 0) it->salida -= 2;
		it++;
	}
}

void inicializar_con_vuelos(vector<vuelo>& res, list<vuelo>& ls){
	
	auto it = ls.begin();		
	int tam = ls.size();	
	for (int i = 0; i < tam; i++){
		res[i] = *it;
		it++;
	}
}



/**
 * Agrega el id de cada vuelo al conjunto de vuelos que llegan a la ciudad que corresponde.
 **/
void inicializar_conjuntos(Trie *ciudades, vector<set<vuelo> >& vuelos_hasta, vector<vuelo>& vuelos){
	for(int id = 0; id < vuelos.size(); id++){
			vuelos_hasta[ciudades->get_id(vuelos[id].des)].insert(vuelos[id]);
	}

}


/**
 * 	Modifica la lista res, agregando los vuelos_id de los vuelos tomados.
 * 	El resultado se reconstruye (de atrás para adelante) de forma recursiva
 * a partir del parámetro "v" que es el vuelo que llega a destino.
 **/
void reconstruir_ruta(vector<vuelo_id>& ruta, list<vuelo_id>& res, vector<vuelo>& vuelos, Trie* ciudades){
	
	ciudad_id c_actual = ruta.size()-1;
	
	while(c_actual != 0){
		res.push_front(ruta[c_actual]);
		c_actual = ciudades->get_id(vuelos[ruta[c_actual]].ori);
	}
}


/**
*		Función recursiva que devuele VERDADERO si hay una ruta de vuelos que 
*	llegue a origen desde la ciudad "c" (parámetro), y FALSO en caso contrario.
*	Dada la ciudad "c", recorre la lista de los vuelos predecesores, es decir
*	los que llegan a "c" y no superen la hora h-2.
**/
bool buscar_ruta(ciudad_id c, hora h_max,  vector<vuelo_id>& ruta, vector<set<vuelo> >& vuelos_hasta, vector<vuelo>& vuelos_por_id, Trie* ciudades){
	
	// Caso Base, estoy en ORIGEN.
	if (c == 0){
		return true;
	} else {
		bool hay_sol = false;
		auto predecesor = vuelos_hasta[c].begin();
		ciudad_id proxima_ciudad;
		hora proximo_horario;

		while (!hay_sol && predecesor != vuelos_hasta[c].end() && predecesor->llegada <= h_max-2){
			
			// Escribo el tramo de la ruta
			ruta[c] = predecesor->id;

			// Parámetros que usare en la llamada recursiva
			proxima_ciudad = ciudades->get_id(predecesor->ori);
			proximo_horario = predecesor->salida;

			// Elimino del set al elemento ya elegido, para no revisarlo posteriormente.
			auto a_eliminar = predecesor;
			predecesor++;
		 	vuelos_hasta[c].erase(a_eliminar);

			// Llamo recursivamente sobre el elemento elegido.
			hay_sol = buscar_ruta(proxima_ciudad, proximo_horario, ruta, vuelos_hasta, vuelos_por_id, ciudades);
		}

		if (hay_sol) return true;

		return false;
	}
}

/*	Algoritmo que resuelve el problema. Solamente toma la lista de vuelos, y
 *	las ciudades de origen y destino, junto con una lista resultante que se 
 *	modifica una vez encontrada la solución óptima.
 **/
hora ruta_de_vuelo(list<vuelo_id>& res, list<vuelo>& vuelos, string origen, string destino){

	 /* Primero creo e inicializo todas las estructuras que necesito:
		* -Un trie para mapear ciudades con un ID entero de 0 a #ciudades-1
		* -Un arreglo de vuelos, donde la posición i corresponde al vuelo con id = i.
		* -Un arreglo que dada una ciudad me indica	qué vuelos llega ahí.
		* -Un arreglo de vuelos, que dado un vuelo_id me indica que vuelo fue tomado
		* antes de tomar ese (sirve para reconstruir el camino).
	 **/
	// Trie de ciudades
	Trie* ciudades = new Trie();
	mapear_ciudades(ciudades, vuelos, origen, destino);
	int cant_ciudades = ciudades->size();

	/**
	 *  Se modifican los vuelos que salen de origen, restando 2 a su horario de salida
	 * con el fin de facilitar la búsqueda de vuelos en funciones posteriores.
	 * Esta modifición se necesita para la función "buscar_ruta".
	 **/
	reducir_hora_salida_origen(vuelos, ciudades);

	// Vector de vuelos
	vector<vuelo> vuelos_por_id(vuelos.size());
	inicializar_con_vuelos(vuelos_por_id, vuelos);
	
	// Vector de conjunto de vuelos por ciudad.
	vector<set<vuelo> > vuelos_hasta(cant_ciudades);
	inicializar_conjuntos(ciudades, vuelos_hasta, vuelos_por_id);

	// Vector de vuelo_id, dado un vuelo me indica que proximo vuelo debo tomar
	vector<vuelo_id> ruta(cant_ciudades);

	
	bool hay_solucion = buscar_ruta(cant_ciudades-1, MAX_INT, ruta, vuelos_hasta, vuelos_por_id, ciudades);

	hora hora_res = -1;

	if (hay_solucion) {
		reconstruir_ruta(ruta, res, vuelos_por_id,  ciudades);
		hora_res = vuelos_por_id[ruta[cant_ciudades-1]].llegada;
	}

	delete ciudades;
	return hora_res;	
}

int main(int argc, char** argv){
	string origen,destino;
	int n;

	cin >> origen;
	cin >> destino;
	cin >> n;
	
	string ori, des;
	hora ini, fin;
	list<vuelo> vuelos;	
	vuelo_id id = 0;
	
	for(int i = 0; i < n; i++){
		cin >> ori;
		cin >> des;
		cin >> ini;
		cin >> fin;
		
		vuelos.push_back(vuelo(ori,des,ini,fin,id));
		id++;
	}

	list<vuelo_id> res;
	hora hora_llegada = ruta_de_vuelo(res, vuelos, origen, destino);

	if(hora_llegada == -1){
		cout << "NO" << endl;
	}else{
		cout << hora_llegada << " " << res.size() << " ";
		auto it = res.begin();
		for(int i = 0; i < res.size()-1; i++){
			cout << *it << " ";
			it++;
		}
		cout << *it << endl;
	}

	return 0;
}

