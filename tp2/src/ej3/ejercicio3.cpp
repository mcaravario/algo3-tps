#include "ejercicio3.h"
 

int main(){
	int cant_nodos;
	int cant_vertices;
	cin >>cant_nodos;
	cin >> cant_vertices;
//	string linea;
	vector<costo> costos(cant_nodos, 0);
	matriz_adya matriz(cant_nodos, costos);
	int max = 0;
	for(int i = 0; i < cant_vertices ; i++){
		int n1, n2, c;
		cin >> n1;
		cin >> n2;
		cin >> c;
		//Se crea matriz de adyacencias
		matriz[n1-1][n2-1]=c;
		matriz[n2-1][n1-1]=c;
		//Maximo costo
		if(max < c) max = c;
	}
	mostrar_result(armar_AGM(matriz, max, cant_nodos));	
	mostrar_matriz_adya(matriz);
	cout << "Maximo costo: " << max << endl;
	return 0;
}
