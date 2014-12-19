# !/bin/bash

# Este script ejecuta los test de optimalidad de la herística golosa.

#>>>  Caso Aleatorio (grafo completo)
# Fijaremos k = 2,3,4 y variaremos el n = [5,23]
./run_aleatorio.sh 2 5 23 0 > grasp.rand.k2.out
./run_aleatorio.sh 3 5 23 0 > grasp.rand.k3.out
./run_aleatorio.sh 4 5 23 0 > grasp.rand.k4.out

./varias_instancias_aleatorias.sh 3 15 0 10 > grasp.tabla.rand.k3.n15.s10.out 

#>>>  Caso Malo
# Fijaremos k = 2,3,4 y variaremos el n = [5,23]
./run_malo.sh 2 5 23 13 > grasp.malo.k2.out
./run_malo.sh 3 5 23 13 > grasp.malo.k3.out
./run_malo.sh 4 5 23 13 > grasp.malo.k4.out


./varias_instancias_malas.sh 3 15 0 10 > grasp.tabla.malo.k3.n15.s10.out 

