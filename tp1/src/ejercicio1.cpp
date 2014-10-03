#include "ejercicio1.h"

int main(){
	string participante;
	int n;
	cin >> n;
		
	while (getline(cin, participante)){ 				//cargo un participante
		if(!participante.empty()){  							//verifico si ya procese a todos
			int c = capacidad_salto(participante);  //cargo la capacidad de salto del participante siendo procesado
			vector<int> tablones_recorridos;
			vector<int> puente;
			tablones_recorridos.reserve(n+1);
			puente.reserve(n+1);
			puente.push_back(0); 												//creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
			int saltos = 0;
			crear_puente(puente,participante,n);		//cargo el puente del participante
			bool res = saltar_puente(puente, c, saltos, tablones_recorridos, n); //verifico si el participante puede saltar el puente
			if(res){                								//si lo logro saltar imprimo la solucion
				cout <<  saltos <<" ";
				for(unsigned int l = 0; l< tablones_recorridos.size();l++){
					cout << tablones_recorridos[l] << " ";
				}
				cout << endl;
			}else{         													//si no lo logra saltar se imprime un "no"
			cout << "no" << endl;
}
		}
		cin >> n;
	}
	return 0;
}
