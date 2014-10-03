#include "ejercicio2.h"



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
				generar_edificios_ordenados(cant_ed, por_altura);
				generar_horizonte(por_altura, res);
				mostrar_res(res);
			}
	}
	return 0;
}


int max(int a, int b){
  return (a >= b) ? a : b;
}

int min(int a, int b){
	return (a <= b) ? a : b;
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

/* Llena el set pasado como parámetro (viene vacío) con los edificios que
 * va procesando desde la entrada estándar. Los ordena decrecientemente
 * por altura, luego por x1.
 **/
void generar_edificios_ordenados(int cant_ed, dicc_y& por_altura)
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


/* PC: No hay edificios de misma altura solapadas */
void generar_horizonte(dicc_y& por_altura, set<vertice>& res)
{
	set<techo> techos;
	set<int> candidatos;
	dicc_y::iterator it = por_altura.begin();

	while (it != por_altura.end()){

		/* Si no hay techo que contenga al x de mi vertice, lo agrego. */			
		if (!contenido(techos, it->x1)) res.insert(vertice(it->x1, it->y));

		/* Este while agrega todos los posibles v2 que vienen de pasadas iteraciones 
		 * si dichos v2 (solo está el x en realidad) caen en el techo de actual
		 * Buscar con x2-1 me asegura que no procesaré los vertices de x = x2
		 **/
		auto arriba = candidatos.upper_bound(it->x2-1);
		auto abajo = candidatos.lower_bound(it->x1);

		while (abajo != arriba){
			res.insert(vertice(*abajo,it->y));
			candidatos.erase(abajo);
			abajo++;
		}
		
		/* Si el x2 no está contenido por algún techo, lo agrego como posible res. */
		if (!contenido(techos, it->x2)) candidatos.insert(it->x2);

		/* Agrego el techo que genera el edificio actual a techos. */
		insertar_y_mergear(techos, techo(it->x1, it->x2));

		it++;
	}

	/* Una vez revisado todos los edificios, agrego los v2 que chocan contra el piso (y = 0)*/
	auto is = candidatos.begin();
	while (is != candidatos.end()) {
		res.insert(vertice(*is,0));
		is++;
	}

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

// Devuelve true si n está contenido en algun techo.
bool contenido(set<techo>& is, int n){
	
	/* Para poder hacer la busqueda se hace la pequeña trampa de crear
	 * el techo (n,n) y buscarlo sabiendo que no existe. Pues nunca
	 * puede estar el elemento (n,n) ya que no es un tehco bien formado.
	**/
	
	auto lower = is.lower_bound(techo(n,n));
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


/* Esta función inserta un techo de forma ordena y mergea si se solapa.*/
void insertar_y_mergear(set<techo>& is, techo i){

	if (is.empty()){
		is.insert(i);
	} else if (is.find(i) == is.end()){
		auto lower = is.lower_bound(i);
		if (lower == is.end()){
			lower--;
			if (i.a <= lower->b && i.b > lower->b){
				techo fusion = techo(lower->a,i.b);
				is.erase(lower);
				is.insert(fusion);	
			} else {
				is.insert(i);
			}
		} else if (lower == is.begin()){
				set<techo>::iterator desde, hasta;
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
					is.insert(techo(a,b));
				} else {
					is.insert(i);
				}
		}	else {
			/* Esta en el medio.*/
			/* Verifico si mergeo con alguien, y si es asi desde donde. */
				int a = i.a;
				int b = i.b;
				set<techo>::iterator desde, hasta;
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
					is.insert(techo(a,b));
				} else {
					is.insert(i);
				}
		}
	}
}



