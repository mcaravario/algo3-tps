# !/bin/bash

# Este script ejecuta el algoritmo exacto con el fin de obtener el peso.
# El grafo de entrada es el caso malo. Se generan varias instancias de grafos del mismo tamaño.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4

while (($d<=$h)); do
	../../../bin/generador_malo $d $k $s | ../../../bin/opt_pexacto
	let d=$d+1
