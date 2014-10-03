#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include "ejercicio2.h"

using namespace std;

// La funcion recibe la cantidad de edificios a crear, una semilla y genera una instancia valida aleatoria.
int main(int argc, char** argv){
	int cant_ed;
  cant_ed = atoi(argv[1]);
	srand(atoi(argv[2]));
	cout << cant_ed << " ";
	for (int i = 0; i < cant_ed; i++){
		int x1 = rand() % 100;
		int x2 = rand() % 50;
		int y = rand() % 200;
		if(x2 < x1 ){
 		  int c = x2;
			x2 = x1;
    	x1 = c;
		}		
		
		if(y == 0){
			y = rand() % 15;
		}
		
	cout << x1 << " " << y << " " << x2;
        if(i!=cant_ed-1)
          cout << " ";
      }
	cout << endl << 0;
      return 0;

}
