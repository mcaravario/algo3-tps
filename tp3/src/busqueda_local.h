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

int costoNuevo_2opt(vector<conjunto>& res,int k, int pos, int i, int nodo1, int nodo2, vector<vector<int> >& mz_ady){
	int conteo = 0;
	int j= 0;
	while(j < k){
		if(j == pos){
			conteo += (res[j].peso - peso_asociado(res[j], mz_ady, nodo1) - peso_asociado(res[j], mz_ady, nodo2));
			if(mz_ady[nodo1][nodo2] != -1) conteo += mz_ady[nodo1][nodo2];
		}else if(j == i){
			conteo += (res[j].peso + peso_asociado(res[j], mz_ady, nodo1) + peso_asociado(res[j], mz_ady, nodo2));
			if(mz_ady[nodo1][nodo2] != -1) conteo += mz_ady[nodo1][nodo2];
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

void  modificarRes_2opt(vector<conjunto>& result, int ori, int dst, int nodo1, int nodo2, vector<vector<int> >& mz_ady){
	if (ori != -1){
		result[dst].peso += peso_asociado(result[dst], mz_ady, nodo1);
		result[dst].peso += peso_asociado(result[dst], mz_ady, nodo2);
		if(mz_ady[nodo1][nodo2] != -1) result[dst].peso += mz_ady[nodo1][nodo2];
		result[ori].peso -= peso_asociado(result[ori], mz_ady, nodo1);
		result[ori].peso -= peso_asociado(result[ori], mz_ady, nodo2);
		if(mz_ady[nodo1][nodo2] != -1) result[ori].peso += mz_ady[nodo1][nodo2];
		result[dst].elementos.push_back(nodo1);
		result[dst].elementos.push_back(nodo2);
		result[ori].elementos.remove(nodo1);
		result[ori].elementos.remove(nodo2);
	}
}

void busquedaLocal_1opt(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
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

void busquedaLocal_2opt(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	bool encontrado = false;
	while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res);
		bool hayMejor = false;
		int ultimo_dst = -1;
		int ultimo_ori = -1;
		while(i < k){
			if(res[i].peso > 0 && res[i].elementos.size()>1){
				auto itNodo1 = res[i].elementos.begin();
				auto tope = res[i].elementos.end();
				tope--;
				while(itNodo1 != tope){
					auto itNodo2 = itNodo1;
					itNodo2++;
					while(itNodo2 != res[i].elementos.end()){
						int dst = 0;
						while(dst < k){
							if(dst != i){
								if(costoParcial > costoNuevo_2opt(res, k, i, dst,*itNodo1, *itNodo2, mz_ady )){
									modificarRes_2opt(res_vecino, ultimo_ori, ultimo_dst, *itNodo1, *itNodo2,  mz_ady);
									modificarRes_2opt(res_vecino, i, dst, *itNodo1, *itNodo2, mz_ady);
									ultimo_dst = dst;
									ultimo_ori = i;
									hayMejor = true;
									costoParcial = suma_total(res_vecino);
								}
							}
							dst++;
						}
						itNodo2++;
					}
					itNodo1++;
				}
			}
			i++;
		}
		if(!hayMejor) encontrado = true;
		res= res_vecino;
	}
}


vector<int> iniciar_local_1opt(list<arista> aristas, int n, int k){
	
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	vector<conjunto> res_inicial = crearResultado(mz_ady, n, k);
	vector<int> vistos(n);
	busquedaLocal_1opt(res_inicial, mz_ady, k);
	establecer_posiciones(res_inicial, vistos);
	return vistos;
}

vector<int> iniciar_local_2opt(list<arista> aristas, int n, int k){
	
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	vector<conjunto> res_inicial = crearResultado(mz_ady, n, k);
	vector<int> vistos(n);
	busquedaLocal_2opt(res_inicial, mz_ady, k);
	establecer_posiciones(res_inicial, vistos);
	return vistos;
}
