# !/bin/bash

# Este script ejecuta la heuristica grasp con el fin de obtener el peso y el tiempo de ejecucion.
# El grafo de entrada es aleatorio, pero con cantidad de aristas que depende la #nodos.
# Recibe como parámetros:
#			- #nodos_inicial, #nodos_final, incremento, semilla, modo_uso_grasp, modo_uso_goloso, it_grasp, cant_elegir (para el goloso)
# k es n/25
k=0
d=$1
h=$2
inc=$3
s=$4
mugrasp=$5
mugol=$6
it_grasp=$7
cant_elegir=$8
divisor=20
proporcion=0

while (($d<=$h)); do
	let	k=$((d/divisor))
	let proporcion=$((d/cant_elegir))
	echo $k; echo $d; echo $cant_elegir; echo $proporcion
	../../../bin/grafos_completos $d $k $s | ../../../bin/opt_grasp $s $mugrasp $mugol $it_grasp $proporcion
	let d=$d+$inc
done
