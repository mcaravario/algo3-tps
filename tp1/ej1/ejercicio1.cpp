#include "ejercicio1.h"
#include <cstdlib>
#include <stdio.h>


int main(int argc,char** argv ){

	
	
	int saltos = 0;
	
	vector<int> tablones_recorridos;					

	int n = atoi(argv[1]);

	int c = atoi(argv[2]);
	
	vector<int> puente;
	puente.push_back(0); //creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
	
	for (int i = 0; i < n; i++){
		
		int j = 3+i;	
		puente.push_back(atoi(argv[j]));	
	
	}	

	bool res = saltar_puente(puente, c, saltos, tablones_recorridos);
			
	if(res){
				
	   cout << saltos << " " ;

	   for(int l = 0; l< tablones_recorridos.size();l++){			
			
	   cout << tablones_recorridos[l] << " ";			
	   
	   }		
	
	}else {
		
	   cout << "no" << endl;	
	}	
return 0;
}
