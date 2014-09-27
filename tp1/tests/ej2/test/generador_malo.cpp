#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include "ejercicio2.h"

using namespace std;

// La funcion recibe la cantidad de edificios a crear, una semilla y genera una instancia mala en la que todos los edificios estan pegados y con la misma altura.
int main(int argc, char** argv){
	int cant_ed;
  cant_ed = atoi(argv[1]);
	srand(atoi(argv[2]));
	cout << cant_ed << " ";

	int y = rand() % 60;
	int x1 = rand() % 200;
	int x2 = x1 + rand() % 120;
	cant_ed--;
	cout << x1 << " " << y << " " << x2 << " ";
	for (int i = 0; i < cant_ed; i++){
		x1 = x2;
		x2 = x1 + rand() % 100;
		cout << x1 << " " << y << " " << x2;
		
    if(i!=cant_ed-1)
        cout << " ";
 

   }
	cout << endl << 0;
      return 0;

}
