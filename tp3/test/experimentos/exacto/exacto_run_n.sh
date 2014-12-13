# !/bin/bash
# Itera sobre la cantidad de conjuntos.
# PARAMS: k (cantidad de conjuntos), s (semilla), i (iteraciones), d (cantidad inicial de nodos), h (cantidad final de nodos), inc (incremento)
k=$1
s=$2
i=$3
d=$4
h=$5
inc=$6

while (($d<$h)); do
				../../bin/generador_grafo $d $k $s | ../../bin/exacto
        let d=$d+$inc

done
