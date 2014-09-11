#include <set>
#include <map>
#include <iostream>
#define dicc_x2 set<intervalo>
#define dicc_x1 set<intervalo>
#define dicc_y set<edificio,cmp_y>
using namespace std;



struct edificio{
	edificio(int a, int b, int c) : x1(a), y(b), x2(c) {}
	bool operator<(edificio) const;
	int x1;
	int y;
	int x2;
};

struct vertice{
	bool operator<(vertice) const;
	int x;
	int y;			
};

struct intervalo{
	intervalo(int c, int d) : a(c), b(d) {}			
	bool operator<(intervalo) const;
	int a;
	int b;			
};


/* Clase comparadora para ordenar set por y. Para ordenar decrecientemente. (Mas alto al principio) */
struct cmp_y{
	bool operator()(const edificio& a, const edificio& b) const{
		return (a.y > b.y) || (a.y == b.y && a.x1 < b.x1) || (a.y == b.y && a.x1 == b.x1 && a.x2 < b.x2);
	}			

};


bool intervalo::operator<(intervalo otro) const{
	return (this->a < otro.a) || (this->a == otro.a && this->b < otro.b); 
} 

bool vertice::operator<(vertice otro) const{
	return (this->x < otro.x) || (this->x == otro.x && this->y < otro.y); 
}


/* Sobrecargamos el operador < para ordenar el set por x */
bool edificio::operator<(edificio other) const{
		return ((this->x1 < other.x1) || ((this->x1 == other.x1) && (this->y > other.y)) ||  ((this->x1 == other.x1) && (this->y == other.y) && (this->x2 < other.x2)) );
}
