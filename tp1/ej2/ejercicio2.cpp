

#include "ejercicio2.h"
#include <iostream>
#include <set>

using namespace std;


int main(int argc, char** argv){

	int cant_edificios = atoi(argv[1]);
 
	list<vertice> res;

	bool (*fn_pt)(edificio,edificio) = comparar_edificios;

	set<edificio,bool (*)(edificio,edificio)> edificios(fn_pt);
	
	for(int i=0; i<cant_edificios; i++){

		int izq = atoi(argv[2+i*3]);

		int alt = atoi(argv[2+i*3+1]);
   
		int der = atoi(argv[2+i*3+2]); 
  
		vertice v1;

		vertice v2;

		v1.x = izq;
		v1.y = alt;
		v2.x = der;
		v2.y = alt;

		edificio ed;

		ed.v1 = v1;
		ed.v2 = v2;

		edificios.insert(ed);
	}
	set<edificio>::iterator its = edificios.begin();
	while (its != edificios.end()){
		cout << "(" << its->v1.x << "," << its->v1.y << ")  (" << its->v2.x << "," << its->v2.y << ")" << endl;
		its++;	
	}
	
	//~ edificio e1 = edificio(1,4,3);
	//~ edificio e2 = edificio(4,5,6);
	//~ 
	//~ cout << "(" << e1.v1.x << "," << e1.v1.y << ")  (" << e1.v2.x << "," << e1.v2.y << ")" << endl;
	//~ cout << "(" << e2.v1.x << "," << e2.v1.y << ")  (" << e2.v2.x << "," << e2.v2.y << ")" << endl;
	//~ 
	//~ cout << comparar_edificios(e1,e2) << endl;
	//~ cout << comparar_edificios(e2,e1) << endl;
	 	//~ 
	// Al salir del for tengo todos los edificios insertados ordenados en el avl

		

	return 0;
}
	
	











