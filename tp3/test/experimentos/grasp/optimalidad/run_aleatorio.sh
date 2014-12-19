# !/bin/bash

# Este script ejecuta la heuristica golosa con el fin de obtener el peso.
# El grafo de entrada es aleatorio.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4

while (($d<$h)); do
	let m=$((d*2)) 
	../../../bin/grafos_completos $d $k $s | ../../../bin/opt_grasp
	let d=$d+1
done
