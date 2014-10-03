#include <iostream>
#include <stdlib.h>
#include "ejercicio1.h"

using namespace std;

//Foward Declaration
void mostrar_vector(vector<int>&);

// Obs, hay muchos buenos casos, no solo el arreglo lleno de ceros, basta con "aprovechar"
//+ al maximo la capacidad de salto en toda iteracion del algoritmo que lo resuelve
int main(int argc, char** argv){
	// Recibe como parametros el C y el N.
	int c = atoi(argv[1]);
	int n = atoi(argv[2]);			
	cout << n << " " << c << " ";
	vector<int> puente(n,0);
	mostrar_vector(puente);

	return 0;
}


void mostrar_vector(vector<int>& vec){
	
	unsigned int i;
	for (i = 0; i < vec.size() -1; i++){
		cout << vec[i] << " ";
	}
	cout << vec[i] << endl;
}


