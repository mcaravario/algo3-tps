#include <iostream>
#include <stdlib.h>
using namespace std;

//Foward Declaration
void generar_valida(int n, int M);

int main(int argc, char** argv){
  // Recibe como parametros el n (Cant productos) y el M (umbral).
  int n = atoi(argv[1]);
  int M = atoi(argv[2]);      
  cout << n << " " << M << " " << endl;
  generar_valida(n,M);
  return 0;
}

void generar_valida(int n,int M){
  int cant_elem = n;
  int umbral = M+1;
  for(int j = 1; j < cant_elem; j++){
    for(int k =j;k<cant_elem; k++){
      cout << "0" << " ";
    }
    cout << endl;
  }
}
