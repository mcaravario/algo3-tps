#include "ejercicio2.h"
void mostrar_techos(set<intervalo>);
void mostrar_y(map<int, int> res);
void mostrar_res(set<vertice>);
void mostrar_edificio(edificio);
void insertar(set<intervalo>& is, intervalo i);
bool contenido(set<intervalo>& is, int n);


int max(int a, int b){
  return (a >= b) ? a : b;
}

int min(int a, int b){
	return (a <= b) ? a : b;
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


/* Esta funcion mergea (si es posible) los edificios e inserta el mergeado, si no, inserta ed.*/
void merge(dicc_y& por_altura, dicc_y::iterator it, edificio ed)
{
  if ((ed.x1 <= it->x2 && ed.x1 >= it->x1) || (it->x1 <= ed.x2 && it->x1 >= ed.x1)) {
		ed.x1 = min(it->x1, ed.x1);
		ed.x2 = max(it->x2, ed.x2);
		por_altura.erase(it);
	}
	por_altura.insert(ed);
}

void merge2(dicc_y& por_altura, dicc_y::iterator menor, dicc_y::iterator mayor, edificio ed)
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

    if(por_altura.empty()){
      por_altura.insert(a_insertar);  
    } else {
		  auto lower = por_altura.lower_bound(a_insertar);
      if (lower == por_altura.begin()) {
        if (lower->y == a_insertar.y) {
					merge(por_altura, lower, a_insertar);
				} else {
					por_altura.insert(a_insertar);
				}
      } else if (lower == por_altura.end()) {
        lower--;
        if(lower->y == a_insertar.y) {
						merge(por_altura, lower, a_insertar);
				} else {
						por_altura.insert(a_insertar);
				}
      } else {
        auto upper = lower;
        lower--;
        if (lower->y == a_insertar.y && upper->y == a_insertar.y) {
          merge2(por_altura, lower, upper, a_insertar);
        } else if (lower->y == a_insertar.y) {
          merge(por_altura, lower, a_insertar);
        } else  if (upper->y == a_insertar.y){
          merge(por_altura, upper, a_insertar);
        } else {
					por_altura.insert(a_insertar);
				}
	   }
   }
  }
}



/* Voy a ir procesando los edificios del dicc_y, de forma tal que voy tomando siempre los de mayor altura.
 * Los proceso, actualizando techos, y res.
**/
	
/*  La estructura techos_x la voy a usar para saber que intervalos ya tengo escritos.
*  Como escribo primero los de mayor altura, se que cuando voy a escribir un elemento i, los i-1
*  anteriores eran de mayor o igual altura, con lo cual si me fijo en 'techos' los intervalos que hay
*  puedo saber cuales me hacen "sombra", es decir, con cuales de los [0..i-1] se solapa el i .
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
*
*	En segundos_vertices, pongo todos los segundos vertices de cada edificio en un set (solo la componente y),
*	de forma tal que cuando evaluo un edificio, me fijo si hay un v2 que caiga en mi rango, y si
*	es así, lo agrego.  Ver si cae en mi rango es log(tam_dicc), (a lo sumo n eltos), y lo hago n veces
*	con lo cual, esto cuesta n*log(n).
* Si hay mas de un edificio cuyo intervalo (x1,x2) comprende a un segundo vertice en mi dicc de vertices,
* a mi solo me interesa poner como resultado el (x1,y), donde y es la altura del edificio mas grande.
* Como recorro los edificios decrecientemente en altura, me aseguro que siempre agrego (x1,y). Y una vez
* que lo agrego, lo saco del diccionario.
*
* */	


