#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(){
	
	/*****   CASOS BORDES  ****/
	
	// CASO 1:
	
	// CASO 2:

	
	/*****   CASOS RANDOM   *****/
	
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
	/***** FIN DEL TEST *****/
	return 0;
}
