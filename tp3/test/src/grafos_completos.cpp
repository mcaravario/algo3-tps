#include <iostream>
#include <stdlib.h>
using namespace std;

//Foward Declaration
void generar_valida(int n, int M);

int main(int argc, char** argv){
	if(argc < 3) cout << "faltan argumentos" << endl;  
	// Recibe como parametros el n (cant nodos), el k (numero de conjuntos) y la semilla.
  int n = atoi(argv[1]);
  int k = atoi(argv[2]);      
  int s = atoi(argv[3]);      
	int	m = (n*(n-1))/2;

	srand(s);
  cout << n << " " << m << " " << k << endl;
  generar_valida(n,m);
  return 0;
}

void generar_valida(int n, int m){
  for(int j = 1; j <= m; j++){
			for (int i = (j+1); i<=n; i++){
				int arista = rand()% 60 + 1;
				cout << j << " " <<  i << " " << arista << endl;
			}
	}
}

