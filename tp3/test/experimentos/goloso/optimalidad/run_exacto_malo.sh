# !/bin/bash

# Este script ejecuta el algoritmo exacto con el fin de obtener el peso.
# El grafo de entrada es el caso malo. Se generan varias instancias de grafos del mismo tamaño.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4
centrales=$k
satelites=0

while (($d<$h)); do
	let satelites=$d-$centrales
	../../../bin/generador_malo $centrales $satelites $k $s | ../../../bin/opt_pexacto
	let d=$d+1
done
