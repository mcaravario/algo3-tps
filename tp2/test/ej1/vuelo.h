#include <queue>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <map>

using namespace std; 

struct vuelo{
  int salida;
  int llegada;
  int id;
  string origen;
  string destino;
  vuelo();
};

struct ordenar_menor_por_llegada
{
  bool operator()(const vuelo& lhs, const vuelo& rhs) const
  {
    return lhs.llegada > rhs.llegada;
  }
};

struct resultado{
  list<int> itinerario; 
  int cant;
  int fin;
  resultado();
};

typedef std::priority_queue<vuelo,vector<vuelo>,ordenar_menor_por_llegada> cola_vuelos;
typedef std::map<string, cola_vuelos> mundo;

vuelo::vuelo(){
  salida = 0;
  llegada = 0;
  origen = "ciudad vacia";
  destino = "ciudad vacia";
  id = 0 ;	
}

resultado::resultado(){
  itinerario = list<int>();
  cant = 0;
  fin = 0;
}

vuelo proximo_vuelo(cola_vuelos& disponibles, int& hora, vector<bool>& habilitados)
{
  vuelo candidato;
  while(!(disponibles.empty())){ //O(1)
    if (hora <= 0 ) break;
    candidato = disponibles.top(); //O(1)
    disponibles.pop(); // 2logn
    if(candidato.llegada <= (hora-2) && habilitados[candidato.id]){
      habilitados[candidato.id] = false;
      return candidato;
    }
  }
return vuelo();
}

resultado armar_ruta(string& destino, string& origen, vector<vuelo>& vuelos, mundo& m)
{ 
  mundo::iterator ciudad_a_revisar = m.find(destino);
  resultado result = resultado();
  vector<bool> habilitados(vuelos.size() , true); // n
  int hora = m.find(destino)->second.top().llegada +2; //log n
    while(ciudad_a_revisar->first != origen){ // n * 3 logn
      vuelo candidato = proximo_vuelo(ciudad_a_revisar->second, hora, habilitados); // 2logn
      if(candidato.origen == "ciudad vacia"){
        if(result.itinerario.empty()){
          break;
        }else{
 	  ciudad_a_revisar = m.find(vuelos[result.itinerario.front()].destino); // log n
	  if(ciudad_a_revisar->first == destino){
	    hora = ciudad_a_revisar->second.top().llegada +2;
	  }else{
	    hora = vuelos[result.itinerario.front()].llegada + 2;
	  }
  	  result.itinerario.pop_front(); //O(1)
	  result.cant--;
	  continue;
        }
      }else{
	result.itinerario.push_front(candidato.id);
	result.cant++; 
	if(ciudad_a_revisar->first == destino) result.fin = candidato.llegada;
        hora = candidato.salida;
	ciudad_a_revisar = m.find(candidato.origen); //log n
      }
    }
return result;
}

void mostrar_res(resultado& ls){
  cout << ls.fin << " " << ls.cant;
  list<int>::iterator first = ls.itinerario.begin();
  list<int>::iterator last = ls.itinerario.end();
  while(first != last){
    cout << " " << *first;
    first++;
  }
  cout << endl;
}
