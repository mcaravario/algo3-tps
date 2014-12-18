# !/bin/bash

# Este script ejecuta las heuristica busquedalocal 1-opt y 2-opt con el fin de obtener el peso y el tiempo.
# El grafo es completo y el resultado de entrada es aleatorio.
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
	./bin/grafos_completos $d $m $k | ./bin/busqueda_local_1opt_aleatorio 13 15 1
	./bin/grafos_completos $d $m $k | ./bin/busqueda_local_2opt_aleatorio 13 15 1
	let d=$d+1
done
