#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#define producto int
#define coef int
//#define matriz_coef coef*
using namespace std;

struct camion{
	list<producto> productos;
	int pelig_acum;
	camion();
};


struct resultado{
	//INV: cant == camiones.size()
	list<camion> camiones;
	int cant;
	resultado();
};


camion::camion(){
	//INV: pelig_acum == sumar_peligrosidades_lista(productos);
	productos = list<producto>();
	pelig_acum = 0;	
}

resultado::resultado(){
	camiones = list<camion>();
	cant = 0;
}
