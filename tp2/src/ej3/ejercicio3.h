#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#define costo int
#define costo int
#define matriz_adya vector< vector<costo> >

using namespace std;

void mostrar_matriz_adya(matriz_adya& matriz){
	for (int i=0; i< matriz.size(); i++){
		for(int j = 0; j< matriz.size(); j++){
			cout << matriz[i][j] << " " ;
		}
		cout << endl;
	}
}