/* PC: No hay edificios de misma altura solapadas */
void generar_horizonte(dicc_y& por_altura, set<vertice>& res)
{
	set<intervalo, cmp_b> techos_por_b; 
	set<intervalo> techos_por_a;
	set<int> segundos_vertices;
	dicc_y::iterator it = por_altura.begin();

	while (it != por_altura.end()){
		
		/* Este bloque de código evalúa si agregar o no v1*/			
		vertice vr = vertice(it->x1, it->y);
				if (techos_por_a.empty()) {
			res.insert(vr);
		} else {
			/* Creo búsqueda de esta forma para encontrar los dos posibles intervalos que me solapen
			 * el primer intervalo que termina antes de este vr.x, y el último que empieza antes de vr.x
			 * Busco con -1 para que upper me traiga el intervalo que cuyo b = vr.x.
			 **/
			intervalo busqueda_a = intervalo(vr->x, vr->x);
			intervalo busqueda_b = intervalo(vr->x-1, vr->x-1);
			auto lower = techos_por_a.lower_bound(busqueda);
			auto upper = techos_por_b.upper_bound(busqueda);
			
			if (lower == techos_por_a.end()) {
				lower--;
				if (vr.x > lower->b && ( upper == techos_por_b.end() || vr.x <  ))

					
			/* Veo si lower es end, en cuyo caso, mi techo va último. */
			if (lower == techos_por_a.end()){
				lower--;
				if (vr.x >= lower->b) res.insert(vr);
			} else if (lower == techos_por_a.begin() && vr.x < lower->a) {
				res.insert(vr);
			} else {
				/* Caso en el que estoy en el medio. */
				auto menor = lower;
				menor--;
				if (vr.x < lower->a && vr.x >= menor->b) res.insert(vr);
				}
			}
		/* Fin de Agregar o no v1*/
		
		/* Actualizo techos_por_a */
		techos_por_a.insert(intervalo(it->x1, it->x2));

		/* Este while agrega todos los posibles v2 que vienen de pasadas iteraciones 
		 * si dichos v2 (solo está el x en realidad) caen en el intervalo de actual
		 *
		 * Buscar con b-1 me asegura que no procesaré los vertices de x = b
		 **/
		auto arriba = segundos_vertices.upper_bound(actual.b-1);
		auto abajo = segundos_vertices.lower_bound(actual.a);

		while (abajo != arriba){
			res.insert(vertice(*abajo,it->y));
			segundos_vertices.erase(abajo);
			abajo++;
		}
		/* Fin de Agregar o no los v2*/

		/* Ahora debo ver si si agrego o no el v2 como un futuro posible vertice resultado.
		 * Para ver si lo agrego, debo ver si hay un techo que le haga sombra.
		 * Para buscar en el diccionario de intervalos, creo el intervalo (actual.b, actual.b)
		 * y busco el menor y el mayor a este.
	   * OBS: Notar que nunca puede haber un intervalo de la forma (x,x) en cualquiera de los dicc
		 * de techos, ya que los intervalos que están, son de edificios bien formados (a < b).
		 * Entonces nunca voy a encontrar un elemento igual al que utilizo en la busqueda.
		 **/
	
		if (techos_por_b.empty()){
			segundos_vertices.insert(actual.b);
			techos_por_b.insert(actual);
		} else {
			intervalo v2 = intervalo(actual.b, actual.b);
			auto menor_v2 = techos_por_b.lower_bound(v2);
			auto mayor_v2 = techos_por_b.upper_bound(v2);
			if (menor_v2 == techos_por_b.end()) {
				menor_v2--;
				if (menor_v2->b < v2.b) segundos_vertices.insert(v2.b);
			} else if (menor_v2 == techos_por_b.begin()) {
				if (!(menor_v2->a <= v2.b && menor_v2->b >= v2.b)) segundos_vertices.insert(v2.b);
			} else {
				if (!( (menor_v2->a <= v2.b && menor_v2->b >= v2.b) || (mayor_v2->a <= v2.b && mayor_v2->b >= v2.b) )){
					segundos_vertices.insert(v2.b);
				}
			}				
			techos_por_b.insert(actual);
		}
		
		it++;
	} /*Esta llave cierra el while general */

	/* Una vez revisado todos los edificios, agrego los v2 que chocan contra el piso (y = 0)*/
	auto is = segundos_vertices.begin();
	while (is != segundos_vertices.end()) {
		res.insert(vertice(*is,0));
		is++;
	}

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
	cout << it->x << " " << it->y << endl;
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
				generar_horizonte(por_altura, res);
				mostrar_res(res);
			}
	}
	return 0;
}



