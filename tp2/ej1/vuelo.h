#include <queue>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

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

struct ciudad{
  priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> vuelos;
  string nombre;
  ciudad();
};

struct mundo{
  list<ciudad> ciudades;
  mundo();
};

struct resultado{
  list<int> itinerario; 
  int cant;
  int fin;
  resultado();
};

vuelo::vuelo(){
  salida = 0;
  llegada = 0;
  origen = "ciudad vacia";
  destino = "ciudad vacia";
  id = 1000000 ;	
}

mundo::mundo(){
  ciudades = list<ciudad>();	
}

ciudad::ciudad(){
  vuelos = priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada>();
  nombre = "ciudad vacia";
}

resultado::resultado(){
  itinerario = list<int>();
  cant = 0;
  fin = 0;
}

vuelo proximo_vuelo(ciudad& destino, int& hora, vector<bool>& vuelos)
{
  vuelo candidato;
  priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> disponibles = destino.vuelos;
  while(!disponibles.empty()){
    candidato = disponibles.top();
    disponibles.pop();
    if (hora <= 0 ) hora = 2;
    if(candidato.llegada <= (hora-2) && vuelos[candidato.id]){
      vuelos[candidato.id] = false;
      return candidato;
    }
  }
return vuelo();
}

ciudad buscar_ciudad(mundo& m, string& target)
{
  list<ciudad>::iterator first = m.ciudades.begin(); 
  list<ciudad>::iterator last = m.ciudades.end();
  while (first != last){
    if (first->nombre == target) return *first;
      ++first;
    }
  return *last;
}

resultado armar_ruta(ciudad& destino, ciudad& origen, vector<bool>& vuelos, mundo& m, int& hora_max)
{
  ciudad ciudad_anterior = ciudad();
  int hora_anterior = 0; 
  ciudad ciudad_a_revisar = destino;
  resultado result;
  int hora = hora_max +2;
    while(ciudad_a_revisar.nombre != origen.nombre){
      vuelo candidato = proximo_vuelo(ciudad_a_revisar, hora, vuelos);
      if(candidato.origen == "ciudad vacia"){
        if(result.itinerario.empty()){
          break;
        }else{
 	  ciudad_a_revisar = ciudad_anterior;
	  hora = hora_anterior;
  	  result.itinerario.pop_front();
	  result.cant--;
	  continue;
        }
      }else{
	result.itinerario.push_front(candidato.id);
	result.cant++; 
	if(ciudad_a_revisar.nombre == destino.nombre) result.fin = candidato.llegada;
	ciudad_anterior = ciudad_a_revisar;
	hora_anterior = hora;
	hora = candidato.salida;
	ciudad_a_revisar = buscar_ciudad(m, candidato.origen); 
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
