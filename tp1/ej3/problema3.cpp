#include "problema3.h"

int main(int argc,char* argv[]){
	int elems;
	string linea;
	int umbral;
	while(getline(cin, linea)){
		if(linea.size()>2){
		cout << "LINEA: " << linea << endl;
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
				cout << matriz[i][j];
				j++;
			}
			lista_productos.push_back(i+1);
      cout << endl;
      i++;
		}
		lista_productos.push_back(i+1);
		cout << "LISTA DE PRODUCTOS: ";
		list<producto>::iterator itl = lista_productos.begin();
		while(itl != lista_productos.end()){
			cout <<*itl<< " ";
			itl++;
		}
		cout<< endl;
		//peor solucion
		resultado res_g = resultado();
		res_g.cant = elems;
		llenar_camiones(vacio,lista_productos,matriz, umbral,res_g); 
		mostrar_res(res_g);
	}
 }
	return 0;
}
