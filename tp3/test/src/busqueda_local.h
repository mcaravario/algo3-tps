#include "kpmp.h"

/*Calcula el costo de la solucion entera*/
int costoNuevo(vector<conjunto>& res,int k, int pos, int i, int nodo, vector<vector<int> >& mz_ady){
	int conteo = 0;
	int j= 0;
	while(j < k){
		if(j == pos){
			conteo += (res[j].peso - peso_asociado(res[j], mz_ady, nodo));
		}else if(j == i){
			conteo += (res[j].peso + peso_asociado(res[j], mz_ady, nodo));
		}else{
			 conteo += res[j].peso;
		}
		j++;
	}
	return conteo;
}


void  modificarRes(vector<conjunto>& result, int ori, int dst, int nodo, vector<vector<int> >& mz_ady){
	if (ori != -1){
		result[dst].peso += peso_asociado(result[dst], mz_ady, nodo);
		result[ori].peso -= peso_asociado(result[ori], mz_ady, nodo);
		result[dst].elementos.push_back(nodo);
		result[ori].elementos.remove(nodo);
	}
}



void busquedaLocal(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	bool encontrado = false;
	while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res);
		bool hayMejor = false;
		int ultimo_dst = -1;
		int ultimo_ori = -1;
		while(i < k){
			if(res[i].peso > 0){
				auto itNodo = res[i].elementos.begin();
				while(itNodo != res[i].elementos.end()){
					int dst = 0;
					while(dst < k){
						if(dst != i){
							if(costoParcial > costoNuevo(res, k, i, dst,*itNodo, mz_ady )){
								modificarRes(res_vecino, ultimo_ori, ultimo_dst, *itNodo, mz_ady);
								modificarRes(res_vecino, i, dst, *itNodo, mz_ady);
								ultimo_dst = dst;
								ultimo_ori = i;
								hayMejor = true;
								costoParcial = suma_total(res_vecino);
							}
						}
						dst++;
					}
					itNodo++;
				}
			}
			i++;
		}
		if(!hayMejor) encontrado = true;
		res= res_vecino;
	}
}

vector<int> iniciar_local(list<arista> aristas, int n, int k){
	
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	vector<conjunto> res_inicial = crearResultado(mz_ady, n, k);
	vector<int> vistos(n);
	busquedaLocal(res_inicial, mz_ady, k);
	establecer_posiciones(res_inicial, vistos);
	return vistos;
}

