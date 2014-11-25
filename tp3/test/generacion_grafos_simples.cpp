#include <vector>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

//Foward Declaration
void generar_valida(int n, int m);

int main(int argc, char** argv){
  // Recibe como parametros el n (Cant productos) y el M (umbral).
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int k = atoi(argv[3]);
  cout << n << " " << m << " " << k <<endl;
  generar_valida(n,m);
  return 0;
}

void generar_valida(int n, int m){
	vector<list<int> > grafo(n+1, list<int>());
  for(int j = 1; j <= n-1; j++){
			int arista = rand()% 60;
			cout << j << " " <<  j+1 << " " << arista << endl;
			grafo[j].push_back(j+1);
	}
	int i = n-1;
	while(i< m){
		int	n1 = rand()% n+1;
		int n2 = rand()% n+1;
		list<int>::iterator it  = std::find(grafo[n1].begin(),grafo[n1].end(),n2);
		if (n1!=n2 && it == grafo[n1].end()){
			int arista = rand()% 60;
			cout << n1 << " " << n2 << " " << arista << endl;
			i++; 
		}
	}
	
/*
			i++;
			if (j > 2 && ((arista % 4) == 0)){
				arista = rand()% 60;
				cout << j << " " <<  j-2 << " " << arista << endl;
				i++;
			}
			if (j > 3 && ((arista % 3) == 0)){
				arista = rand()% 60;
				cout << j << " " <<  j-3 << " " << arista << endl;
				i++;
			}
			
			if (j > 4 &&  ((arista % 5)==0)){
				arista = rand()% 60;
				cout << j << " " <<  j-4 << " " << arista << endl;
				i++;
			}*/
}

