#include <stdlib.h>
#include <iostream>
#include "string.h"

using namespace std;
//Le paso la cantidad de vuelos, duracion maxima de vuelo(hora maxima de inicio) y la semilla
int main(int argc, char** argv){
	srand(atoi(argv[3]));
	int hora = atoi(argv[2]);
	string mundo[]={"BuenosAires", "Chaco", "Rosario", "Bariloche", "Baradero", "Lincol","MarDelPlata", "CarlosPaz", "SanPedro", "SanNicolas"};
	
	int origen = rand() % 10;
	int destino = (origen + 3) % 10;
	int cant_vuelos = atoi(argv[1]);
	
	cout << mundo[origen] << " " << mundo[destino] << " " << cant_vuelos << endl;
	
	string ori,des;
	int ini,fin;

	for(int i = 0; i < cant_vuelos; i++){
		int a = rand() % 10;
		ori = mundo[a];
		int b;
		
		do{
			b = rand() % 10;
		}while(a == b);

		des = mundo[b];
		ini = rand() % hora;
		fin = ini + (rand() % hora);

		cout << ori << " " << des << " " << ini << " " << fin << endl;
	}

	return 0;
}
