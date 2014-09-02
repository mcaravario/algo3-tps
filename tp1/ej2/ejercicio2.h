
#include <set>
#include <list>
#include <iterator>   
#include <iostream>    
#include <algorithm>    

using namespace std;



struct vertice{
  vertice();
  vertice(int x, int y);	
  int x;
  int y;
  	
};


struct edificio{
   edificio();
   edificio(int x1, int y, int x2);		
   vertice v1;
   vertice v2;	

};

vertice::vertice(){
	x=0;
	y=0;
}

vertice::vertice(int a, int b){
	x = a;
	y = b;	
}

edificio::edificio(int x1, int y, int x2){
	v1 = vertice(x1,y);
	v2 = vertice(x2,y);	
}

edificio::edificio(){
	v1.x = 0;
	v1.y = 0;
	v2.x = 0;
	v2.y = 0;
	
	}




bool hay_x_edificios_relacionados(set<edificio>::iterator it, int cant, set<edificio> edificios){

  bool parar = 0;                                        //Utilizo el flag para parar cuando encuentro los x edificios relacionados

	edificio e = *it;
  
	bool res = true;

  while(it != edificios.end() && !parar && cant > 0){

		set<edificio>::iterator sig = it++;

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

bool comparar_edificios(edificio e1, edificio e2){
 
	return ((e1.v1.x < e2.v1.x) || ((e1.v1.x == e2.v1.x) && (e1.v1.y > e2.v1.y)) ||  ((e1.v1.x == e2.v1.x) && (e1.v1.y == e2.v1.y) && (e1.v2.x < e2.v2.x)) );

}


bool vertice_contenido(set<edificio>::iterator it, vertice v){
	
	return ((v.x < it->v2.x) && (v.x > it->v1.x) && (v.y < it->v1.y));
} 



list<vertice> generar_horizonte(set<edificio>& edificios){

list<vertice>  res;

set<edificio>::iterator it = edificios.begin();



	while(it!= edificios.end()){
  
		if(hay_x_edificios_relacionados(it,0,edificios)){         //Si no hay edificios relacionados
		

			procesar_edificio_simple(it,res);
			it++;

		}else{            //Caso en el que se relacionan 2 edificios o mas
		
			set<edificio>::iterator sig = it++;
			
			if(edificio_contenido(it,sig)){

				edificios.erase(sig);
			
				if(hay_x_edificios_relacionados(it,0,edificios)){
					procesar_edificio_simple(it,res);
					it++;
				}
									
			}else{
					
				if(rompe_techo(it,sig)){
					// agrego el primer vertice del primer edificio, ya que se que no hay otro antes
					res.push_back(it->v1);
					//creo iterador al siguiente elemento
					set<edificio>::iterator sig = it++;

					// creo el nuevo edificio, el cual se desprende de la interseccion entre el edificio siguiente y el actual.
					edificio a_insertar = edificio(sig->v2.x,it->v1.y,it->v2.x);
					 // inserto ordenadamente el nuevo edificio en mi avl para analizarlo en el futuro.
					edificios.insert(a_insertar);

					it++;
				
				}else{
					/*
					if(vertice_contenido(it,sig->v1)){
						//creo nuevo edificio con el vertice corrido de lugar
						edificio nuevo_edificio = edificio(it->v2.x,sig->v1.y,sig->v2.x);
						//elimino el siguiente
						edicios.erase(sig);
						//inserto ordenadamente el nuevo edificio que cree
						edificios.insert(nuevo_edificio);
						
						if(hay_x_edificios_relacionados(it,0,edificios){
						
							res.push_back(it->v1);
							it++;
						}
					*/	
						
					}	
					
				}			
			}					
		}                                                      
	
	return res;
}



