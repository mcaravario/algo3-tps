#include "ejercicio3C.h"
 
int main(){
	int cant_nodos;
	int cant_vertices;
	cin >> cant_nodos;
	cin >> cant_vertices;
	vector<costos> costos2(cant_nodos,costos(-1,-1,-1));
	matriz_adya matriz(cant_nodos, costos2);
	int max = 0;
	for(int i = 0; i < cant_vertices ; i++){
		int n1, n2, c;
		cin >> n1;
		cin >> n2;
		cin >> c;
		//Se crea matriz de adyacencias y listado de enlaces disponibles
		matriz[n1-1][n2-1]=costos(n1-1,n2-1,c);
		matriz[n2-1][n1-1]=costos(n2-1,n1-1,c);
		//Maximo costo
		if(max < c) max = c;
	}
	//mostrar_matriz_adya(matriz);
	result res = armar_AGM(matriz, max, cant_nodos);
	mostrar_result(res);	
	return 0;
}

//para hacer la diferencia entre dos listas de enlaces tener en cuenta que (e1,e2) tiene que ser igual a (e2,e1)
