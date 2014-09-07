#include "ejercicio2_nuevo.h"


set<vertice> generar_horizonte(set<edificio>& edificios)
{
	// creo el diccionario por y
	dicc_y por_altura;
	crear_dicc_edificio_por_y(por_altura, edificios);
	
}

void agregar_en_dicc_y(dicc_y& por_altura, edificio nuevo)
{
	if (por_altura.find(nuevo.y) != por_altura.end()){
		
	}
}	

void generar_estructuras(int cant_ed, dicc_y& por_altura, dicc_x& por_ejex)
{
	list<vertice> res;
	int izq;
	int alt;
	int der;
	int i;

	for (i = 0; i < cant_ed; i++){
	
		cin >> izq;
		cin >> alt;
		cin >> der;
	
		edificio nuevo = edificio(izq, alt, der);
		por_ejex.insert(nuevo);
		agregar_en_dicc_y(dicc_y, nuevo);

	}
	res = generar_horizonte(edificios);
	return res;
}

// TODO
inline void mostrar_vertice(vertice v){
	cout << v.x << " " << v.y << ")"; 
}

void mostrar_res(set<vertice> res)
{
	auto it = res.begin();
	while (it != res.end()){
		mostrar_vertice(*it);
	}
}


int main(int argc, char** argv){

		int cant_ed;
		bool parar = false;
		while (!parar){
			cin >> cant_ed;
			if (cant_ed == 0){
				parar = true;
			} else {
				dicc_y por_altura;
				dicc_x por_ejex;
				set<vertice> res;
				generar_estructuras(cant_ed, por_altura, por_ejex);
				generar_horizonte(por_altura, res, por_ejex);
				mostrar_res(res);
			}
	}
	return 0;
}



