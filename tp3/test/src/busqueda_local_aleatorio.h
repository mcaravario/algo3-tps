#include "kpmp.h"

vector<conjunto> resultado_aleatorio(vector<vector<int> >& mz_ady, int n, int k){
	vector<conjunto> resultado(k,conjunto());
	for(int i = 0; i < n ; i++){
		int dst = rand()% k;
		resultado[dst].elementos.push_back(i);		
	}
	for(int i =0 ; i < k; i++){
		pesoParticion(resultado[i], mz_ady);
	}
	return resultado;
}

/*Calcula el costo de la solucion entera, complejidad O(n)   */
int costoNuevo(vector<conjunto>& res,int ori, int dst, int nodo, vector<vector<int> >& mz_ady, int costo){
	
	int conteo = costo;
	conteo = conteo - peso_asociado(res[ori], mz_ady, nodo);
	conteo += peso_asociado(res[dst], mz_ady, nodo);
	return conteo;
}

/* complejidad O(n) */
int costoNuevo_2opt(vector<conjunto>& res, int pos, int i, int nodo1, int nodo2, vector<vector<int> >& mz_ady, int costo){
	int conteo = costo;
	conteo -= (peso_asociado(res[pos], mz_ady, nodo1) +  peso_asociado(res[pos], mz_ady, nodo2));
	if(mz_ady[nodo1][nodo2] != -1) conteo += mz_ady[nodo1][nodo2];
	conteo += peso_asociado(res[i], mz_ady, nodo1) + peso_asociado(res[i], mz_ady, nodo2);
	if(mz_ady[nodo1][nodo2] != -1) conteo += mz_ady[nodo1][nodo2];
	return conteo;
}

/*complejidad O(n) */
void  modificarRes(vector<conjunto>& result, int ori, int dst, int nodo, vector<vector<int> >& mz_ady){
	if (ori != -1){
		int p_dst = peso_asociado(result[dst], mz_ady, nodo);
		result[dst].peso =  	result[dst].peso + p_dst;
		int p_ori = peso_asociado(result[ori], mz_ady, nodo);
		result[ori].peso = result[ori].peso - p_ori;
		result[dst].elementos.push_back(nodo);
		result[ori].elementos.remove(nodo);
	}
}

