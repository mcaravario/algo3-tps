//typedef vector< vector<int> > matriz
#include <utility>
#include <iostream>
#include <tuple>

using namespace std;

/*Esta funcion devuelve true si no hay solucion y false en caso contrario */ 
bool no_hay_sol(int** matriz, int n){
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if(matriz[i][j] == -1){
				return true;
			}
		}
	}

return false;
}


/* Esta funcion modifica la primer matriz, dejando la suma de todas las
matrices pasadas como parametro */
void sumar_matrices(int** matriz_res, int*** matrices_caballos, int n, int k){
	
	//inicializo el resultado en 0
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			matriz_res[i][j] = 0;		
		}
	}
	/* 
	 Sumo las matrices considerando si alguno de los valores a sumar
	 es -1, si es asi dejo -1, sino los sumo.
	*/
	for(int h = 0; h<k ; h++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(matrices_caballos[h][i][j] == -1 || matriz_res[i][j] == -1){
					matriz_res[i][j] = -1;
				} else {
					matriz_res[i][j] = matriz_res[i][j] + matrices_caballos[h][i][j];
				}
			}
		}
	}
}

tuple<int,int,int> buscar_minimo(int** matriz, int n){
	/*inicializo el resultado con el valor del primer casillero de
	 * la matriz*/
	tuple<int,int,int> res(matriz[0][0],0,0) ;
	for(int i = 0; i<n; i++){
		for (int j = 0; j<n ; j++){
			if(get<0>(res) > matriz[i][j]){
				tuple<int,int,int> nuevo_min(matriz[i][j],i,j);
				res = nuevo_min;
			}
		}
	}
return res;

}

// Esta funcion devuelve una terna con m f c.
tuple<int, int, int> caballos_salvajes(int n, int k, pair<int, int> posiciones_caballos[]){

	int matrices_caballos[k][n][n];
	
	/* LLeno la matriz con -1 para indicar las posiciones invalidas */
	for(int h = 0; h < k; h++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				matrices_caballos[h][i][j] = -1;		
			}
		}
	}

	/*
	Asigno las posiciones iniciales de cada caballo en 0 y lleno su
	respectiva matriz, calculando la distancia a cada casillero	
	*/
	for(int i = 0; i<k; i++){
		pair<int, int> pos = posiciones_caballos[i];
		matrices_caballos[i][get<0>(pos)][get<1>(pos)] = 0;
		calcular_posiciones(matrices_caballos[i],pos);
	}
	
	int matriz_res[n][n];
	sumar_matrices(matriz_res, matrices_caballos,n,k);

	if(no_hay_sol(matriz_res)){
		/* Si no hay solucion devuelvo -1 */
		tuple<int, int, int> res(-1, -1, -1);
		return res;
	}
	
	tuple<int, int, int> res = buscar_minimo(matriz_res,n);
	
	return res;
	
}



int main(int argc, char** argv){
	
	int n,k;
	cin >> n;
	cin >> k;
	pair<int, int> posiciones_caballos[k]; 
	//Creo un arreglo con las posiciones iniciales de cada caballo,
	//leidas del stdin.
	for(int i = 0; i < k ; i++){
		int f,c;
		cin >> f;
		cin >> c;
		auto par = make_pair(f,c);
		posiciones_caballos[i] = par;	
	}
	
	//tuple<int,int,int> res ;
	auto res = caballos_salvajes(n,k,posiciones_caballos);
	
	if(get<0>(res) == -1){
		cout << "NO" << endl;
	}
	
	
	cout << get<1>(res) << " " << get<2>(res) << " " << get<0>(res);
	
	return 0;
	}

