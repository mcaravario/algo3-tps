# !/bin/bash

# Este script ejecuta la heuristica golosa con el fin de obtener el peso.
# El grafo de entrada es el caso malo. Para un mismo n y k, crea varios grafos.
# Recibe como parámetros:
#			- k, #nodos, #sem_inicial, #sem_final

k=$1
n=$2
d=$3
h=$4
centrales=$k
satelites=0

while (($d<$h)); do
	let satelites=$n-$centrales
	../../../bin/generador_malo $centrales $satelites $k $d | ../../../bin/opt_grasp
	let d=$d+1
done
