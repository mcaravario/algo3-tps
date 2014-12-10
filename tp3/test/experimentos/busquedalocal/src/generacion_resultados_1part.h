#include <vector>
#include <list>
#include <iostream>
#include <tuple>

using namespace std;

#define MAX_INT 2147483647                                                                 
 
struct particion{                                                   
	list<int> elementos;                                              
	int peso;                                                         
	particion(): elementos(), peso(0) {}                              
};

void pesoParticion(particion& p, vector<vector<int> >& mz_ady){
	p.peso = 0;
	list<int>::iterator it1 = p.elementos.begin();
	list<int>::iterator tope = p.elementos.end();
	tope--;
	for(it1; it1 != tope; it1++){
		list<int>::iterator it2 = it1;
		it2++;
		while(it2 != p.elementos.end()){
			if(mz_ady[*it1][*it2] != -1) p.peso += mz_ady[*it1][*it2];
			it2++;
		}
	}
}


vector<particion> crearResultado(int n, int k, vector<vector<int> >& mz_ady){
	vector<particion> res (k, particion());
	int i = 0;
	for(i; i<n; i++){
		res[0].elementos.push_back(i);
	}
	
	pesoParticion(res[0], mz_ady);

	return res;
}    
