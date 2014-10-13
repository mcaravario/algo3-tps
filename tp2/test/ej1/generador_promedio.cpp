#include <iostream>
#include <stdlib.h>
using namespace std;

//Foward Declaration
void generar_valida(int n, int M);

int main(int argc, char** argv){
	//MUNDO
	string mundo[]={"BuenosAires", "Chaco", "Rosario", "Bariloche", "Baradero", "Lincol","MarDelPlata", "CarlosPaz", "SanPedro", "SanNicolas"};
	// Recibe como parametros el can_vuelos (Cantidad de vuelos).
  int cant_vuelos = atoi(argv[1]);
	cout << mundo[0] << " " << mundo[1]  <<" " << cant_vuelos << endl;
	cout << mundo[0] << " ";
	int i = 0;
	int destino = rand()% 10;
	int inicio = rand()% 15;
	int fin = rand()% 15 + inicio;
	for(i; i<cant_vuelos/3; i++){
		cout << mundo[destino] << " " << inicio << " " << fin << endl;
		cout << mundo[destino] << " "; 
		destino = rand()% 10 ;
		inicio = rand()% 15 + (fin+2);
		fin = rand()% 15 + inicio;
  }

	cout << mundo[1] << " "  << inicio << " " << fin << endl;
	cout << mundo[0] << " ";
	i++;
	
	destino = rand()% 10;
	inicio = rand()% 20;
	fin = rand()% 20 + inicio;
	for(i; i < cant_vuelos/2; i++){
		cout << mundo[destino] << " " << inicio << " " << fin << endl;
		cout << mundo[destino] << " ";
		destino = rand()% 10 ;
		inicio = rand()% 20 + (fin+2);
		fin = rand()% 20 + inicio;
  }
	
	cout << mundo[1] << " " << inicio << " " << fin << endl;
	cout << mundo[0] << " ";
	i++;
	
	destino = rand()% 10;
	inicio = rand()% 5;
	fin = rand()% 5 + inicio;
	for(i; i < cant_vuelos-1; i++){
		cout << mundo[destino] << " " << inicio << " " << fin << endl;
		cout << mundo[destino] << " ";
		destino = rand()% 10 ;
		inicio = rand()% 5 + (fin+2);
		fin = rand()% 5 + inicio;
  }
	
	inicio = rand()% 10 + (fin+2);
	fin = rand()% 10 + inicio;
	cout << mundo[1] << " " << inicio << " " << fin;

	return 0;
	
}
