#include "vuelo.h"

int main(int argc,char* argv[])
{
  string origen;
  string destino;
  mundo m;
  int cantVuelos = 0;
  int i;
  string linea;
  vector<vuelo> vectorVuelos;
  cin >> origen;
  cin >> destino;
  cin >> cantVuelos;
  vectorVuelos.resize(cantVuelos+1);
  vectorVuelos[0] = vuelo();
  for(i = 0; i < cantVuelos; i++){ 
    string origenV;
    string destinoV;
    int ini;
    int fin;
    cin >> origenV;
    cin >> destinoV;
    cin >> ini;
    cin >> fin;
    vuelo load;
    load.origen = origenV;
    load.destino = destinoV;
    load.salida = ini;
    load.llegada = fin;
    load.id = i+1;
    if (m.count(destinoV) == 0){
      cola_vuelos vuelosLoad; 
      vuelosLoad.push(load);
      m.insert(pair<string,cola_vuelos>(destinoV, vuelosLoad));
    }else{
      m.find(destinoV)->second.push(load);
    }
    if (m.count(origenV) == 0) m.insert(pair<string,cola_vuelos>(origenV, cola_vuelos()));
    vectorVuelos[i+1] = load;
  }
  resultado res = armar_ruta(destino, origen, vectorVuelos, m);
  if(res.cant != 0){
     mostrar_res(res);
  }else{
    cout << "no";
  }
  return 0;
}
