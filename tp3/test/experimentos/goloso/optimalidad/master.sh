# !/bin/bash

# Este script ejecuta los test de optimalidad de la herística golosa.

#>>>  Caso Aleatorio
# Fijaremos k = 2,3,4 y variaremos el n = [5,20] m = 2n
./run_aleatorio.sh 2 5 20 13 > gol.rand.k2.out
./run_aleatorio.sh 3 5 20 13 > gol.rand.k3.out
./run_aleatorio.sh 4 5 20 13 > gol.rand.k4.out

./varias_instancias_aleatorias.sh 3 15 0 10 > gol.tabla.rand.k3.n15.s10.out 

#>>>  Caso Malo
# Fijaremos k = 2,3,4 y variaremos el n = [5,20] m = 2n
./run_malo.sh 2 5 20 13 > gol.malo.k2.out
./run_malo.sh 3 5 20 13 > gol.malo.k3.out
./run_malo.sh 4 5 20 13 > gol.malo.k4.out


./varias_instancias_malas.sh 3 15 0 10 > gol.tabla.malo.k3.n15.s10.out 

#Genero resultados con el exacto para las mismas instancias (para comparar)
./run_exacto_aleatorio.sh 2 5 20 13 > exacto.rand.k2.out
./run_exacto_aleatorio.sh 3 5 20 13 > exacto.rand.k2.out
./run_exacto_aleatorio.sh 3 5 20 13 > exacto.rand.k2.out

./exacto_instancias_aleatorias.sh 3 15 0 10 > exacto.tabla.rand.k3.n15.s10.out 

./run_exacto_malo.sh 2 5 20 13 > exacto.malo.k2.out
./run_exacto_malo.sh 3 5 20 13 > gol.malo.k2.out
./run_exacto_malo.sh 4 5 20 13 > gol.malo.k2.out

./exacto_instancias_malas.sh 3 15 0 10 > exacto.tabla.malo.k3.n15.s10.out 
