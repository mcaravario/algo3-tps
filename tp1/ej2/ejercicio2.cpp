#include "ejercicio2.h"
#include <iostream>
#include <set>

using namespace std;


void mostrar_edificio(edificio ed){
	cout << "[ (" << ed.v1.x << "," << ed.v1.y << ") (" << ed.v2.x << "," << ed.v2.y << ") ]   "; 
}

int main(int argc, char** argv){
	

		int cant_edificios = atoi(argv[1]);
		list<vertice> res;
		set<edificio> edificios;
	
		for(int i=0; i<cant_edificios; i++){

			int izq = atoi(argv[2+i*3]);
			int alt = atoi(argv[2+i*3+1]);
			int der = atoi(argv[2+i*3+2]); 
 
			edificio ed = edificio(izq,alt,der); 
			edificios.insert(ed);
		}
		set<edificio>::iterator its = edificios.begin();
		while(its != edificios.end()){
			mostrar_edificio(*its);
			its++; 
		}
		cout << endl;

	
		res = generar_horizonte(edificios);
		list<vertice>::iterator it = res.begin();
		
		while(it != res.end()){
		cout << "(" <<  it->x << "," << it->y << ")" << endl;
		it++; 
		}
		
		
	return 0;
}
