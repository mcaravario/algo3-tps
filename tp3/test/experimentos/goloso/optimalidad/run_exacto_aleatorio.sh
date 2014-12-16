# !/bin/bash

# Este script ejecuta el algoritmo exacto con el fin de obtener el peso.
# El grafo de entrada es aleatorio. Se generan varias instancias de grafos.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4

while (($d<=$h)); do
	../../../bin/generador_grafo_aristas $d (($d*2)) $k $s | ../../../bin/opt_pexacto
	let d=$d+1
