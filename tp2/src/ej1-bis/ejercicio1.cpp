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


void inicializar_con_vuelos(vector<vuelo>& res, list<vuelo>& ls){
	
	auto it = ls.begin();			
	for (int i = 0; i < ls.size(); i++){
		res[i] = *it;
		it++;
	}
}



/*	Esta función ubica en la posición (i,j) de la matriz todos los vuelos
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


/*	Algoritmo que resuelve el problema. Solamente toma la lista de vuelos, y 
 *	las ciudades de origen y destino, junto con una lista resultante que se 
 *	modifica una vez encontrada la solución óptima.
 **/
				
int ruta_de_vuelo(list<int> res, list<vuelo> vuelos, string origen, string destino){
	
	Trie* ciudades = new Trie();
	mapear_ciudades(ciudades, vuelos, origen, destino);
	int cant_ciudades = ciudades.size();
	vector<vuelo> vuelos_por_id(cant_ciudades);
	inicializar_con_vuelos(vuelos, vuelos_por_id);
	vector<vector<list<vuelo> > >  vuelos_entre(cant_ciudades, vector<list<vuelo> >(cant_ciudades));
	ubicar_vuelos(vuelos_entre, vuelos, ciudades);

}

int main(int argc, char** argv){
	string origen,destino;
	int n;

	cin >> origen;
	cin >> destino;
	cin >> n;
	
	string ori,des,ini,fin;
	list<vuelo> vuelos;	
	int id = 0;

	for(int i = 0; i < n; i++){
		cin >> ori;
		cin >> des;
		cin >> ini;
		cin >> fin;
		
		vuelos.push_back(vuelo(ori,des,ini,fin,id));
		id++;
	}

	list<int> res;
	int hora_llegada = ruta_de_vuelos(res, vuelos, origen, destino);

	if(hora_llegada == -1){
		cout << "NO";
	}else{
		cout << hora_llegada << " " << res.size() << " ";
		auto it = res.begin();
		for(int i = 0; i < res.size()-1; i++){
			cout << it->id << " ";
			it++:
		}
		cout << it->id << endl;
	} 

}
