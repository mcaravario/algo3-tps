#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <sstream>

using namespace std;

int siguiente_salto(int actual, vector<int> puente, int c, int tam){
	int n = 0; 						//variable para evitar bugs cuando estoy fuera del puente
	int res = c;					//cuanto voy a poder saltar
	if(actual+c >= tam){
		return actual+c;} 	//si con mi capacidad logro salir del puente salgo
	if(actual == -1){ 		//chequeo del primer salto
		n=0;
	}else{
		n=actual;
	}
	while(res!=0 && puente[n+res]==1){ //voy reduciendo mi capacidad de salto hasta encontrar el primer tablon sano a saltar
		res--;
	}
	return res+actual;								//retorno la posicion del proximo tablon donde salto
}



bool saltar_puente(vector<int> puente, int c, int& saltos, vector<int>& tablones_recorridos, int n ){

    int actual = 0; 																						//arranco fuera del puente
    int tam = n;
    while (actual <= tam -1){ 																	//recorro hasta salir del puente
        int whereTo = siguiente_salto(actual,puente,c, tam);		//calculo mi proximo salto
        if (whereTo == actual){ 																//significa que no hay salto posible
            return false;
        }else{
            actual = whereTo; 																	//me muevo al proximo tablon
            saltos++;		  																			//incremento los saltos que realice
            tablones_recorridos.push_back(actual); 							//grabo los tablones por donde pase
        }
    }
    return true;
}

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
