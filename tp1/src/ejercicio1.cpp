#include "ejercicio1.h"



int main(){
	string participante;
	int n;
	cin >> n;
		
	while (getline(cin, participante)){ 			
		if(!participante.empty()){  				
			int c = capacidad_salto(participante);  
			vector<int> tablones_recorridos;
			vector<int> puente;
			tablones_recorridos.reserve(n+1);
			puente.reserve(n+1);
			//creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
			puente.push_back(0); 												
			int saltos = 0;
			//cargo el puente del participante
			crear_puente(puente,participante,n);		
			bool res = saltar_puente(puente, c, saltos, tablones_recorridos, n); 
			if(res){                								
				cout <<  saltos <<" ";
				for(unsigned int l = 0; l< tablones_recorridos.size();l++){
					cout << tablones_recorridos[l] << " ";
				}
				cout << endl;
			}else{         											
			cout << "no" << endl;
			}
		}
		cin >> n;
	}
	return 0;
}


//Esta funcion devuelve la posicion del proximo tablon a donde debo saltar
int siguiente_salto(int actual,const vector<int>& puente, int c, int tam){
	int res = c;			
	if(actual+c >= tam){
		return actual+c;
	} 	
	//En este ciclo voy reduciendo mi capacidad de salto hasta encontrar el primer tablon sano a saltar
	while(res!=0 && puente[actual+res]==1){ 
		res--;
	}
	return res+actual;	
}

//Esta es la funcion principal que resuelve el problema de saltar el puente
bool saltar_puente(const vector<int>& puente, int c, int& saltos, vector<int>& tablones_recorridos, int n ){
	//arranco fuera del puente
	int actual = 0; 												
	while (actual <= n -1){
		//calculo a donde debo saltar 											
		int whereTo = siguiente_salto(actual,puente,c, n);		
        if (whereTo == actual){
			//significa que no hay salto posible 		
            return false;
        }else{
            actual = whereTo; 						
            saltos++;		  						
            tablones_recorridos.push_back(actual);
        }
    }
	return true;
}

// Funciones utilizadas para procesar los datos de entrada.
int puente_size(string linea){
	stringstream line(linea);
	string tam;
	getline(line,tam,' ');
	return atoi(tam.c_str());
}


int capacidad_salto(string linea){
	stringstream line(linea);
	string jump;
	getline(line,jump,' ');
	getline(line,jump,' ');
  return atoi(jump.c_str());
}

void crear_puente(vector<int>& puente, string linea, int tam){
	stringstream line(linea);
	string escalon;
	getline(line,escalon, ' ');
	getline(line,escalon, ' ');
	for(int i = 0; i<tam; i++){
		getline(line, escalon, ' ');
		puente.push_back(atoi(escalon.c_str()));
	}
}
