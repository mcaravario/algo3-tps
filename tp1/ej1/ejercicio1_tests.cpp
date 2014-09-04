#include "ejercicio1.h"
#include "time.h"
//El programa recibe la cantidad de iteraciones a realizar y devuelve el promedio y el minimo por pantalla

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

	while (getline(cin, participante)){ 				//cargo un participante
		if(!participante.empty()){  							//verifico si ya procese a todos
			//int n = puente_size(participante);  		//cargo el tamaño del puente
			int c = capacidad_salto(participante);  //cargo la capacidad de salto del participante siendo procesado
			vector<int> tablones_recorridos;
			vector<int> puente;
			puente.push_back(0); 												//creo el primer tablon en cero, el cual representa que estoy parado  en la tierra
			int saltos = 0;
			crear_puente(puente,participante,n);		//cargo el puente del participante
			vector<int>::iterator it = puente.begin();
			int copia_iteraciones = iteraciones;
			clock_t total,acum,inicio,fin,min;
			acum = 0;

			while(iteraciones != 0){
				vector<int> copia_tablones = tablones_recorridos;
				int copia_saltos = saltos;
				inicio = clock();
				bool res = saltar_puente(puente, c, copia_saltos, copia_tablones, n); //verifico si el participante puede saltar el puente
				fin = clock();
				total = fin - inicio;
				acum += total;
				if (iteraciones == copia_iteraciones || total < min)	min = total;
				iteraciones--;
			}
				cout << n << " " << (float)acum/ (float)copia_iteraciones << " " <<endl;	
			}
		cin >> n;
	}
	return 0;
}
