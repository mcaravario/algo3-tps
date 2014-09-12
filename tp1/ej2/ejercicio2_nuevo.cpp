#include "ejercicio2_nuevo.h"
void mostrar_techos(set<intervalo>);
void mostrar_y(map<int, int> res);
void mostrar_res(set<vertice>);
int max(int a, int b){
  return (a >= b) ? a : b;
}


void mostrar_edificios(set<edificio,cmp_y> res)
{
	auto it = res.begin();
	auto fin = res.end();
  fin--;
	while (it != fin){
		cout << "( " << it->x1 << ", " << it->y << ", " << it ->x2 <<")  ";
		it++;
	}
	cout << "( " << it->x1 << ", " << it->y << ", " << it ->x2 <<")  ";
}


/* Esta funcion mergea (si es posible) los edificios e inserta el mergeado.*/
void merge(dicc_y& por_altura, dicc_y::iterator it, edificio ed)
{
  if (ed.x1 <= it->x2) {
    ed.x1 = it->x1;
    ed.x2 = max(it->x2, ed.x2);
    por_altura.erase(it);
  } else if (ed.x2 >= it->x1) {
    ed.x2 = max(ed.x2,it->x2);
    por_altura.erase(it);
  }

  por_altura.insert(ed);
}

void merge2(dicc_y& por_altura, dicc_y::iterator menor, dicc_y::iterator
mayor, edificio ed)
{
  /* Los 3 se relacionan */
  if (menor->x2 >= ed.x1 && ed.x2 >= mayor->x1){
   ed.x1 = menor->x1;
   ed.x2 = max(mayor->x2, ed.x2);
   por_altura.erase(menor);
   por_altura.erase(mayor);
   por_altura.insert(ed);
   /* Menor se relaciona con ed*/
  } else if (menor->x2 >= ed.x1){
    merge(por_altura, menor, ed);
    /* Mayor se relaciona con ed */
  } else if (ed.x2 >= mayor->x1) {
    merge(por_altura, mayor, ed);
    /* No se relaciona con nadie*/
  } else {
    por_altura.insert(ed);
  }
}


void mostrar_edificio(edificio it){
		cout << "( " << it.x1 << ", " << it.y << ", " << it.x2 <<")  ";
}

void generar_estructuras(int cant_ed, dicc_y& por_altura)
{
	int izq;
	int alt;
	int der;
	int i;

	for (i = 0; i < cant_ed; i++){
	
		cin >> izq;
		cin >> alt;
		cin >> der;

    edificio a_insertar = (edificio(izq, alt, der));
    /* Testing  */
    cout << "El edificio es: ";
    mostrar_edificio(a_insertar);
    cout << endl;

    if(por_altura.empty()){
      por_altura.insert(a_insertar);  
    } else {
		  auto lower = por_altura.lower_bound(a_insertar);
      if (lower == por_altura.begin()) {
        if (lower->y == a_insertar.y) merge(por_altura, lower, a_insertar);
      } else if (lower == por_altura.end()) {
        lower--;
        if (lower->y == a_insertar.y) merge(por_altura, lower,
        a_insertar);

      } else {
        auto upper = lower;
        lower--;
        if (lower->y == a_insertar.y && upper->y == a_insertar.y) {
          merge2(por_altura, lower, upper, a_insertar);
        } else if (lower->y == a_insertar.y) {
          merge(por_altura, lower, a_insertar);
        } else {
          merge(por_altura, upper, a_insertar);
        }
	   }
   }
   cout << "Este es la nueva lista de edificios: ";
   mostrar_edificios(por_altura);
   cout << endl;
  }
}

/* techo_y tiene que mantener dada una altura, el intervalo que finalize 'mas adelante'.*/
inline void actualizar_techos_y(map<int, int>& ts, intervalo& nv, int alt){
	if (ts.find(alt) == ts.end() || ts[alt] < nv.b) ts[alt] = nv.b;
}

/* Dado un edificio devuelve true si se solapa con un edificio de su misma altura . */
bool misma_altura_y_solapa(map<int, int>& ts, edificio ed){
	return (ts.find(ed.y) == ts.end()) ? false : !(ts[ed.y] < ed.x1);
}


	
/* Voy a ir procesando los edificios del dicc_y, de forma tal que voy tomando siempre los de mayor altura.
 * Los proceso, actualizando techos, y res.
**/
	
