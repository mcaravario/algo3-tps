#include "problema3.h"

resultado res_g = resultado();
int k =1;
int umbral =9;

bool sigue_siendo_sol(resultado& r, producto q){
		return true;
}

int peligrosidad_elem(list<producto>& ls, producto p, coef mz[4][4]){
	list<producto>::iterator it = ls.begin();
	int res = 0;
	while(it != ls.end()){
//		cout << "i: " << (*it) << " j: " << p << endl;
		if(*it < p){
//			cout <<"i<: " << (*it)-1 << endl;
//			cout <<"j<: " <<  p-1-(*it) << endl;
			res = res + mz[(*it)-1][p-1-(*it)];
		}else{
//			cout <<"i: " << p-1 << endl;
//			cout <<"j: " << (*it)-1-p << endl;
			res = res + mz[p-1][(*it)-1-p];
		}
		it++;
	}
//	cout << "res: " << res <<endl;
	return res; 
}
	

bool es_posible_agregar(resultado& res_parcial, producto p, coef mz[4][4]){
	list<camion>::iterator it = res_parcial.camiones.end();
	it--;
	int peligrosidad = it->pelig_acum;
	int pelig_nueva = peligrosidad_elem(it->productos,p, mz);
	if((peligrosidad + pelig_nueva) > umbral){
		return false;
	}
	return true;
}


void agregar_producto(resultado& res_parcial, producto p, coef mz[4][4]){

	if (res_parcial.cant == 0 || !es_posible_agregar(res_parcial,p, mz) ){
		camion nuevo = camion();
		res_parcial.camiones.push_back(nuevo);
		res_parcial.cant++;
	} else {
		int pelig_nueva = peligrosidad_elem(res_parcial.camiones.back().productos,p,mz);
		res_parcial.camiones.back().pelig_acum += pelig_nueva;
	}
	res_parcial.camiones.back().productos.push_back(p);
}

void mostrar_camiones(resultado& ls){
	list<camion>::iterator itc = ls.camiones.begin();
	int i=1;
	while(itc != ls.camiones.end()){
		list<producto>::iterator itp = itc->productos.begin();
		cout << "C" << k <<": "; 
		while(itp != itc->productos.end()){
			cout << *itp <<" ";
			itp++;
		}
		itc++;
		cout << endl;
		i++;	
	}
	cout << endl << endl;
	k++;
}


void llenar_camiones(resultado& res_parcial, list<producto>& Q, coef mz[4][4] )
{
	if (Q.empty()){
		res_g = res_parcial;
		mostrar_camiones(res_g);
	}else{
		list<producto>::iterator it = Q.begin();
		while(it != Q.end()){
			if(sigue_siendo_sol(res_parcial,*it)){
				resultado res_parcial_copy = resultado();
				if(res_parcial.cant == 0){//tengo que preguntar si la lista camiones es vacia, pero me da segmentation fault
					res_parcial_copy.camiones = list<camion>();
				}else res_parcial_copy = res_parcial;
				list<producto> Q_copy = Q;
				agregar_producto(res_parcial_copy,*it,mz);
				list<producto>::iterator itp = find(Q_copy.begin(),Q_copy.end(),*it);
				Q_copy.erase(itp);
				llenar_camiones(res_parcial_copy,Q_copy, mz);
			}
				it++;
		}	
	}
}

int main(){


	list<producto> q;
	q.push_back(1);	
	q.push_back(2);	
	q.push_back(3);	
	q.push_back(4);	
	q.push_back(5);
	
	resultado vacia1 = resultado();
	coef m1[4][4];
	m1[0][0]=8;
	m1[0][1]=1;
	m1[0][2]=1;
	m1[0][3]=0;
	m1[1][0]=3;
	m1[1][1]=5;
	m1[1][2]=3;
	m1[2][0]=4;
	m1[2][1]=0;
	m1[3][0]=2;

	llenar_camiones(vacia1,q,m1);
	mostrar_camiones(res_g);

	return 0;

}



