#include <iostream>
#include <stdlib.h>
using namespace std;

//Foward Declaration
void generar_valida(int n, int M);

int main(int argc, char** argv){
	if(argc < 2) cout << "faltan argumentos" << endl;  
	// Recibe como parametros el n (Cant productos) y el M (umbral).
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);      
  int k = atoi(argv[3]);      
  cout << n << " " << m << " " << k << endl;
  generar_valida(n,m);
  return 0;
}

void generar_valida(int n,int m){
  for(int j = 1; j <= m; j++){
			for (int i = (j+1); i<=n; i++){
			int arista = rand()% 60 + 1;
			cout << j << " " <<  i << " " << arista << endl;
			}
	}
}

