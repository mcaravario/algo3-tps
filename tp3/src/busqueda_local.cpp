#include "busqueda_local.h"

int main() {
	
	int n,m,k,u,v,w;
  cin >> n;
  cin >> m;
  cin >> k;
  vector<vector<int> > mz_ady(n, vector<int>(n));
  list<tuple<int,int,int> > aristas;
  vector<int> vistos(n);
	vector<bool> p_vistas(n,false);

  /* Inicializo matriz de adyacencias */
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      mz_ady[i][j] = -1;
    }
  }

  /* Inicializacion de estructuras */
  for (int i = 0; i < m; i++){
    cin >> u;
    cin >> v;
    cin >> w;
    /* Resto uno para que no haya problemas con los bordes. Los nodos estan numerados de 0 a n-1*/
    u--;
    v--;

    if(mz_ady[u][v] == -1 || mz_ady[v][u] == -1){
      mz_ady[u][v] = w;
      mz_ady[v][u] = w;
      aristas.push_back(make_tuple(u,v,w));
    }
  }

	vector<particion> res = crearResultado(n,k,mz_ady);
	int c = costoTotal(res, k);
  busquedaLocal(res,k,mz_ady,n,c,false);

	/* creando vector para imprimir resultado*/
	vector<int> resultado(n);
	for(int i=0; i<k; i++){
		for(list<int>::iterator it= res[i].elementos.begin(); it != res[i].elementos.end(); it++){
			resultado[*it] = i;
		}
	}

	for(int i = 0; i < n; i++) cout << resultado[i] << " "; 
	cout << endl;
	return 0;
}
