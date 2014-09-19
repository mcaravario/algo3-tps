#include "ejercicio2.h"


int max(int a, int b){
  return (a >= b) ? a : b;
}

int min(int a, int b){
	return (a <= b) ? a : b;
}

bool contenido(set<intervalo>& is, int n){
	
	auto lower = is.lower_bound(intervalo(n,n));
	if (is.empty()) return false;
	if (lower == is.end()) {
		lower--;
		return lower->b >= n;
	} else if (lower == is.begin()) {
		return lower->a == n;
	} else {
		auto anterior = lower;
		anterior--;
		return anterior->b >= n || lower->a == n;
	}
}

/* Esta función inserta un intervalo de forma ordena y mergea si se solapa.*/
void insertar(set<intervalo>& is, intervalo i){

	if (is.empty()){
		is.insert(i);
	} else if (is.find(i) == is.end()){
		auto lower = is.lower_bound(i);
		if (lower == is.end()){
			lower--;
			if (i.a <= lower->b && i.b > lower->b){
				intervalo fusion = intervalo(lower->a,i.b);
				is.erase(lower);
				is.insert(fusion);	
			} else {
				is.insert(i);
			}
		} else if (lower == is.begin()){
				set<intervalo>::iterator desde, hasta;
				int a = i.a;
				int b = i.b;
				if (i.b >= lower->a){
					desde = lower;
					auto it = lower;
					while (is.end() != it && it->a <= b){
						b = max(it->b, b);
						it++;
					}
					hasta = it;
					is.erase(desde,hasta);
					is.insert(intervalo(a,b));
				} else {
					is.insert(i);
				}
		}	else {
			/* Esta en el medio.*/
			/* Verifico si mergeo con alguien, y si es asi desde donde. */
				int a = i.a;
				int b = i.b;
				set<intervalo>::iterator desde, hasta;
				desde = is.end();
				auto anterior = lower;
				anterior--;
				if (a <= anterior->b){
					a = anterior->a;
					desde = anterior;
				} else if (b >= lower->a) {
					desde = lower;
				}
				
				if (desde != is.end()) {
					auto it = desde;
					while ( is.end() != it && it->a <= b ) {
						b = max(b,it->b);
						it++;
					}
					hasta = it;
					is.erase(desde,hasta);
					is.insert(intervalo(a,b));
				} else {
					is.insert(i);
				}
		}
	}
}

void mostrar_techos(set<intervalo> res)
{
	cout << endl;
	auto it = res.begin();
	auto fin = res.end();
  fin--;
	while (it != fin){
		cout << "(" << it->a << "," << it->b << ")  ";
		it++;
	}
	cout << "("<< it->a << "," << it->b << ")" << endl;
}




int main(){


		intervalo a = intervalo(2,5);
		intervalo b = intervalo(6,7);
		intervalo c = intervalo(8,9);
		intervalo d = intervalo(10,11);
		intervalo e = intervalo(12,13);
		intervalo f = intervalo(14,17);
		intervalo g = intervalo(3,4);
		intervalo h = intervalo(3,6);
		intervalo i = intervalo(0,1);
		intervalo j = intervalo(3,15);
		set<intervalo> s;
		insertar(s,a);
		mostrar_techos(s);
		insertar(s,b);
		mostrar_techos(s);
		insertar(s,c);
		mostrar_techos(s);
		insertar(s,d);
		mostrar_techos(s);
		insertar(s,e);
		mostrar_techos(s);
		insertar(s,f);
		mostrar_techos(s);
		insertar(s,g);
		mostrar_techos(s);
		insertar(s,h);
		mostrar_techos(s);
		insertar(s,i);
		mostrar_techos(s);
		insertar(s,j);
		mostrar_techos(s);
		
		cout << contenido(s,0) << " " << contenido(s,3) <<  " ";
	  cout << contenido(s,17) << " " << contenido(s,18) << endl; 

	return 0;
}
