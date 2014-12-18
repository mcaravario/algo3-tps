# !/bin/bash

# Este script experimenta la complejidad de grasp, aumentando la cantidad de iteraciones.
# Parámetros: modo_uso_grasp, cantidad de nodos, k, semilla, iteracion_inicial, iteracion_final
#			incremento, modo_uso_goloso, cant_elegir del goloso

mugrasp=$1
n=$2
k=$3
s=$4
d=$5
h=$6
inc=$7
mugol=$8
cant_elegir=$9
let m=19900

while (($d<=$h)); do
	../../bin/grafos_completos $n $m $k | ../../bin/opt_grasp $s $mugrasp $mugol $d $cant_elegir
	let d=$d+$inc
done
