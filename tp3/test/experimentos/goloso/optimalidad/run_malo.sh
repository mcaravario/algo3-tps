# !/bin/bash

# Este script ejecuta la heuristica golosa con el fin de obtener el peso.
# El grafo de entrada es el caso malo.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4

while (($d<$h)); do
	../../../bin/generador_malo $d $k $s | ../../../bin/opt_pgoloso
	let d=$d+1
done
