#include <set>
#include <list>
#include <iterator>   
#include <iostream>    
#include <algorithm>    

using namespace std;

struct vertice{
  vertice(int x, int y);
  int x;
  int y;
	vertice() : x(0), y(0){}	
};


struct edificio{
	edificio(int x1, int y, int x2);
	vertice v1;
	vertice v2;	

	bool operator<(edificio other) const {
		return ((this->v1.x < other.v1.x) || ((this->v1.x == other.v1.x) && (this->v1.y > other.v1.y)) ||  ((this->v1.x == other.v1.x) && (this->v1.y == other.v1.y) && (this->v2.x < other.v2.x)) );
	}

	edificio() : v1(vertice()), v2(vertice()){}		
};


vertice::vertice(int a, int b){
	x = a;
	y = b;	
}


edificio::edificio(int x1, int y, int x2){
	v1 = vertice(x1,y);
	v2 = vertice(x2,y);	
}


bool hay_edificio_relacionado(set<edificio>::iterator it, set<edificio> edificios){

	bool res;	
	if (it == edificios.end()){
		res = false;
	} else {
		set<edificio>::iterator sig = it;
		sig++;
		res = sig->v1.x < it->v2.x;
	}

	return res;
}


void procesar_edificio_simple(set<edificio>::iterator it, set<edificio> edificios, list<vertice> res){
	// Se que mi edificio no se relaciona con otro, pero podria compartir la ultima pared.
	set<edificio>::iterator sig = it;
	sig++;
	res.push_back(it->v1);				//agrego el primer vertice sin modificar
	if (it == edificios.end() || sig->v1.x > it->v2.x){
		vertice insertar = vertice(it->v2.x,0);		//modifico la altura del segundo vertice y la "bajo" al piso y luego la agrego al resultado
		res.push_back(insertar);
	}		
}


bool vertice_contenido(set<edificio>::iterator it, vertice v){	
	return ((v.x < it->v2.x) && (v.x > it->v1.x) && (v.y < it->v1.y));
} 

bool edificio_contenido(set<edificio>::iterator it, set<edificio>::iterator sig){
	return vertice_contenido(it,sig->v1) && vertice_contenido(it,sig->v2);
}


bool rompe_techo(set<edificio>::iterator it,set<edificio>::iterator sig){
	// Por el invariante de la estructura, it->v1.x >= sig->.x, y si los x de ambos
	// edificios coinciden la altura de E1 tiene que superar la de E2
	return (sig->v2.x < it->v2.x) &&  (sig->v2.y > it->v2.y);
}


bool igual_altura(set<edificio>::iterator it1, set<edificio>::iterator it2){
	return (it1->v1.y == it2->v1.y);
}


list<vertice> generar_horizonte(set<edificio>& edificios){

	list<vertice>  res;
	set<edificio>::iterator it = edificios.begin();

	while(it!= edificios.end()){
 			bool a =  !hay_edificio_relacionado(it,edificios);
  		if(a){        //Si no hay edificios relacionados
			procesar_edificio_simple(it,edificios,res);
			it++;
		}else{            //Caso en el que se relacionan 2 edificios o mas
			set<edificio>::iterator sig = it;
			sig++;
			if(edificio_contenido(it,sig)){
				edificios.erase(sig);
	
				if(!hay_edificio_relacionado(it,edificios)){
					procesar_edificio_simple(it,edificios,res);
					it++;
				}
									
			}else{
					
				if(rompe_techo(it,sig)){
					// agrego el primer vertice del primer edificio, ya que se que no hay otro antes
					res.push_back(it->v1);
					// creo el nuevo edificio, el cual se desprende de la interseccion entre el edificio siguiente y el actual.
					edificio a_insertar = edificio(sig->v2.x,it->v1.y,it->v2.x);
					 // inserto ordenadamente el nuevo edificio en mi avl para analizarlo en el futuro.
					edificios.insert(a_insertar);

					it++;
				
				}else{
					
					if(vertice_contenido(it,sig->v1)){
						//creo nuevo edificio con el vertice corrido de lugar
						edificio nuevo_edificio = edificio(it->v2.x,sig->v1.y,sig->v2.x);
						//elimino el siguiente
						edificios.erase(sig);
						//inserto ordenadamente el nuevo edificio que cree
						edificios.insert(nuevo_edificio);
						bool b = !hay_edificio_relacionado(it,edificios);
						if(b){
						
							res.push_back(it->v1);
							it++;
						}
						
					}else{
						if(vertice_contenido(sig,it->v2)){
							res.push_back(it->v1);
							it++;
						}else{
							if(igual_altura(it,sig)){
								// Creo un edificio que es la "union" de ambos, reemplazando a e1 y e2.
								edificio nuevo_ed = edificio(it->v1.x,it->v1.y,sig->v2.x);
								edificios.erase(sig);
								edificios.insert(nuevo_ed);
								it++;
							}	
						}
					}		
				}			
			}					
		}	                                                      
	}
	return res;
}
