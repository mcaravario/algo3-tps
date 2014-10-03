#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <sstream>

using namespace std;

int siguiente_salto(int actual,const vector<int>& puente, int c, int tam);

bool saltar_puente(const vector<int>& puente, int c, int& saltos, vector<int>& tablones_recorridos, int n);
  
int puente_size(string linea);

int capacidad_salto(string linea);

void crear_puente(vector<int>& puente, string linea, int tam);
