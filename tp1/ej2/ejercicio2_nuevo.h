#include <set>
#include <map>
#include <stdlib>
#include <stdio>
#include <iostream>
#define dicc_x set<edificio>
#define dicc_y map<int,dicc_x >
using namespace std;



struct edificio{
	edificio(int a, int b, int c) : x1(a), y(b), x2(c) {}
	int x1;
	int y;
	int x2;
};

struct vertice{
	int x;
	int y;			
};

struct intervalo{
	int x;
	int y;			
};



