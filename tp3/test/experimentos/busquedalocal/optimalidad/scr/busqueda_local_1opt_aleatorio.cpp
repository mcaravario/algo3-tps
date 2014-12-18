#include "busqueda_local_aleatorio.h"
#include <chrono>

int main(int argc, char** argv){

		if (argc < 3){
			cout << "Se necesitan las iteraciones como parámetro." << endl;
			return 0;
		}

	int n,m,k,u,v,w,iteraciones, tipoResultado;
  cin >> n; 
	cin >> m;
  cin >> k;
	iteraciones = atoi(argv[2]);
 	tipoResultado = atoi(argv[3]);

	using namespace std::chrono;
	high_resolution_clock reloj;
	size_t minimo = MAX_INT;

	list<arista> aristas;
  /* Creo la lista de aristas. */
  for (int i = 0; i < m; i++){
    cin >> u;
    cin >> v;
    cin >> w;
    u--;
    v--;
		aristas.push_back(arista(u,v,w));
	}

	int pesoTotal = 0;
	while(iteraciones != 0){
  	srand(atoi(argv[1]));
		auto t_inicial = reloj.now();
		vector<int> posiciones = iniciar_local_1opt(aristas, n, k, pesoTotal, tipoResultado);
		auto t_final = reloj.now();
	
		auto t_total = duration_cast<microseconds>(t_final - t_inicial).count();
		
		if ((unsigned int) t_total < minimo) minimo = t_total;

		iteraciones--; 
	}
	
	cout << "Busqueda Local 1-opt" << endl << "Nodos: " << n << endl;
	cout << "Resultado: " << pesoTotal<< endl;
	cout << "Tiempo: " << minimo << endl << endl;
	return 0;
}
