#include <iostream>
#include <stdlib.h>
using namespace std;

//Foward Declaration
void generar_valida(int n, int M);

int main(int argc, char** argv){
  // Recibe como parametros el n (Cant productos) y el M (umbral).
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);      
  cout << n << " " << m << " " << endl;
  generar_valida(n,m);
  return 0;
}

void generar_valida(int n,int m){
  for(int j = 1; j <= m; j++){
			for (int i = (j+1); i<=n; i++){
			int arista = rand()% 20 -1;
			cout << j << " " <<  i << " " << arista << endl;
			}
	}
}

