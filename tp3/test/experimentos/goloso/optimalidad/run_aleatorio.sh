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
	../../../bin/generador_grafo_aristas $d $m $k $s | ../../../bin/opt_pgoloso
	let d=$d+1
done
