#include "ejercicio2.h"
#include <iostream>
#include <string>
#include <set>
#include <sstream>

using namespace std;


void mostrar_edificios(list<vertice>& edificios){
	list<vertice>::iterator it = edificios.begin();
	while (it != edificios.end()){
		cout << it->x << " " << it->y << " ";
		it++;
	}
	cout << endl;
}


list<vertice> pasar_params_y_correr(int cant_ed){

	list<vertice> res;
	set<edificio> edificios;

	int izq;
	int alt;
	int der;
	int i;

	for (i = 0; i < cant_ed; i++){
	
		cin >> izq;
		cin >> alt;
		cin >> der;
	
		edificio nuevo = edificio(izq,alt,der);
		edificios.insert(nuevo);
	}
	res = generar_horizonte(edificios);
	return res;
}

int main(int argc, char** argv){

		int cant_ed;
		bool parar = false;
		while (!parar){
			cin >> cant_ed;
			if (cant_ed == 0){
				parar = true;
			} else {
				list<vertice> res = pasar_params_y_correr(cant_ed);
				mostrar_edificios(res);
			}
	}
	return 0;
}
