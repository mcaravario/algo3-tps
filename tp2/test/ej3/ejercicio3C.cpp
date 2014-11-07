#include "ejercicio3C.h"
#include "time.h"
#include <chrono>

using namespace std::chrono;

int main(int argc, char*argv[]){
	int cant_nodos;
	int cant_vertices;
	cin >> cant_nodos;
	cin >> cant_vertices;
	vector<costos> costos2(cant_nodos,costos(-1,-1,-1));
	matriz_adya matriz(cant_nodos, costos2);
	int max = 0;
	int iteraciones = atoi(argv[1]);
	high_resolution_clock reloj;
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
	size_t mi = 99999999;
	while(iteraciones != 0){
		matriz_adya matriz_c = matriz;
		auto t1 =reloj.now();
		result res = armar_AGM(matriz_c, max, cant_nodos);
		auto t2 = reloj.now();
		auto total = duration_cast<microseconds>(t2-t1).count();
		if (total < mi) mi = total;
		iteraciones--;
	}
	cout << cant_nodos << " " << mi << endl;
	return 0;
}

//para hacer la diferencia entre dos listas de enlaces tener en cuenta que (e1,e2) tiene que ser igual a (e2,e1)
