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
	int cant;
	camion();
};


struct resultado{
	//INV: cant == camiones.size()
	list<camion> camiones;
	int cant;
	vector<int> a_imprimir;
	resultado();
};

struct soluciones{
	list<resultado> resultados;
	int cant;
	soluciones();
};


camion::camion(){
	//INV: pelig_acum == sumar_peligrosidades_lista(productos);
	productos = list<producto>();
	pelig_acum = 0;	
	cant =0;
}

resultado::resultado(){
	camiones = list<camion>();
	cant = 0;
	a_imprimir = vector<int>();
}

soluciones::soluciones(){
	resultados = list<resultado>();
	cant = 0;
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

bool camion_igual(camion& c1, camion& c2){
	if(c1.cant == c2.cant){
		list<producto>::iterator it2 = c2.productos.begin();
		bool res_1 = true;
		bool res_2 = false;
		while(it2 != c2.productos.end() && res_1){
			list<producto>::iterator it1 = c1.productos.begin();
			res_2 = false;
			while (it1 != c1.productos.end() && !res_2){
				if(*it2 == *it1) res_2 = true;
				it1++;
			}
		
			if (res_2){
				 res_1 = true;
			}else res_1 = false;
		
			it2++;
		}
		
	/*	if (res_1){
			cout << "TRUE 1" << endl;
		}else cout << "FALSE 1" << endl;*/
			return res_1;
	}else return false;
}

bool camiones_iguales(list<camion>& c1, list<camion>& c2){
	list<camion>::iterator it2 = c2.begin();
	bool res_1 = true;
	bool res_2 = false;
	while(it2 != c2.end() && res_1){
		list<camion>::iterator it1 = c1.begin();
		res_2 = false;	
		while (it1 != c1.end() && !res_2){
			if(camion_igual(*it1, *it2)) res_2 = true;
			it1++;
		}
		if (res_2){
			 res_1 = true;
		}else res_1 = false;

		it2++;
	}
	/*if (res_1){
		cout << "TRUE 2" << endl;
	}else cout << "FALSE 2" << endl;*/
	return res_1;
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

void mostrar_productos(camion& c){
	list<producto>::iterator it = c.productos.begin();
	while (it != c.productos.end()){
		cout << *it << " ";
	it++;
	}
	cout << endl;
}

//Esa funcion se encarga de descartar los casos que ya no son solucion. Es decir descar los casos al ir armandose
//cuando ya superan la cantidad de camiones de la solucion que se guardo anteriormente
bool resultados_iguales(resultado& r, soluciones& solus){
	if(solus.cant != 0){
		bool res = false;
		list<resultado>::iterator it_resultados_solus = solus.resultados.begin();
		if(r.cant == it_resultados_solus->cant-1){ 
			while(it_resultados_solus != solus.resultados.end() && !res){
				if (camiones_iguales(it_resultados_solus->camiones,r.camiones)) res = true;
				it_resultados_solus++;
			}
			if(res){
				cout << "TRUE" << endl;
			}else cout << "FALSE"<< endl;
			return res;
		} else return false;
	}else return false;
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
	res_parcial.camiones.back().cant++;
	res_parcial.a_imprimir[p-1]= res_parcial.cant;
}



void mostrar_soluciones(soluciones& solus){
	int i = solus.cant;
	list<resultado>::iterator it = solus.resultados.begin(); 
	while(i != 0){
		mostrar_camiones(*it);
		i--;
		it++;
	}
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

void llenar_camiones(resultado& res_parcial, list<producto>& Q, vector< vector<coef> > mz, int umbral, resultado& res_g, soluciones& solus){
  if (Q.empty()){
    res_g = res_parcial;
		solus.resultados.push_back(res_parcial);
		solus.cant ++;
		cout << "camion resul: " << endl;
		mostrar_camiones(res_g);
  }else{
		list<producto>::iterator it = Q.begin();
    	while(it != Q.end()){
				cout << "producto: " << *it <<  endl;
				if(!es_posible_agregar(res_parcial,*it,mz,umbral)){
					if(!resultados_iguales(res_parcial, solus)){
					resultado res_parcial_copy = resultado();
					res_parcial_copy = res_parcial;
					list<producto> Q_copy = Q;
					agregar_producto(res_parcial_copy,*it,mz, umbral);
        
					list<producto>::iterator itp = find(Q_copy.begin(),Q_copy.end(),*it);
        	Q_copy.erase(itp);
        
					llenar_camiones(res_parcial_copy,Q_copy, mz, umbral, res_g, solus);
        	it++;
					}else it = Q.end();
				}else{
					resultado res_parcial_copy = resultado();
					res_parcial_copy = res_parcial;
					list<producto> Q_copy = Q;
					agregar_producto(res_parcial_copy,*it,mz, umbral);
        
					list<producto>::iterator itp = find(Q_copy.begin(),Q_copy.end(),*it);
        	Q_copy.erase(itp);
        
					llenar_camiones(res_parcial_copy,Q_copy, mz, umbral, res_g, solus);
        	it++;
				}
		}
  }/*


	camion c1 =camion();
	c1.productos.push_back(1);
	c1.productos.push_back(2);
	
	camion c2 =camion();
	c2.productos.push_back(3);
	c2.productos.push_back(4);
	c1.cant=2;
	c2.cant =2;
	
	camion c5 = camion();
	c5.productos.push_back(1);
	c5.productos.push_back(3);
	c5.productos.push_back(4);
	c5.cant= 3;
	
  resultado r = resultado();
	r.camiones.push_back(c1);
	r.camiones.push_back(c2);
	r.cant = 2;
	

	camion c3 = camion();
	c3.productos.push_back(3);
	camion c4 = camion();
	c4.productos.push_back(5);
	c4.productos.push_back(4);
	c4.productos.push_back(1);
	
	c3.cant = 1;
	c4.cant = 3;
	
	resultado r1 = resultado();
	r1.camiones.push_back(c3);
	r1.camiones.push_back(c4);
	r1.cant=2;
	solus.resultados.push_back(r);
	solus.cant++;
	solus.resultados.push_back(r1);
	solus.cant++;	
	resultado r2 = resultado();
	r2.camiones.push_back(c5);
	res_parcial= r2;
	res_parcial.cant =1;
	resultados_iguales(res_parcial,solus);*/
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

