# !/bin/bash

# Este script ejecuta el algoritmo exacto con el fin de obtener el peso.
# El grafo de entrada es el caso malo. Para un mismo n y k, crea varios grafos.
# Recibe como parámetros:
#			- k, #nodos, #sem_inicial, #sem_final

k=$1
n=$2
d=$3
h=$4

while (($d<=$h)); do
	../../../bin/generador_malo $n $k $d | ../../../bin/opt_pexacto
	let d=$d+1
done
