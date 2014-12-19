# !/bin/bash

# Este script ejecuta el algoritmo exacto con el fin de obtener el peso.
# El grafo de entrada es completo. Se generan varias instancias de grafos.
# Recibe como parámetros:
#			- k, #nodos_inicial, #nodos_final, #iteraciones, semilla

k=$1
d=$2
h=$3
s=$4

while (($d<$h)); do
	let CUENTA1=$d\*$d
	let CUENTA2=$CUENTA1-$d
	let m=$CUENTA2/2
	./bin/grafos_completos $d $m $k | ../../../bin/opt_pexacto
	let d=$d+1
 done
