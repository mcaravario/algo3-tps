#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#define MAX_INT 2147483647
#define producto unsigned int
#define coef unsigned int
using namespace std;

struct camion{
	list<producto> productos;
	unsigned int pelig_acum;
	camion();
};


struct resultado{
	//INV: cant == camiones.size()
	list<camion> camiones;
  unsigned	int cant;
	vector<unsigned int> a_imprimir;
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
	a_imprimir = vector<unsigned int>();
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

bool es_posible_agregar(resultado& res_parcial, producto p, vector< vector<coef> > mz, unsigned  int umbral){
  if(!res_parcial.cant == 0){															//Si no hay elementos, es posible agregar
    list<camion>::iterator it = res_parcial.camiones.end();
    it--;																									// Se retorcede al ultimo elemnto
    unsigned int peligrosidad = it->pelig_acum;
    unsigned int pelig_nueva = peligrosidad_elem(it->productos,p, mz);
    if((peligrosidad + pelig_nueva) > umbral){
      return false;
    }else return true;
  }else return true;
}

//Esa funcion se encarga de descartar los casos que ya no son solucion. Es decir descar los casos al ir armandose
//cuando ya superan la cantidad de camiones de la solucion que se guardo anteriormente
bool sigue_siendo_sol(resultado& r, producto p, vector< vector<coef> > mz, unsigned int umbral,resultado& res_g){
  unsigned int cant_camiones = r.cant;
  if(!es_posible_agregar(r,p,mz,umbral)){
    cant_camiones ++;
  }
  
  return cant_camiones < res_g.cant;
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

void agregar_producto(resultado& res_parcial, producto p, vector< vector<coef> > mz, unsigned int umbral){
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
  auto it = ls.a_imprimir.begin();
  while(it != ls.a_imprimir.end()){
    cout <<" " << *it;
		it++;
	}
	cout << endl;
}

inline coef minimo(coef a, coef b){
  return (a <= b) ? a : b;
}


/* PRE: la lista tiene al menos dos productos.
 * Este algoritmo es n^2
 **/
coef min_coef(list<producto>& Q, vector< vector<coef> > mz){

  coef min = MAX_INT;
  auto primero = Q.begin();
  
  while (primero != Q.end()){
    auto segundo = primero;
    segundo++;
    while(segundo != Q.end()){
      min = minimo(min,mz[*primero - 1][*segundo - *primero - 1]);
      segundo++;
    }
    primero++;
  }
  return min;
}


//PRE: existe un camión en resultado
bool poda_min(list<producto>& Q, vector< vector<coef> > mz, resultado& res_parcial, unsigned int max_camiones, unsigned int umbral){

	if(Q.size() > 1 && res_parcial.cant !=0){ 
	/* Primero me fijo cuantos productos puedo agregar en el camión a medio
   * llenar */
  	auto itp = Q.begin();
  	auto itc = res_parcial.camiones.end();
		itc--;
  	unsigned int min = min_coef(Q,mz);
 		unsigned int pelig_nuevo = itc->pelig_acum;
  	unsigned int cant_agregados = itc->productos.size();
		while ((((pelig_nuevo + min*cant_agregados)) <= umbral) && (itp != Q.end()) ){
    	pelig_nuevo += min*cant_agregados;
    	cant_agregados++;
    	itp++;
  	}
  	/* Si se llego al final de la lista de productos, entonces la poda no fue
    	* fructífera*/
  	if (itp == Q.end()) return true;

  	/* Necesito saber cuantos productos quedan para agregar, para así calcular
   	* la cantidad de camiones que necesito para agregar a todos.
   	**/
  	unsigned productos_restantes = Q.size() - cant_agregados;
  
  	/* Con un while calculo la cantidad de productos que entran en un camión
   	* vacío.
   	**/
  	unsigned int peligrosidad = 0;
  	unsigned int productos_por_camion = 0;
  	while ( (peligrosidad + min*productos_por_camion) <= umbral){
    	peligrosidad += min*productos_por_camion;
    	productos_por_camion++;
  	}

  	/* En cant_agregados tengo los productos que entran por camión*/
  	/* Veamos cuantos camiones tengo disponibles, y cuantos necesito para
   	* ocupar con los productos*/

		unsigned int camiones_disponibles = max_camiones - res_parcial.cant;
 		unsigned int camiones_necesarios = productos_restantes/productos_por_camion + ((productos_restantes%productos_por_camion != 0) ? 1 : 0);
 		return camiones_necesarios < camiones_disponibles;
	}else return true;
}

void llenar_camiones(resultado& res_parcial, list<producto>& Q, vector<vector<coef> > mz, unsigned int umbral, resultado& res_g){
  if (Q.empty()){
    res_g = res_parcial;
  }else{
    list<producto>::iterator it = Q.begin();
    while(it != Q.end()){
      
			if(poda_min(Q,mz, res_parcial,umbral,res_g.cant) && sigue_siendo_sol(res_parcial,*it,mz, umbral, res_g)){
        
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
  unsigned int um = atoi(umbral.c_str());
  return um;
}

