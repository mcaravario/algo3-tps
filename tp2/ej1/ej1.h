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
    return lhs.llegada < rhs.llegada;
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

vuelo proximo_vuelo(ciudad destino, int hora, vector<bool>& vuelos)
{
  vuelo candidato;
  priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> disponibles = destino.vuelos;
  while(!disponibles.empty()){
    candidato = disponibles.top();
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
  while (first->nombre != last->nombre){
    if (first->nombre == target) return *first;
      ++first;
    }
  return *last;
}

resultado armar_ruta(ciudad destino, ciudad origen, vector<bool>& vuelos, mundo m)
{
  ciudad ciudad_anterior = ciudad();
  int hora_anterior = 0; 
  ciudad ciudad_a_revisar = destino;
  resultado result;
  int hora = (destino.vuelos.top().salida);
    while(ciudad_a_revisar.nombre != origen.nombre){
      if(proximo_vuelo(ciudad_a_revisar, hora, vuelos).origen == "ciudad vacia"){
        if(result.itinerario.empty()){
          break;
        }else{
 	  ciudad_a_revisar = ciudad_anterior;
	  hora_anterior = hora;
  	  result.itinerario.pop_front();
	  result.cant--;
	  continue;
        }
      }else{
	vuelo siguiente = proximo_vuelo(ciudad_a_revisar, hora, vuelos);
	result.itinerario.push_front(siguiente.id);
	result.cant++; 
	if(ciudad_a_revisar.nombre == destino.nombre) result.fin = siguiente.llegada;
	ciudad_anterior = ciudad_a_revisar;
	ciudad_a_revisar = buscar_ciudad(m, siguiente.origen); 
      }
    }
return result;
}

void mostrar_res(resultado& ls){
  cout << ls.fin << " " << ls.cant;
  list<int>::iterator it = ls.itinerario.begin();
  for(int i = 0; i <= ls.cant; i++){
    cout << " " << *it;
    it++;
  }
  cout << endl;
}
