#include <utility>
#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <list>
#include <chrono>
using namespace std;
typedef vector<vector<int> > matriz_int;



/*Esta funcion devuelve true si no hay solucion, es decir que todos los valores
 * son -1,  y false en caso contrario */ 
bool no_hay_sol(matriz_int mz, int n){
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if(mz[i][j] != -1){
				return false;
			}
		}
	}

return true;
}


/* Esta funcion modifica la primer matriz, dejando la suma de todas las
matrices pasadas como parametro */
void sumar_matrices(matriz_int&  matriz_res, vector<matriz_int>& matrices_caballos, int n, int k){
	
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
/* Esta funcion devuelve el minimo de la matriz, junto con la respectiva
 * fila y columna del valor */
tuple<int,int,int> buscar_minimo(matriz_int matriz, int n){
	/*inicializo el resultado con el valor del primer casillero de
	 * la matriz*/
	tuple<int,int,int> res(matriz[0][0],0,0) ;
/*
	for(int i = 0; i<n; i++){
			for (int j = 0; j<n ; j++){
				cout << matriz[i][j] << " ";
			}
			cout << endl;
		}
*/
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
/* Devuelve true si la posicion i,j es valida dentro del tablero de n*n */ 
inline bool es_valido(int i, int j, int n){	
	return (i < n && j < n && i >= 0 && j >= 0);
}

/* Calcula los casilleros alcanzables por un caballo desde una determinada posicion*/
void calcular_vecinos(list<pair<int,int> > &vecinos, pair<int,int> actual, int n){
	int i = get<0>(actual);	
	int j = get<1>(actual);	

	if(es_valido(i+1,j-2,n)){
		vecinos.push_back(pair<int,int>(i+1,j-2));
	}	
	if(es_valido(i+1,j+2,n)) vecinos.push_back(pair<int,int>(i+1,j+2));
	if(es_valido(i-1,j-2,n)) vecinos.push_back(pair<int,int>(i-1,j-2));
	if(es_valido(i-1,j+2,n)) vecinos.push_back(pair<int,int>(i-1,j+2));
	if(es_valido(i-2,j+1,n)) vecinos.push_back(pair<int,int>(i-2,j+1));
	if(es_valido(i-2,j-1,n)) vecinos.push_back(pair<int,int>(i-2,j-1));
	if(es_valido(i+2,j+1,n)) vecinos.push_back(pair<int,int>(i+2,j+1));
	if(es_valido(i+2,j-1,n)) vecinos.push_back(pair<int,int>(i+2,j-1));

} 


/*Esta funcion llena la matriz, con el costo de movimientos de cada caballo a su respectivo casillero
 * comenzando por la posicion pasada como parametro. */
void calcular_posiciones(matriz_int &matriz, pair<int,int> pos, int n){
	queue<pair<int,int> > proximos_casilleros;
	proximos_casilleros.push(pos);

	while(!proximos_casilleros.empty()){
		pair<int,int> actual = proximos_casilleros.front();
		list<pair<int,int> > vecinos;
		proximos_casilleros.pop();
		calcular_vecinos(vecinos,actual,n);
		auto it = vecinos.begin();

		//Reviso a los vecinos y actualizo sus valores segun corresponda.
		while(it != vecinos.end()){
			if(matriz[get<0>(*it)][get<1>(*it)] < 0){
				matriz[get<0>(*it)][get<1>(*it)] = matriz[get<0>(actual)][get<1>(actual)] + 1;
				proximos_casilleros.push(*it);	
			}
			it++;
		}/*
	for(int i = 0; i<n; i++){
		for (int j = 0; j<n ; j++){
			cout << matriz[i][j] << " ";
			}
		cout << endl;
	}
	cout << endl;
	*/
	}
}

// Esta funcion devuelve una terna con m f c.
void caballos_salvajes(int n, int k, pair<int, int> posiciones_caballos[], tuple<int,int,int> &res){

	vector<matriz_int> matrices_caballos(k, vector<vector<int> >(n, vector<int>(n))) ;
	
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
	for(int h = 0; h<k; h++){
		pair<int, int> pos = posiciones_caballos[h];
		matrices_caballos[h][get<0>(pos)][get<1>(pos)] = 0;
		calcular_posiciones(matrices_caballos[h],pos,n);
	
	}
	
	matriz_int  matriz_res(n, vector<int>(n));
	sumar_matrices(matriz_res, matrices_caballos,n,k);

/*
	for(int i = 0; i<n; i++){
		for (int j = 0; j<n ; j++){
			cout << matriz_res[i][j];
			}
		cout << endl;
	}
*/	
	if(no_hay_sol(matriz_res,n)){
		/* Si no hay solucion devuelvo -1 */
		tuple<int, int, int> result(-1, -1, -1);
		res = result;
	}else{
	
	tuple<int, int, int> result = buscar_minimo(matriz_res,n);
	res = result;


	}
	
}


//Recibe la cantidad de iteraciones a realizar y cantidad de casilleros
int main(int argc, char** argv){
	
	int iteraciones = atoi(argv[1]);
	int cant_casilleros = atoi(argv[2]);
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
	using namespace std::chrono;
	high_resolution_clock reloj;
	size_t mi = 99999999;
	
	while(iteraciones != 0){
	tuple<int,int,int> res;
	auto t1 = reloj.now();
	caballos_salvajes(n,k,posiciones_caballos,res);
	auto t2 = reloj.now();
	auto total = duration_cast<microseconds>(t2-t1).count();
	
	if(total < mi) mi = total;
	iteraciones--;
	}
	
	cout << cant_casilleros << " " << mi << endl; 
/*	
	if(get<0>(res) == -1){
		cout << "NO" << endl;
	}else{
		cout <<  get<1>(res) << " " << get<2>(res) << " " << get<0>(res);
	}
*/
	return 0;
	}

