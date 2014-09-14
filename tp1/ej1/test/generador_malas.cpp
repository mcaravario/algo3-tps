#include <iostream>
//#include <time.h>
#include <stdlib.h>
#include "ejercicio1.h"

using namespace std;

//Foward Declaration
void generar_mala(vector<int>& puente, int c);
void mostrar_vector(vector<int>&);

int main(int argc, char** argv){
	// Recibe como parametros el C y el N.
	int c = atoi(argv[1]);
	int n = atoi(argv[2]);			
	cout << n << " " << c << " ";
	vector<int> puente(n);
	generar_mala(puente,c);
	mostrar_vector(puente);

	return 0;
}

// PRE: C tiene que ser menor a puente.size()
void generar_mala(vector<int>& puente,int c){
	int fin = puente.size()/c;
	for (int i = 0; i < puente.size();i++){
		puente[i]=1;
	}
	puente[0] = 0;
	int i = c;
	while (i < puente.size()-1){
		puente[i] = 0;
		puente[i+1] = 0;
		i = i + c + 1;
	}
}

void mostrar_vector(vector<int>& vec){
	
	unsigned int i;
	for (i = 0; i < vec.size() -1; i++){
		cout << vec[i] << " ";
	}
	cout << vec[i] << endl;
}


