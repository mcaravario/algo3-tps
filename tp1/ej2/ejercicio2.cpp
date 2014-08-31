

#include "ejercicio2.h"
#include <iostream>
#include <set>

using namespace std;


int main(int argc, char** argv){

	int cant_edificios = atoi(argv[1]);
 
	list<vertice> res;

	set<edificio,bool (*comparar_edificios)(edificio,edificio)> edificios;  	
	
	set<edificio>::iterator it = edificios.begin();

  for(int i=0; i<cant_edificios; i+=3){

   	int izq = atoi(argv[i]);

   	int alt = atoi(argv[i+1]);
   
  	int der = atoi(argv[i+2]); 
  
    vertice v1;

    vertice v2;

    v1.x = izq;
    v1.y = alt;
    v2.x = der;
    v2.y = alt;

    edificio ed;

    ed.v1 = v1;
    ed.v2 = v2;

		edificios.insert(it,ed);
 	}	
	// Al salir del for tengo todos los edificios insertados ordenados en el avl

		
	while(it!= edificios.end()){
	
		if(hay_x_edificios_relacionados(it,0,edificios)){  				//Si no hay edificios relacionados
		
				
				procesar_edificio_simple(it,res);
				it++;
	
		}else{						//Caso en el que se relacionan 2 edificios o mas
		
			if(edificio_contenido(it,next(it)){
			
				
			
			
			}

				
		}
	
		
		


	return 0;

	}
	
	











}
