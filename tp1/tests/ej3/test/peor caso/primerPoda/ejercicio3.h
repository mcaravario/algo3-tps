#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#define producto int
#define coef int
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
	vector<int> a_imprimir;
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
	a_imprimir = vector<int>();
}

int peligrosidad_elem(list<producto>& ls, producto p, vector< vector<coef> > mz){
    list<producto>::iterator it = ls.begin();
    int res = 0;
    while(it != ls.end()){
      if(*it < p){
        res = res + mz[(*it)-1][p-1-(*it)]; // EJEMPlO: Producto en Lista 1, y producto a calc peligrosidad 2, res = res + mz[0][0]
      }else{
        res = res + mz[p-1][(*it)-1-p];			// EJEMPLO: Producto en Lista 3, y producto a calc peligrosidad 2, res = res + mz[1][0]
      }
      it++;
    }
  return res;
}

bool es_posible_agregar(resultado& res_parcial, producto p, vector< vector<coef> > mz, int umbral){
  if(!res_parcial.cant == 0){															//Si no hay elementos, es posible agregar
    list<camion>::iterator it = res_parcial.camiones.end();
    it--;																									// Se retorcede al ultimo elemnto
    int peligrosidad = it->pelig_acum;
    int pelig_nueva = peligrosidad_elem(it->productos,p, mz);
    if((peligrosidad + pelig_nueva) > umbral){
      return false;
    }else return true;
  }else return true;
}

//Esa funcion se encarga de descartar los casos que ya no son solucion. Es decir descar los casos al ir armandose
//cuando ya superan la cantidad de camiones de la solucion que se guardo anteriormente
bool sigue_siendo_sol(resultado& r, producto p, vector< vector<coef> > mz, int umbral,resultado& res_g){
  int cant_camiones = r.cant;
  if(!es_posible_agregar(r,p,mz,umbral)){
    cant_camiones ++;
  }
  if(cant_camiones < res_g.cant){
    return true;
  }else return false;

}

void mostrar_camiones(resultado& ls){
  list<camion>::iterator itc = ls.camiones.begin();
  int i=1;
  while(itc != ls.camiones.end()){
    list<producto>::iterator itp = itc->productos.begin();
    cout << "C" << i <<": ";
    while(itp != itc->productos.end()){
      cout << *itp <<" ";
      itp++;
    }
    itc++;
    cout << endl;
    i++;
  }
  cout << endl << endl;
}

void agregar_producto(resultado& res_parcial, producto p, vector< vector<coef> > mz, int umbral){
  if (res_parcial.cant == 0 || !es_posible_agregar(res_parcial,p, mz, umbral) ){//Si no es posible agregar un producto, o no existia el 
    camion nuevo = camion();																										//camion, se tiene que crear el camion y dps agregar
    res_parcial.camiones.push_back(nuevo);
    res_parcial.cant++;
  } else {
    int pelig_nueva = peligrosidad_elem(res_parcial.camiones.back().productos,p,mz);
    res_parcial.camiones.back().pelig_acum += pelig_nueva;
  }
  res_parcial.camiones.back().productos.push_back(p);
	res_parcial.a_imprimir[p-1]= res_parcial.cant;
}

void mostrar_res(resultado& ls){
  cout << ls.cant;
  vector<int>::iterator it = ls.a_imprimir.begin();
  while(it != ls.a_imprimir.end()){
    cout <<" " << *it;
		it++;
	}
	cout << endl;
}

void llenar_camiones(resultado& res_parcial, list<producto>& Q, vector< vector<coef> > mz, int umbral, resultado& res_g){
  if (Q.empty()){
    res_g = res_parcial;
  }else{
    list<producto>::iterator it = Q.begin();
    while(it != Q.end()){
			if(sigue_siendo_sol(res_parcial,*it,mz, umbral, res_g)){
        resultado res_parcial_copy = resultado();
				res_parcial_copy = res_parcial;
        list<producto> Q_copy = Q;
				
				agregar_producto(res_parcial_copy,*it,mz, umbral);
        
				list<producto>::iterator itp = find(Q_copy.begin(),Q_copy.end(),*it);
        Q_copy.erase(itp);
        
				llenar_camiones(res_parcial_copy,Q_copy, mz, umbral, res_g);
			}
			it++;
    }
  }
}

int tomar_elementos(string linea){
  stringstream l(linea);
  string cant_elem;
  getline(l, cant_elem);
  int cant = atoi(cant_elem.c_str());
  return cant;
}

int tomar_umbral(string linea){
  stringstream l(linea);
  string umbral;
  getline(l,umbral,' ');
  getline(l,umbral,' ');
  int um = atoi(umbral.c_str());
  return um;
}

