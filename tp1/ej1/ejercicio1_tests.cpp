#include "ejercicio1.h"
#include "time.h"
#include <chrono>
//El programa recibe la cantidad de iteraciones a realizar y devuelve el promedio y el minimo por pantalla
using namespace std::chrono;

int main(int argc,char** argv ){
	string participante;
	vector<int> tablones_recorridos;
	vector<int> puente;
	puente.push_back(0); 												//creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
	int saltos = 0;
	int n;
	cin >> n;
	int iteraciones;
	iteraciones = atoi(argv[1]);			
	high_resolution_clock reloj;
	while (getline(cin, participante)){ 				//cargo un participante
		if(!participante.empty()){  							//verifico si ya procese a todos
			//int n = puente_size(participante);  		//cargo el tamaño del puente
			int c = capacidad_salto(participante);  //cargo la capacidad de salto del participante siendo procesado
			vector<int> tablones_recorridos;
			vector<int> puente;
			tablones_recorridos.reserve(n + 2);
			puente.reserve(n + 2);
			puente.push_back(0); 												//creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
			int saltos = 0;
			crear_puente(puente,participante,n);		//cargo el puente del participante
			vector<int>::iterator it = puente.begin();
			int copia_iteraciones = iteraciones;
			size_t acum = 0, mi = 99999999;

			while(iteraciones != 0){
				vector<int> copia_tablones = tablones_recorridos;
				int copia_saltos = saltos;
                                copia_tablones.reserve(n + 2);
                                auto t1 = reloj.now();
				bool res = saltar_puente(puente, c, copia_saltos, copia_tablones, n); //verifico si el participante puede saltar el puente
				auto t2 = reloj.now();
				auto total = duration_cast<microseconds>(t2 - t1).count();
				acum = total;
				if (total < mi)	mi = total;
				iteraciones--;
			}
				cout << n << " " << mi  << endl;	
			}
		cin >> n;
	}
	return 0;
}
