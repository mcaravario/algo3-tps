
#include <set>
#include <list>
#include <iterator>   
#include <iostream>    
#include <algorithm>    

using namespace std;



struct vertice{
	
  int x;
  int y;
  	
};


struct edificio{

   vertice v1;
   vertice v2;	

};


bool hay_x_edificios_relacionados(set<edificio>::iterator it, int cant, set<edificio> edificios){

  bool parar = 0;                                        //Utilizo el flag para parar cuando encuentro los x edificios relacionados

	edificio e = *it;
  
	bool res = true;

  while(it != edificios.end() && !parar && cant > 0){

		set<edificio>::iterator sig = next(it,1);

    if(!(sig->v1.x <= e.v2.x)){  	// Caso en el quei no hay un edificio relacionado  

      parar = 1;
      res = false;	

    }else{

      cant--;    
      it++;
	
    }


 }

return res;

}


bool comparar_edificios(edificio e1, edificio e2){
return false;
}

void procesar_edificio_simple(set<edificio>::iterator it, list<vertice> res){


	res.push_back(it->v1);		//agrego el primer vertice sin modificar
	
	vertice insertar = it->v2;						//modifico la altura del segundo vertice y la "bajo" al piso y luego la agrego al resultado

	insertar.y = 0;
	
	res.push_back(insertar);		

}



/********ACORDARSE DE HACER MACROS PARA COMPARAR LOS VERTICES **********/
/*
bool contengo_edificio(const iterador it){

edificio e1 = it.actual();		
edificio e2 = it.siguiente();		//Solo chequeo el edificio actual y el siguiente, ya que estan ordenados.

bool res = false;

  if((e1.v1 <= e2.v1) && (e2.v1 < e1.v2) && (e2.v2 <= e1.v2) && (e1.v1.y >= e2.v1.y) ){

    res = true;
  }		

return res;

}
*/
/*
bool rompe_techo(edificio e, edificio sig){


}

bool contengo_vertice(edificio e, vertice v){

}
*/


bool edificio_contenido(set<edificio>::iterator it, set<edificio>::iterator sig){

return true;
}


void reordenar_estructura(set<edificio> edificios, set<edificio>::iterator it){
}

bool rompe_techo(set<edificio>::iterator it,set<edificio>::iterator sig){
}



list<vertice> generar_horizonte(set<edificio> edificios){

list<vertice>  res;

set<edificio>::iterator it = edificios.begin();



 while(it!= edificios.end()){
  
    if(hay_x_edificios_relacionados(it,0,edificios)){         //Si no hay edificios relacionados
    

        procesar_edificio_simple(it,res);
        it++;

    }	else{            //Caso en el que se relacionan 2 edificios o mas
    
      	if(edificio_contenido(it,next(it,1))){

						edificios.erase(next(it,1));
					
						if(hay_x_edificios_relacionados(it,0,edificios)){

							procesar_edificio_simple(it,res);
							 
							it++;				
	
						}

    
					
      	}else{
				
					if(rompe_techo(it,next(it,1))){
					
						res.push_back(it->v1);

						set<edificio>::iterator sig = next(it,1);		//creo iterador al siguiente elemento

						res.push_back(it->v1);				// agrego el primer vertice del primer edificio, ya que se que no hay otro antes

						vertice nuevo_v1;

						vertice nuevo_v2;
						
						nuevo_v1.x = sig->v2.x;		//le asigno el mismo x que tenia el vertice 2 del edficio siguiente.

						nuevo_v1.y = it->v1.y;

						nuevo_v2 = it->v2;			// el nuevo v2 es el mismo v2 que el del edificio en el que estoy parado.

						edificio a_insertar;		// creo el nuevo edificio, el cual se desprende de la interseccion entre el edificio siguiente y el actual.

						a_insertar.v1 = nuevo_v1;
						a_insertar.v2 = nuevo_v2;
					
						edificios.insert(it,a_insertar); // inserto ordenadamente el nuevo edificio en mi avl para analizarlo en el futuro.

						it++;
					
					}
				
				}
				
				



    	}	
                                                      
	}



return res;

}


