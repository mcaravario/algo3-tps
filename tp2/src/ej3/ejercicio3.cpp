#include "ejercicio3.h"
 
int main(){
	int cant_nodos;
	int cant_vertices;
	cin >>cant_nodos;
	cin >> cant_vertices;
//	string linea; lo comente porque vi que es una variable que no se usa, fijarse si queda o no
	vector<costo> costos(cant_nodos, 0);
	matriz_adya matriz(cant_nodos, costos);
	list<enlace> enlaces;
	int max = 0;
	for(int i = 0; i < cant_vertices ; i++){
		int n1, n2, c;
		cin >> n1;
		cin >> n2;
		cin >> c;
		//Se crea matriz de adyacencias y listado de enlaces disponibles
		enlaces.push_back(enlace(n1,n2));
		matriz[n1-1][n2-1]=c;
		matriz[n2-1][n1-1]=c;
		//Maximo costo
		if(max < c) max = c;
	}
	result res = armar_AGM(matriz, max, cant_nodos, enlaces);
	mostrar_result(res);	
	mostrar_matriz_adya(matriz);
	cout << "Maximo costo: " << max << endl;
	return 0;
}

//para hacer la diferencia entre dos listas de enlaces tener en cuenta que (e1,e2) tiene que ser igual a (e2,e1)
