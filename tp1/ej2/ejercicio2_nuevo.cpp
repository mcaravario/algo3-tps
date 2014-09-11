#include "ejercicio2_nuevo.h"

/* Esta función agrega al dicc de  intervalos ocupados (techos) un nuevo intervalo. */
void mergear_ed(set<intervalo>& is, intervalo nuevo)
{
/* Primero verifico que el intervalo no esté */
	if (is.find(nuevo) == is.end()){
		/* Al no estar, chekeo si debo mergear con su anterior, y/o su siguiente. */
		set<intervalo>::iterator menor =	is.lower_bound(nuevo);
		set<intervalo>::iterator mayor =	is.upper_bound(nuevo);
		
		
		if (menor == is.end()){		
			/* nuevo es mayor a todos los elementos, debo checkear que no se solape con el ultimo. */
			menor--;			
			if (menor->b >= nuevo.a){
				/* Los junto */
				nuevo.a = menor->a;
				is.erase(menor);
				is.insert(nuevo);				
			} else { is.insert(nuevo); }			

		} else {
			/* menor es el primer elemento más grande a nuevo  */
			if (menor == is.begin()){
				/* nuevo va adelante de todo, solo se puede solapar con el segundo */
			}
		}
	}
}	

void generar_estructuras(int cant_ed, dicc_y& por_altura, dicc_x1& por_ejex1, dicc_x2 por_ejex2)
{
	int izq;
	int alt;
	int der;
	int i;

	for (i = 0; i < cant_ed; i++){
	
		cin >> izq;
		cin >> alt;
		cin >> der;
	
		por_ejex1.insert(intervalo(izq, der));
		por_ejex2.insert(intervalo(der, izq));
		por_altura.insert(edificio(izq, alt, der));
	}
}

/* Esta función evalua si el vertice nuevo está contenido en algún intervalo formado por
 * algún edificio del diccionario por_ejex (el cual contiene a todos los edificios.)
 * OBS: Notar que si se invocó a esta función, entonces el dicc no está vacío.
 * */
void agregar_si_no_contenido(dicc_x1 por_ejex1, dicc_x2 por_ejex2, set<vertice> res, intervalo ed)
{
	dicc_x1::iterator actual_1 = por_ejex1.find(ed);
	dicc_x2::iterator actual_2 = por_ejex2.find(ed);
	
	actual_1++;
	if (actual_2 != por_ejex2.begin()){
		actual_2--;
		if (actual_1 == por_ejex1.end() || (actual_1->a > ed.b && actual_2->b < ed.a)) res.insert(vertice(ed.a,0));
	}	else {
					

}


void generar_horizonte(dicc_y& por_altura, set<vertice>& res, dicc_x1& por_ejex1, dicc_x2& por_ejex2)
{
		
	/* Voy a ir procesando los edificios del dicc_y, de forma tal que voy tomando siempre los de mayor altura.
	 * Los proceso, actualizando techos, y res. Uso dicc_x para saber si puedo o no agregar el segundo vértice,
	 * dado que si existe un edifcio tal que dicho vértice esta contendido en un intervalo definido por otro 
	 * edifico, entonces no puedo agregar el segundo vertice.
	 **/
	
	/*  Esta estructura la voy a usar para saber que intervalos ya tengo escritos.
	 *  Como escribo primero los de mayor altura, se que cuando voy a escribir un elemento i, los i-1
	 *  anteriores eran de mayor o igual altura, con lo cual si me fijo en 'techos' los intervalos que hay
	 *  puedo saber cuales me hacen "sombra", es decir, con cuales de los [0..i-1] se solapa el i .  */			
	set<intervalo> techos;

	dicc_y::iterator it = por_altura.begin();

	while (it != por_altura.end()){

		if (!se_solapa(techos,*it)){
			/* Al no haber edificio que me haga sombra, simplemente agrego v1, y me fijo si puedo agregar v2  */			
			res.insert(vertice(it->x1, it->y));
			if (!vertice_contenido(por_ejex1, *it)) res.insert(vertice(it->x2, 0));			
		} else {

			/*  El techo me hace sombra (en alguna parte, o en todo).
			 *  Debo acomodar mi edificio hasta que no me hagan sombra.
			 *  Para hacer esto, necesito buscar a dos intervalos de 'techos'.
			 *  Por un lado, necesito el primero mayor, y por el otro,
			 *  necesito al ultimo menor (ya que 'techos' es una estructura
			 *  ordenada).
			 **/	
			intervalo actual = intervalo(it->x1, it->x2);
			set<intervalo>::iterator lower = techos.lower_bound(intervalo(it->x1, it->x2));
			/* Veo si lower es end, en cuyo caso, mi techo va último. */
			if (lower == techos.end()){
				/* Debo chequear, al momento de agregar el v1, si el edificio anterior tiene la misma altura que el actual.
				 * Pues si la tienen, no hay cambio de nivel, con lo cual v1 no debe formar parte de la solución.
				 * Entonces, debo ver que si tienen la misma altura, qué sucede con el x1 de actual, en relación con el 
				 * x2 del anterior. Si x1(actual) > x2(anterior) , etonces debo agregar el x1 */
				lower--;
				if (actual.a <= lower->b) actual.a = lower->b;
				if (actual.a < actual.b) agregar_si_no_contenido(por_ejex1, por_ejex2, res, *it);	
		}

	}

	
}				

// TODO
inline void mostrar_vertice(vertice v){
	cout << v.x << " " << v.y << ")"; 
}

void mostrar_res(set<vertice> res)
{
	set<vertice>::iterator it = res.begin();
	while (it != res.end()){
		mostrar_vertice(*it);
	}
}


int main(int argc, char** argv){
	
		int cant_ed;
		bool parar = false;
		while (!parar){
			cin >> cant_ed;
			if (cant_ed == 0){
				parar = true;
			} else {
				dicc_y por_altura;
				dicc_x1 por_ejex1;
				dicc_x2 por_ejex2;
				set<vertice> res;
				generar_estructuras(cant_ed, por_altura, por_ejex1, por_ejex2);
				//generar_horizonte(por_altura, res, por_ejex);
				//mostrar_res(res);
			}
	}
	return 0;
}



