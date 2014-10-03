#include "ejercicio3.h"
#include <chrono>

using namespace std::chrono;

int main(int argc,char* argv[]){
	int elems;
	string linea;
	int umbral;
	high_resolution_clock reloj;
	int iteraciones;
	iteraciones = atoi(argv[1]);
	while(getline(cin, linea)){
		if(linea.size()>2){
			elems = tomar_elementos(linea);
			umbral = tomar_umbral(linea);
			resultado vacio = resultado();
			list<producto> lista_productos = list<producto>();
			vector< vector<coef> > matriz;
			matriz.resize(elems);
			int i = 0;
			int rango;
			while(i < elems-1){
				int j = 0;
				while(j < elems-1-i){
					int n = matriz[i].size() +1;
					matriz[i].resize(n);
					scanf("%i",&rango);
					matriz[i][j]=rango;
					j++;
				}
				lista_productos.push_back(i+1);
      	i++;
			}
			lista_productos.push_back(i+1);
			//peor solucion
			resultado res_g = resultado();
			res_g.cant = elems +1;
			res_g.a_imprimir.resize(elems);
			vacio.a_imprimir.resize(elems);
			list<producto> copia_prod;
			resultado copia_res;
			size_t minimo = 999999999;
			while(iteraciones !=0 ){
				copia_prod = lista_productos;
				copia_res = vacio;
				auto t1 = reloj.now();
				poda_peligrosa(copia_res, copia_prod, matriz, umbral);
				llenar_camiones(copia_res, copia_prod, matriz, umbral, res_g); 
				auto t2= reloj.now();
				auto total = duration_cast<microseconds>(t2 - t1).count();
				if (total < minimo) minimo = total;
				iteraciones--;
			}
			cout << elems << " " << minimo << endl;
		}
 	}
	return 0;
}
