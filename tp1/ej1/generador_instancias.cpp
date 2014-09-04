#include <iostream>
//#include <time.h>
#include <stdlib.h>
#include "ejercicio1.h"

using namespace std;

//Foward Declaration
void generar_valida(int n, int c);

int main(int argc, char** argv){
	// Recibe como parametros el C y el N.
	int c = atoi(argv[1]);
	int n = atoi(argv[2]);			
	cout << n << " " << c << " "
	generar_valida(n,c);

	return 0;
}

void generar_random(){	
	for(int i = 0; i<10; i++){
		int c = rand() % 10 + 1;
		int n = rand() % 40 + c;		//La canridad de tablones tiene que ser como minimo la capacidad de salto.
		cout << n << " ";
		cout << c << " 0 ";					// Se imprime el 0 de tierra.
		for(int j = 0; j < n;j++){
			int tablon = rand() % 2;
			cout << tablon << " ";
		}
	cout << endl;
	}
	cout << "0" << endl;	

}

void generar_instancia_aleatoria(vector<int>& puente){
	
	for (int i = 0; i < puente.size(); i++){
		puente[i] = rand() % 2;
	}
}

void mostrar_vector(vector<int>& vec){
	
	int i;
	for (i = 0; i < vec.size() -1; i++){
		cout << vec[i] << " ";
	}
	cout << vec[i] << endl;
}

void generar_valida(int n, int c){

	vector<int> puente(n);
	vector<int> tablones_recorridos;
	int saltos;
	bool parar = false;

	while (!parar){
		generar_instancia_aleatoria(puente);
		parar = saltar_puente(puente,c,saltos,tablones_recorridos,n);
	}

	// Salgo del while cuando la instancia es valida.
	
	mostrar_vector(puente);
}