/*  La estructura techos_x la voy a usar para saber que intervalos ya tengo escritos.
*  Como escribo primero los de mayor altura, se que cuando voy a escribir un elemento i, los i-1
*  anteriores eran de mayor o igual altura, con lo cual si me fijo en 'techos' los intervalos que hay
*  puedo saber cuales me hacen "sombra", es decir, con cuales de los [0..i-1] se solapa el i .
*	La estructura techos_y la voy a usar para determinar si efectivamente al agregar el edificio sobre
*	el que itero se produce un cambio de nivel. Voy a guardar aquí el último edificio agregado
*	(por cada algura) para luego chequear si el edificio que estoy evaluando se solapa con dicho elemento.
*	(Notar que los edificios de dicc_y se ordenan por y, luego
*	 por x1, y luego por x2; de manera tal que el subconjunto de edificios de una misma altura se agrega
*	 de forma ordenada creciente por x1).
*
* Debo chequear, al momento de agregar el v1, si el edificio anterior tiene la misma altura que el actual.
* Pues si la tienen, no hay cambio de nivel, con lo cual v1 no debe formar parte de la solución.
* Entonces, debo ver que si tienen la misma altura, qué sucede con el x1 de actual, en relación con el 
* x2 del anterior. Si x1(actual) > x2(anterior) , etonces debo agregar el x1.
*
* Si lower devuelve end, entonces no hay elto mas grande que actual, eso no significa que no se solape
* con el último elto.
* El techo me hace sombra (en alguna parte, o en todo).
*  Debo acomodar mi edificio hasta que no me hagan sombra.
*  Para hacer esto, necesito buscar a dos intervalos de 'techos_x'.
*  Por un lado, necesito el primero mayor, y por el otro,
*  necesito al ultimo menor (ya que 'techos' es una estructura
*  ordenada).
**/	

void generar_horizonte(dicc_y& por_altura, set<vertice>& res)
{
	set<intervalo> techos_x;
	map<int, int> techos_y;
	dicc_y::iterator it = por_altura.begin();

	while (it != por_altura.end()){
	
		intervalo actual = intervalo(it->x1, it->x2);
		auto lower = techos_x.lower_bound(intervalo(it->x1, it->x2));
		/* Si hay alguien de la misma altura y nos solapamos, o si ya hay un intervalo en techos_x
		 * igual al que yo genero, no agrego nada a res. Solo actualizo los techos. */
		if (misma_altura_y_solapa(techos_y, *it) || (lower->a == it->x1 && lower->b == it->x2))	{
			techos_x.insert(actual);
		} else {		
				if (techos_x.empty()) {
					res.insert(vertice(it->x1, it->y));
					techos_x.insert(actual);
				} else {
					/* Veo si lower es end, en cuyo caso, mi techo va último. */
					if (lower == techos_x.end()){
						lower--;
						if (lower->b < actual.b) res.insert(vertice(lower->b, it->y));
						/* Agrando el intervalo que se superponía con actual, de forma que termina donde termina actual. */
						techos_x.insert(intervalo(lower->a, actual.b));
						techos_x.erase(lower);
					} else if (lower == techos_x.begin()) {
						if (actual.a < lower->a) res.insert(vertice(actual.a, it->y));
							techos_x.insert(actual);
						} else {
							auto menor = lower;
							menor--;
							if (actual.a < menor->b) actual.a = menor->b;
							if (actual.a < actual.b && lower->a > menor->b) res.insert(vertice(actual.a,it->y));
							techos_x.insert(actual);
						}
				}				
		}
		actualizar_techos_y(techos_y, actual, it->y);
		it++;
	}

	auto is = techos_x.begin();
	auto fin = techos_x.end();
	fin--;

	mostrar_res(res);
	cout << endl;
	//mostrar_techos(techos_x);
	//mostrar_y(techos_y);	

	while (is != fin){
	auto	sig = is;
		sig++;
		if (is->b < sig->a) res.insert(vertice(is->b,0));
		is++;	
	}
	res.insert(vertice(is->b,0));
}

void mostrar_y(map<int, int> res)
{
	cout << endl;
	auto it = res.begin();
	auto fin = res.end();
  fin--;
	while (it != fin){
		cout << it->first << ": " <<  it->second << "  ";
		it++;
	}
	
		cout << it->first << ": " <<  it->second << endl;
}

void mostrar_techos(set<intervalo> res)
{
	cout << endl;
	auto it = res.begin();
	auto fin = res.end();
  fin--;
	while (it != fin){
		cout << it->a << " " << it->b << " ";
		it++;
	}
	cout << it->a << " " << it->b << endl;
}

void mostrar_res(set<vertice> res)
{
	auto it = res.begin();
	auto fin = res.end();
  fin--;
	while (it != fin){
		cout << it->x << " " << it->y << " ";
		it++;
	}
	cout << it->x << " " << it->y;
}



int main(){
	
		int cant_ed;
		bool parar = false;
		while (!parar){
			cin >> cant_ed;
			if (cant_ed == 0){
				parar = true;
			} else {
				dicc_y por_altura;
				set<vertice> res;
				generar_estructuras(cant_ed, por_altura);
//				generar_horizonte(por_altura, res);
//				mostrar_res(res);
        mostrar_edificios(por_altura);
			}
	}
	return 0;
}



