#include "ejercicio3.h"

int main(){
	int elems;
	string linea;
	int umbral;
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
			res_g.cant = elems;
			res_g.a_imprimir.resize(elems);
			vacio.a_imprimir.resize(elems);
			llenar_camiones(vacio,lista_productos,matriz, umbral,res_g); 
			mostrar_camiones(res_g);
			mostrar_res(res_g);
		}
 	}
	return 0;
}
