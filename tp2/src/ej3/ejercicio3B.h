#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

#define costo int
pair<int,int>
#define matriz_adya vector< vector<costo> >

using namespace std;

struct result{
	int cant_anillo;
	int cant_red;
	list<enlace> anillo;
	list<enlace> red;
	costo c;
	result();
};

struct enlace{
	pair<int,int> arista;
	bool usado;
	enlaces()
};

result::result(){
	cant_anillo = 0;
	cant_red = 0;
	anillo = list<enlace>();
	red = list<enlace>();
	c = 0;
}

enlaces::enlaces(int a, int b){
	arista.first = a;
	arista.second = b;
	usado = false;
}

int costo_min(vector<costo>& costos, vector<bool>& agregado, int maximo, int cantidad)
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

bool hay_solucion(vector<costo>& revisar, int maximo)
{
	vector<costo>::iterator it = std::find(revisar.begin(), revisar.end(), maximo+1);
	return (it==revisar.end());
}

enlace menor_no_utilizado(list<enlace>& disponibles, matriz_adya& adyacencias, vector<int>& padre_de)
{
	list<enlace>::iterator it = disponibles.begin();
	list<enlace>::iterator min = disponibles.begin();
	
	//Avanzo a un enlae no usado.
	while(it->usado){
		it++;
	}
	
	//Busco de los enlaces disponibles cual tiene menor coto y lo guardo en Min
	while(it != disponibles.end()){
		int candidato = adyacencias[it->arista.first][it->arista.second]; 
		if( (!(it->usado)) && candidato != -1 && candidato < adyacencias[min->arista.first][min->arista.second] && (padre_de[it->arista.first] != it->arista.second) &&( padre_de[it->arista.second] != it->arista.first) ) min = it;
		it++;
	}
	
	min->usado = true;
	return *min;
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

void armar_anilloAux(list<enlace>& res, list<int>& revisar, int enlace_union)
{
	list<int>::iterator it1 = revisar.begin();
	while(*it1 != enlace_union){
		int f = *it1;
		it1++;
		int s = *it1; 
		res.push_back(enlace(f,s));
	}
}

void cerrar_anillo(list<enlace>& res, list<int>& uno, list<int>& dos){
	list<int>::iterator it_1 = uno.begin();
	list<int>::iterator it_2 = dos.begin();
	res.push_back(enlace(*it_1,*it_2));
}

list<enlace> armar_anillo(list<int>& uno, list<int>& dos)
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
	armar_anilloAux(res, uno, *enlace_union);
	armar_anilloAux(res, dos, *enlace_union);
	cerrar_anillo(res, uno, dos);
	return res;
}

result armar_resultado(vector<int>& padre_de, int cantidad, matriz_adya& adyacencias, list<enlace>& disponibles)//, list<enlace>& usados)
{
	result res = result();	

	enlace comienzo_anillo = menor_no_utilizado(disponibles,adyacencias, padre_de); //usados
	list<int> medio1= armar_medio(comienzo_anillo.first, padre_de);
	list<int> medio2= armar_medio(comienzo_anillo.second, padre_de);
	res.anillo = armar_anillo(medio1, medio2);
	
	res.cant_anillo = res.anillo.size();
	
	list<enlace>::iterator it_c = disponibles.begin();
	while(it_c!=disponibles.end()){
		if(it_c->usado)	res.c = res.c + adyacencias[it_c->arista.first][it_c->arista.second];
		it_c++;
	}
	res.c = res.c + adyacencias[comienzo_anillo.arista.first][comienzo_anillo.arisa.second];
	//CONSTRUIR RED
	list<enlace>::iterator it_red = disponibles.begin();
	while(it_red != disponibles.end()){
		if (!it_red->usado) res.red.push_back(*it_red);
		it_red++;
		res.cant_red ++;
	}
	return res;
}

result armar_AGM(matriz_adya& adyacencias, int maximo, int cantidad, list<enlace>& disponibles)
{
	vector<int> padre_de(cantidad , -1);
	vector<costo> costos(cantidad , maximo +1);
	vector<bool> agregado(cantidad , false);
	list<enlace> usados;
 
	int u = 0;
	for (int count = 0; count < cantidad-1 ; count++)
	{ 	
		agregado[u] = true;

		for (int v = 0; v < cantidad; v++)
		{
			if (adyacencias[u][v] != -1 && !agregado[v] && adyacencias[u][v] < costos[v])
			{
				padre_de[v]  = u;
				costos[v] = adyacencias[u][v];
			}
		}

		u = costo_min(costos, agregado, maximo, cantidad);
		usados.push_back(enlace(padre_de[u], u));
		list<enlace>::iteradtor it = find(disponibles.begin(), disponibles.end(), enlace(padre_de[u],u));
		it->usado = true; 
		
	}
	
	//El costo del primer elemento siempre va a quedar en maximo+1, para que funcione bien hay_solucion lo harcodeamos
	costos[0]=0;
	if(hay_solucion(costos, maximo)){
		return armar_resultado(padre_de, cantidad, adyacencias, disponibles)//, usados);
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
			cout << it->first+1 << " " << it->second+1 << endl;
		}
		for(it = res.red.begin(); it != res.red.end(); it++){
			cout << it->first+1 << " " << it->second+1 << endl;
		}
	}
}

void mostrar_matriz_adya(matriz_adya& matriz){
	for (int i=0; i< matriz.size(); i++){
		for(int j = 0; j< matriz.size(); j++){
			cout << matriz[i][j] << " " ;
		}
		cout << endl;
	}
}

