#include "ejercicio1.h"
#include <chrono>

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


void inicializar_con_vuelos(vector<vuelo>& res, list<vuelo>& ls){
	
	auto it = ls.begin();			
	for (int i = 0; i < ls.size(); i++){
		res[i] = *it;
		it++;
	}
}



/**
 * Esta función ubica en la posición (i,j) de la matriz todos los vuelos
 *	que salen de i y llegan a j.
 *
 *	En la lista que está en cada posición no se agrega el vuelo, si no su
 *	identificador.
 *
 **/
void ubicar_vuelos(vector<vector<list<vuelo_id> > >& mz, list<vuelo>& vs, Trie *t){
	
	for (auto it = vs.begin(); it != vs.end(); it++){
		mz[t->get_id(it->ori)][t->get_id(it->des)].push_back(it->id);
	}
}


/**
 *	Devuelve el el próximo vuelo que llega antes a destino.
 **/
vuelo_id proximo_vuelo(ciudad_id ciudad, hora h, list<vuelo_id>& ls, vector<vuelo>& vs){

	vuelo res = vuelo();

	/* Si la ciudad es origen, no tengo que esperar 2 hs para tomar un vuelo.
	**/
	if (ciudad == 0){
		for (auto it = ls.begin(); it != ls.end(); it++){	
			if (res.id == -1 || vs[*it].llegada < res.llegada){
				res = vs[*it];
			}
		}

	} else {

		for (auto it = ls.begin(); it != ls.end(); it++){	
			if (h + 2  <= vs[*it].salida && (res.id == -1 || vs[*it].llegada < res.llegada)){
				res = vs[*it];
			}
		}
	}
	return res.id;
}


/**
 *	Pone en la lista res (viene vacía) los vuelos tomados para
 *	llegar a destino (última posición del arreglo) desde
 *	origen (primera posición del arreglo, con ID = 0).
 *	Si no se llega origen, no hay camino y se devuelve false.
 *	Si lo hay, devuelve true.
 **/
bool reconstruir_camino(list<vuelo_id>& res, vector<camino>& cm){

	camino actual = cm.back();
	while(actual.c != -1 && actual.c != INICIO){
		res.push_front(actual.v);
		actual = cm[actual.c];
	}

	return actual.c == INICIO;
}


/*	Algoritmo que resuelve el problema. Solamente toma la lista de vuelos, y
 *	las ciudades de origen y destino, junto con una lista resultante que se 
 *	modifica una vez encontrada la solución óptima.
 **/
int ruta_de_vuelo(list<vuelo_id>& res, list<vuelo>& vuelos, string origen, string destino){

	 /* Primero creo e inicializo todas las estructuras que necesito:
		* -Un trie para mapear ciudades con un ID entero de 0 a #ciudades-1
		* -Un arreglo de vuelos, donde la posición i corresponde al vuelo con id = i.
		* -Una matriz de lista de vuelo_id que dado dos ID de ciudades me 
		* 	de los vuelos que parten de una y lleguen a la otra.
		* -Un arreglo que dada una ciudad me indica cómo se llega, o sea
		* 	qué vuelos hay que tomar.
		* -Un arreglo que dada una ciudad me indica el (menor) horario al que se llega.
	 **/
	// Trie de ciudades
	Trie* ciudades = new Trie();
	mapear_ciudades(ciudades, vuelos, origen, destino);
	int cant_ciudades = ciudades->size();

	// Vector de vuelos
	vector<vuelo> vuelos_por_id(vuelos.size());
	inicializar_con_vuelos(vuelos_por_id, vuelos);

	// Matriz de vuelos por par de ciudades.
	vector<vector<list<vuelo_id> > >  vuelos_entre(cant_ciudades, vector<list<vuelo_id> >(cant_ciudades));
	ubicar_vuelos(vuelos_entre, vuelos, ciudades);

	// Vector de caminos (vuelos que tomar) a una ciudad.
	vector<camino> caminos(cant_ciudades);

	// Vector de horario de llegada a una ciudad.
	vector<hora> arribos(cant_ciudades);

	// El horario de llegada a la ciudad inicial es 0.
	arribos[0] = 0;

	/* No hay que tomar ningún vuelo para llegar a origen.
	 * Se asigna el valor INICIO para saber si se llega
	 * a origen en reconstruir camino.
	**/
	caminos[0] = camino(INICIO,INICIO);

	/**
	 *	La manera de resolver el ejercicio es programación dinámica
	 *	"bottom-up", es decir, iremos resolviendo primero la mejor
	 *	forma para llegar a las primeras ciudades, hasta llegar a
	 *	destino.
	 *
	 *	El cilo recorre todas las ciudades, fijándose cuál es 
	 *	la mejor forma de llegar a dicha ciudad, considerando 
	 *	todas las evaluadas hasta el momento.
	 *
	 *	Invariante de ciclo:
	 *	Al terminar la i-ésima iteración, para todo j <= i, en
	 *	arribos[j] tengo la mínima hora a la que puedo llegar
	 *	a esa ciudad, considerando las ciudades 0..j. Y en 
	 *	caminos[j] está descripto el camino para llegar a esa
	 *	hora.
	 *	Entonces, como destino es la ciudad n-1, en la última
	 *	iteración consideré	todas las ciudades anteriores
	 *	o sea, todas. 
	 **/
	
	for (int i = 1; i < cant_ciudades; i++){
		hora h_min = MAX_INT;
		camino cm = camino();
		for (int j = 0; j < i; j++){
			vuelo_id mejor_vuelo = proximo_vuelo(j, arribos[j], vuelos_entre[j][i], vuelos_por_id);
			if (mejor_vuelo != -1 && h_min > vuelos_por_id[mejor_vuelo].llegada){
				h_min = vuelos_por_id[mejor_vuelo].llegada;
				cm.c = j;
				cm.v = vuelos_por_id[mejor_vuelo].id;
			}
		}
		arribos[i] = h_min;
		caminos[i] = cm;
	}
	borrar_trie(ciudades);
	delete ciudades;
	
	/**
	 *	Como el camino para llegar a destino está
	 *	definido recursivamente en el arreglo "caminos"
	 *	llamo a una función que recorre el arreglo
	 *	reconstruyendo la solución.
	 **/
	if (reconstruir_camino(res, caminos)){
		return arribos[cant_ciudades-1];
	} else {
		return -1;
	}
}

//recibe la cantidad de iteraciones y la cantidad de vuelos que recibe
int main(int argc, char** argv){
	string origen;
	string destino;
	int n;
	int iteraciones = atoi(argv[1]);
	int cant_vuelos = atoi(argv[2]);
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

	using namespace std::chrono;
	high_resolution_clock reloj;
	size_t mi = 99999999;
	list<vuelo_id> res;
	
	while(iteraciones != 0){
		res.clear();
		auto t1 = reloj.now();
		int hora_llegada = ruta_de_vuelo(res, vuelos, origen, destino);
		auto t2 = reloj.now();
		auto total = duration_cast<microseconds>(t2-t1).count();

		if(total < mi) mi = total;
		iteraciones--;
	}
	cout << cant_vuelos << " " << mi << endl;	
}

