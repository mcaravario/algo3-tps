#include "ejercicio3.h"

int main(int argc,char* argv[]){
	int elems;
	string linea;
	int umbral;
	while(getline(cin, linea)){
		if(linea.size()>2){
			elems = tomar_elementos(linea);
			umbral = tomar_umbral(linea);
			resultado vacio = resultado();
			list<producto> lista_productos = list<producto>();
			vector< vector<int> > matriz;
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
					cout << rango << " ";
					j++;
				}
				cout << endl;
				lista_productos.push_back(i+1);
      	i++;
			}
			lista_productos.push_back(i+1);
			//peor solucion
			resultado res_g = resultado();
			res_g.cant = elems;
			res_g.a_imprimir.resize(elems);
			vacio.a_imprimir.resize(elems);
			soluciones solus = soluciones();
			llenar_camiones(vacio,lista_productos,matriz, umbral,res_g,solus); 
			mostrar_camiones(res_g);
			mostrar_res(res_g);
		}
 	}
	return 0;
}
