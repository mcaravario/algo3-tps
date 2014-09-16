#include "vuelo.h"


int main(){

vuelo v1 = vuelo();
vuelo v2 = vuelo();
vuelo v3 = vuelo();

vuelo v4 = vuelo();
vuelo v5 = vuelo();
vuelo v6 = vuelo();

vuelo v7 = vuelo();
vuelo v8 = vuelo();
vuelo v9 = vuelo();

v1.salida = 22;
v1.llegada= 30;
v1.id = 0;
v1.origen = "living" ;
v1.destino = "trabajo";

v2.salida = 0;
v2.llegada= 8;
v2.id = 1;
v2.origen = "cama";
v2.destino = "trabajo";

v3.salida = 2;
v3.llegada= 35;
v3.id = 2;
v3.origen = "casa";
v3.destino = "trabajo";

v4.salida = 0;
v4.llegada= 15;
v4.id = 3;
v4.origen = "trabajo" ;
v4.destino = "cama";

v5.salida = 0;
v5.llegada= 14;
v5.id = 4;
v5.origen = "living" ;
v5.destino = "cama";

v6.salida = 1;
v6.llegada= 10;
v6.id = 5;
v6.origen = "casa" ;
v6.destino = "cama";

v7.salida = 14;
v7.llegada= 10;
v7.id = 6;
v7.origen = "casa" ;
v7.destino = "living";

v8.salida = 14;
v8.llegada= 10;
v8.id = 7;
v8.origen = "trabajo" ;
v8.destino = "living";

v9.salida = 12;
v9.llegada= 20;
v9.id = 8;
v9.origen = "cama" ;
v9.destino = "living";

priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> vuelosC;

priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> vuelosL;

priority_queue<vuelo, vector<vuelo>, ordenar_menor_por_llegada> vuelosT;

vuelosT.push(v1);
vuelosT.push(v3);
vuelosT.push(v2);

vuelosC.push(v4);
vuelosC.push(v5);
vuelosC.push(v6);

vuelosL.push(v7);
vuelosL.push(v8);
vuelosL.push(v9);

ciudad cama;
cama.vuelos = vuelosC;
cama.nombre = "cama";

ciudad living;
living.vuelos = vuelosL;
living.nombre = "livin";

ciudad trabajo;
trabajo.vuelos = vuelosT;
trabajo.nombre = "trabajo";

ciudad casa;
casa.nombre = "casa";

vector<bool> todo (10, true);

mundo m = mundo();
m.ciudades.push_back(cama);
m.ciudades.push_back(casa);
m.ciudades.push_back(trabajo);
m.ciudades.push_back(living);

int hora = 30;

resultado res = armar_ruta(trabajo, casa, todo, m, hora);

mostrar_res(res);
return 0;
}
