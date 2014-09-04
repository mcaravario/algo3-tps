#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

int main(){
	
	/*****   CASOS BORDES   *****/

	//CASO 1

//	cout << "3 2" << endl;
//	cout << "0 0" << endl;
//	cout << "0" << endl;

	
	/*****   CASOS RANDOM   *****/
	for(int i = 0; i < 5; i++){
		int cant_elem = rand()%  5 + 3;
		int umbral = rand()% 30 + 3;
		cout<< cant_elem <<" " << umbral << endl;
		for(int j = 1; j < cant_elem; j++){
			for(int k =j;k<cant_elem; k++){
				int coef = rand()% 14;
				cout << coef << " ";
			}
			cout << endl;
		}
	}
	

	return 0;
}
