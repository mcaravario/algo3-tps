# !/bin/bash

# Este script ejecuta la heuristica golosa con el fin de obtener el peso.
# El grafo de entrada es el caso malo.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla
# #centrales = k
# #satelites = #nodos - k

k=$1
d=$2
h=$3
s=$4
centrales=$k
satelites=0

while (($d<$h)); do
	let satelites=$d-$centrales
	../../../bin/generador_malo $centrales $satelites $k $s | ../../../bin/opt_grasp $s 1 1 5 3
	let d=$d+1
done
