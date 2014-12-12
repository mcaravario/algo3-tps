#include "busqueda_local.h"

int main() {
	
	int n,m,k,u,v,w;
  cin >> n;
  cin >> m;
  cin >> k;
 
	list<arista> aristas;
  /* Creo la lista de aristas. */
  for (int i = 0; i < m; i++){
    cin >> u;
    cin >> v;
    cin >> w;
    u--;
    v--;
		aristas.push_back(arista(u,v,w));
   }

	/* Funcion que resuelve el ejercicio. */
	vector<int> posiciones = iniciar_local_2opt(aristas, n, k);

	/* Imprimo por salida estandar el resultado. */
	mostrar_res(posiciones);
	return 0;
}
