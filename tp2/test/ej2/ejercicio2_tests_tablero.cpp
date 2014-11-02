#include <utility>
#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <list>
#include <chrono>
using namespace std;
typedef vector<vector<int> > matriz_int;





/* Esta funcion modifica la primer matriz, dejando la suma de la primera con la segunda
 **/
void sumar_matrices(matriz_int&  matriz_res, matriz_int& actual, int n){
	
	/* 
	 Sumo las matrices considerando si alguno de los valores a sumar
	 es -1, si es asi dejo -1, sino los sumo.
	*/
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if( actual[i][j] == -1 || matriz_res[i][j] == -1){
				matriz_res[i][j] = -1;
			} else {
				matriz_res[i][j] = matriz_res[i][j] + actual[i][j];
			}
		}
	}
}


/* Esta funcion devuelve el minimo de la matriz, junto con la respectiva
 * fila y columna del valor.
 * En caso de no haberlo, devuelve (-1, -1, -1).
 * */
tuple<int,int,int> buscar_minimo(matriz_int matriz, int n){

	/* Inicializo al resultado como inválido.
	 **/		
	tuple<int,int,int> res(-1, -1, -1);

	/* Me quedo con el mínimo valor no negativo.
	 * Si no lo hay, entonces no hay solución.
	 **/
	for(int i = 0; i<n; i++){
		for (int j = 0; j<n ; j++){
			if(get<0>(res) == -1 || (matriz[i][j] > -1 && matriz[i][j] < get<0>(res))){
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
		}
	}
}


void inicializar_con(matriz_int& m, int tam, int valor){
	for (int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			m[i][j] = valor;
		}
	}
}


// Esta funcion devuelve una terna con m f c.
void caballos_salvajes(int n, int k, pair<int, int> posiciones_caballos[], tuple<int,int,int> &res){

	matriz_int acumuladora(n, vector<int>(n));
	matriz_int actual(n, vector<int>(n));

	inicializar_con(acumuladora, n, 0);

	for (int h = 0; h < k; h++){
		inicializar_con(actual, n, -1);
		pair<int, int> pos = posiciones_caballos[h];
		actual[get<0>(pos)][get<1>(pos)] = 0;
		calcular_posiciones(actual, pos, n);
		sumar_matrices(acumuladora, actual, n);
	}
	
	res = buscar_minimo(acumuladora, n);

}


//Recibe la cantidad de iteraciones a realizar y cantidad de casilleros
int main(int argc, char** argv){
	
	if (argc < 3){
		cout << "Dame más parámetros cabeza" << endl;
		return 0;
	}		
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