/*complejidad O(n) */
void  modificarRes_2opt(vector<conjunto>& result, int ori, int dst, int nodo1, int nodo2, vector<vector<int> >& mz_ady){
	if (ori != -1){
		int p_dst1 = peso_asociado(result[dst], mz_ady, nodo1);	
		int p_dst2 = peso_asociado(result[dst], mz_ady, nodo2);	
		result[dst].peso =  result[dst].peso + p_dst1 +p_dst2;
		if(mz_ady[nodo1][nodo2] != -1) result[dst].peso += mz_ady[nodo1][nodo2];
		
		int p_ori1 = peso_asociado(result[ori], mz_ady, nodo1);
		int p_ori2 = peso_asociado(result[ori], mz_ady, nodo2);
		result[ori].peso = result[ori].peso - (p_ori1 + p_ori2); 
		if(mz_ady[nodo1][nodo2] != -1) result[ori].peso += mz_ady[nodo1][nodo2];
		
		result[dst].elementos.push_back(nodo1);
		result[dst].elementos.push_back(nodo2);
		result[ori].elementos.remove(nodo1);
		result[ori].elementos.remove(nodo2);
	}
}
//O(n²*k)
void busquedaLocal_1opt(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	bool encontrado = false;
	while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res); // O(k)
		bool hayMejor = false;
		while(i < k){
			if(res[i].peso > 0){
				auto itNodo = res[i].elementos.begin();
				while(itNodo != res[i].elementos.end()){ //O(n²*k)
					int dst = 0;
					while(dst < k){ //O(k*n)
						if(dst != i){
							int p_costo = costoNuevo(res, i, dst,*itNodo, mz_ady, suma_total(res)); //O(n)
							if(costoParcial > p_costo ){
								res_vecino = res;//O=(n)
								modificarRes(res_vecino, i, dst, *itNodo, mz_ady); //O(n)
								hayMejor = true;
								costoParcial = p_costo;
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


/* Para testeo de complejidad O(k²n + kn²). */
void busquedaLocal_1opt_test(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	//bool encontrado = false;
	//while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res); // O(k)
		//bool hayMejor = false;
		while(i < k){
			if(res[i].peso > 0){
				auto itNodo = res[i].elementos.begin();
				while(itNodo != res[i].elementos.end()){ //O(k²n +kn²)
					int dst = 0;
					while(dst < k){ //O(k²+kn)
						if(dst != i){
							int p_costo = costoNuevo(res, i, dst,*itNodo, mz_ady, suma_total(res)); //O(k+n)
							if(costoParcial > p_costo ){
								res_vecino = res;//O=(n)
								modificarRes(res_vecino, i, dst, *itNodo, mz_ady); //O(n)
								//hayMejor = true;
								costoParcial = p_costo;
							}
						}
						dst++;
					}
					itNodo++;
				}
			}
			i++;
		}
		/*if(!hayMejor) encontrado = true;
		res= res_vecino;
	}*/
}


///O(n²k² + kn³)
void busquedaLocal_2opt(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	bool encontrado = false;
	while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res);
		bool hayMejor = false;
		while(i < k){
			if(res[i].peso > 0){
				auto itNodo1 = res[i].elementos.begin();
				auto tope = res[i].elementos.end();
				tope--;
				while(itNodo1 != tope){ //O(n²k² + kn³)
					auto itNodo2 = itNodo1;
					itNodo2++;
					while(itNodo2 != res[i].elementos.end()){ //O(nk² +kn²)
						int dst = 0;
						while(dst < k){ // O(k²+ kn)
							if(dst != i){
								int p_costo = costoNuevo_2opt(res, i, dst,*itNodo1, *itNodo2, mz_ady, suma_total(res)) ;//O(k+n)
								if(costoParcial > p_costo){
									res_vecino = res;
									modificarRes_2opt(res_vecino, i, dst, *itNodo1, *itNodo2, mz_ady);
									hayMejor = true;
									costoParcial = p_costo;
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

/* Para testeo de complejidad. */
void busquedaLocal_2opt_test(vector<conjunto>& res, vector<vector<int> >& mz_ady, int k){
	//bool encontrado = false;
	//while(!encontrado){
		vector<conjunto> res_vecino = res;
		int i = 0;
		int costoParcial = suma_total(res);
		//bool hayMejor = false;
		while(i < k){
			if(res[i].peso > 0){
				auto itNodo1 = res[i].elementos.begin();
				auto tope = res[i].elementos.end();
				tope--;
				while(itNodo1 != tope){ //O(k*n³)
					auto itNodo2 = itNodo1;
					itNodo2++;
					while(itNodo2 != res[i].elementos.end()){ //O(k*n²)
						int dst = 0;
						while(dst < k){ // O(k*n)
							if(dst != i){
								int p_costo = costoNuevo_2opt(res, i, dst,*itNodo1, *itNodo2, mz_ady, suma_total(res)) ;
								if(costoParcial > p_costo){
									res_vecino = res;
									modificarRes_2opt(res_vecino, i, dst, *itNodo1, *itNodo2, mz_ady);
									//hayMejor = true;
									costoParcial = p_costo;
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
		//if(!hayMejor) encontrado = true;
		//res= res_vecino;
	//}
}

vector<int> iniciar_local_1opt(list<arista>& aristas, int n, int k){
	
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	vector<conjunto> res_inicial = resultado_aleatorio(mz_ady, n, k);
	vector<int> vistos(n);
	busquedaLocal_1opt_test(res_inicial, mz_ady, k);
	establecer_posiciones(res_inicial, vistos);
	return vistos;
}

vector<int> iniciar_local_2opt(list<arista>& aristas, int n, int k){
	
	vector<vector<int> > mz_ady = crear_adyacencias(aristas, n);
	vector<conjunto> res_inicial = resultado_aleatorio(mz_ady, n, k);
	vector<int> vistos(n);
	busquedaLocal_2opt_test(res_inicial, mz_ady, k);
	establecer_posiciones(res_inicial, vistos);
	return vistos;
}
