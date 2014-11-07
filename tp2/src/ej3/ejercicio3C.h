#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct enlace{
	pair<int,int> arista;
	enlace(int, int);
};

struct info{
		int costo;
		pair<int,int>arista;
		bool usado;
		bool en_anillo;
		info(int, int, int);
};

struct result{
	int cant_anillo;
	int cant_red;
	list<enlace> anillo;
	list<enlace> red;
	int c;
	result();
};

enlace::enlace(int a, int b){
	arista.first = a;
	arista.second = b;
}

info::info(int a, int b, int c){
	costo = c;
	arista.first = a;
	arista.second = b;
	usado = false;
	en_anillo = false;
}

result::result(){
	cant_anillo = 0;
	cant_red = 0;
	anillo = list<enlace>();
	red = list<enlace>();
	c = 0;
}
#define matriz_adya vector< vector<info> >

int costo_min(vector<int>& costos, vector<bool>& agregado, int maximo, int cantidad)
{
	int min = maximo+1;
	int min_index;
 
	for (int v = 0; v < cantidad; v++)
	{
		if (!agregado[v] && costos[v] < min)
		{
			min = costos[v]; 
			min_index = v;
		}
	}
	return min_index;
}

bool hay_solucion(vector<int>& revisar, int maximo)
{
	vector<int>::iterator it = std::find(revisar.begin(), revisar.end(), maximo+1);
	return (it==revisar.end());
}


enlace menor_no_utilizado(matriz_adya& adyacencias, vector<int>& padre_de, int cant_nodos, int maximo)
{
	int a = 0;
	int b = 0;
	int mi = maximo+1; 
	enlace ari = enlace(-1,-1);

	for(int i = 0; i<cant_nodos; i++){
		for(int j= 0; j <cant_nodos; j++){
			if( (adyacencias[i][j].usado != true) && (mi > adyacencias[i][j].costo) && (padre_de[adyacencias[i][j].arista.first] != adyacencias[i][j].arista.second) &&
				  (padre_de[adyacencias[i][j].arista.second] != adyacencias[i][j].arista.first) && (adyacencias[i][j].costo != -1)){
				mi = adyacencias[i][j].costo;
				ari.arista.first = adyacencias[i][j].arista.first;
				ari.arista.second = adyacencias[i][j].arista.second;
				a = i;
				b = j;
			}
		}
	}
	adyacencias[a][b].usado = true;

	return ari;
}

list<int> armar_medio(int comienzo, vector<int>& padre)
{
	list<int> res;
	while(comienzo != -1){
		res.push_back(comienzo);
		comienzo = padre[comienzo];
	}
	return res;
}

void armar_anilloAux(list<enlace>& res, list<int>& revisar, int enlace_union, matriz_adya& adyacencias)
{
	list<int>::iterator it1 = revisar.begin();
	while(*it1 != enlace_union){
		int f = *it1;
		it1++;
		int s = *it1; 
		res.push_back(enlace(s,f));
		adyacencias[s][f].en_anillo = true;
		adyacencias[f][s].en_anillo = true;
	}
}

void cerrar_anillo(list<enlace>& res, list<int>& uno, list<int>& dos, matriz_adya& adyacencias){
	list<int>::iterator it_1 = uno.begin();
	list<int>::iterator it_2 = dos.begin();
	res.push_back(enlace(*it_1,*it_2));
	adyacencias[*it_1][*it_2].en_anillo = true;
	adyacencias[*it_2][*it_1].en_anillo = true;
}

list<enlace> armar_anillo(list<int>& uno, list<int>& dos, matriz_adya& adyacencias)
{
	list<enlace> res;
	list<int>::iterator it1 = uno.begin();
	list<int>::iterator enlace_union = uno.begin();
	while(it1 != uno.end()){
		list<int>::iterator it2 = find(dos.begin(), dos.end(), *it1);
		if (!(it2 == dos.end())){
			enlace_union = it2;
			break;
		}
		it1++;
	}
	armar_anilloAux(res, uno, *enlace_union, adyacencias);
	armar_anilloAux(res, dos, *enlace_union, adyacencias);
	cerrar_anillo(res, uno, dos, adyacencias);
	return res;
}

result armar_resultado(vector<int>& padre_de, int cantidad, matriz_adya& adyacencias, int maximo)//, list<enlace>& usados)
{
	result res = result();	
	enlace comienzo_anillo = menor_no_utilizado(adyacencias, padre_de, cantidad,maximo);
	if(comienzo_anillo.arista.first == -1 && comienzo_anillo.arista.second == -1) return res;
	list<int> medio1= armar_medio(comienzo_anillo.arista.first, padre_de);
	list<int> medio2= armar_medio(comienzo_anillo.arista.second, padre_de);
	res.anillo = armar_anillo(medio1, medio2, adyacencias);
	res.cant_anillo = res.anillo.size();
	
	for(int i = 0; i < cantidad; i++){
		for(int j = 0; j < cantidad; j++){
			if(adyacencias[i][j].usado  && adyacencias[i][j].costo != -1 ){
				res.c = res.c + adyacencias[i][j].costo;
			}
			 if (adyacencias[i][j].usado && !adyacencias[i][j].en_anillo  && adyacencias[i][j].costo != -1){
				res.red.push_back(enlace(adyacencias[i][j].arista.first, adyacencias[i][j].arista.second));
				res.cant_red ++;
			}
		}
	}
	//res.c = res.c + adyacencias[comienzo_anillo.arista.first][comienzo_anillo.arista.second].costo;
	

	return res;
}

result armar_AGM(matriz_adya& adyacencias, int maximo, int cantidad)
{
	vector<int> padre_de(cantidad , -1);
	vector<int> cost(cantidad , maximo +1);
	vector<bool> agregado(cantidad , false);
 
	int u = 0;
	for (int count = 0; count < cantidad-1 ; count++)
	{ 	
		agregado[u] = true;

		for (int v = 0; v < cantidad; v++){
			if (adyacencias[u][v].costo != -1 && !agregado[v] && adyacencias[u][v].costo < cost[v])
			{
				padre_de[v]  = u;
				cost[v] = adyacencias[u][v].costo;
			}
		}

		u = costo_min(cost, agregado, maximo, cantidad);
		adyacencias[u][padre_de[u]].usado = true;
		//adyacencias[padre_de[u]][u].usado = true;
		
	}
	//El costo del primer elemento siempre va a quedar en maximo+1, para que funcione bien hay_solucion lo harcodeamos
	cost[0]=0;
	if(hay_solucion(cost, maximo)){
		return armar_resultado(padre_de, cantidad, adyacencias, maximo);
	}else{
		return result();
	}
}

void mostrar_result(result& res)
{
	if(res.cant_anillo == 0){
		cout << "no" << endl;
	}else{
		cout << res.c << " " << res.cant_anillo << " " << res.cant_red << endl;
		list<enlace>::iterator it;
		for(it = res.anillo.begin(); it != res.anillo.end(); it++){
			cout << it->arista.first+1 << " " << it->arista.second+1 << endl;
		}
		for(it = res.red.begin(); it != res.red.end(); it++){
			cout << it->arista.first+1 << " " << it->arista.second+1 << endl;
		}
	}
}/*

void mostrar_matriz_adya(matriz_adya& matriz){
	for (int i=0; i< matriz.size(); i++){
		for(int j = 0; j< matriz.size(); j++){
			cout << matriz[i][j] << " " ;
		}
		cout << endl;
	}
}
*/
