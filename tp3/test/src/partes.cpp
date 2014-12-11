#include <vector>
#include <list>
#include <iostream>
using namespace std;

#define CANT_BOLSAS 3

// Declaración
void mostrarBolsas(vector<list<int> >& bolsas);

// Se utiliza para numerar los resultados
unsigned int n = 0;

void partes(vector<list<int> >& bolsas, list<int> candidatos) {
	if (candidatos.size() == 0) {
		n++;
		mostrarBolsas(bolsas);
	}else {
		int elegido = *candidatos.begin();
		candidatos.pop_front();
		for (unsigned int i = 0; i < bolsas.size(); i++){
			bolsas[i].push_back(elegido);
			partes(bolsas, candidatos);
			int tam = bolsas[i].size();
			bolsas[i].pop_back();
			if (tam == 1) i = bolsas.size();
		}
	}
}

void mostrarBolsas(vector<list<int> >& bolsas) {
	cout << ">>> Bolsa número " << n << endl;
	for (unsigned int i = 0; i < bolsas.size(); i++){
		cout << "Bolsa " << i << ": ";
		auto it = bolsas[i].begin();
		while(it != bolsas[i].end()){
			cout << *it << " ";
			it++;
		}
		cout << endl; 
	}
	cout << endl;	
}

int main() {
	
	vector<list<int> > bs(CANT_BOLSAS, list<int>());
	list<int>	cn {1, 2, 3, 4, 5, 6, 7};

	partes(bs, cn);	

	return 0;
}
