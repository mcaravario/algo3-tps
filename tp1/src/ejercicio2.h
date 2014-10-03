#include <set>
#include <map>
#include <iostream>
#define dicc_y set<edificio,cmp_y>
using namespace std;


/******* ESTRUCTURAS UTILIZADAS *******/

struct edificio{
	edificio(int a, int b, int c) : x1(a), y(b), x2(c) {}
	bool operator<(edificio) const;
	int x1;
	int y;
	int x2;
};

struct vertice{
	vertice(const int& a, const int& b) : x(a), y(b)  {}
	bool operator<(vertice) const;
	int x;
	int y;			
};

struct techo{
	techo(const techo& i) : a(i.a), b(i.b) {}
	techo(const int& c, const int& d) : a(c), b(d) {}			
	bool operator<(techo) const;
	int a;
	int b;			
};

/* Clase comparadora para ordenar set por y. Para ordenar decrecientemente. (Mas alto al principio) */
struct cmp_y{
	bool operator()(const edificio& a, const edificio& b) const{
		return (a.y > b.y) || (a.y == b.y && a.x1 < b.x1) || (a.y == b.y && a.x1 == b.x1 && a.x2 < b.x2);
	}			
};

/* Clase comparadora para odernar el set por b  (segundo componente de techo) de forma creciente. */
struct cmp_b{
	bool operator()(const techo& u, const techo& v) const{
		return (u.b < v.b) || (u.b == v.b && u.a < v.a);
	}			
};

bool techo::operator<(techo otro) const{
	return (this->a < otro.a) || (this->a == otro.a && this->b < otro.b); 
} 

bool vertice::operator<(vertice otro) const{
	return (this->x < otro.x) || (this->x == otro.x && this->y < otro.y); 
}


/* Sobrecargamos el operador < para ordenar el set por x */
bool edificio::operator<(edificio other) const{
		return ((this->x1 < other.x1) || ((this->x1 == other.x1) && (this->y > other.y)) ||  ((this->x1 == other.x1) && (this->y == other.y) && (this->x2 < other.x2)) );
}

/******* DECLARACION DE FUNCIONES ********/


void merge(dicc_y& por_altura, dicc_y::iterator it, edificio ed);

void merge2(dicc_y& por_altura, dicc_y::iterator menor, dicc_y::iterator mayor, edificio ed);

void generar_edificios_ordenados(int cant_ed, dicc_y& por_altura);

void generar_horizonte(dicc_y& por_altura, set<vertice>& res);

void mostrar_res(set<vertice> res);

void insertar_y_mergear(set<techo>& is, techo i);

void mostrar_techos(set<techo>);

void mostrar_y(map<int, int> res);

void mostrar_res(set<vertice>);

void insertar_y_mergear(set<techo>& is, techo i);

bool contenido(set<techo>& is, int n);


