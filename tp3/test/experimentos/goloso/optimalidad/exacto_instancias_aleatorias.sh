# !/bin/bash

# Este script ejecuta algoritmo exactocon el fin de obtener el peso.
# El grafo de entrada es el caso aleatorio. Para un mismo n y k, crea varios grafos.
# Recibe como parámetros:
#			- k, #nodos, #sem_inicial, #sem_final

k=$1
n=$2
d=$3
h=$4

while (($d<$h)); do
	m=$((n*2))
	../../../bin/grafos_completos $n $k $d | ../../../bin/opt_pexacto
	let d=$d+1
done
