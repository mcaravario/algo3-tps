#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>

using namespace std;


//La funcion recibe la cantidad de casilleros,la cantidad de caballos y una semilla.
int main(int argc, char** argv){
	srand(atoi(argv[3]));
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	cout << n << " " << k << endl;
	int f,c;
	for(int i=0; i<k ; i++){
		f = rand() % n;
		c = rand() % n;
		cout << f << " " << c << endl;
	}
	return 0;
}
