# !/bin/bash
# Itera sobre la cantidad de conjuntos.
# PARAMS: n (cantidad de nodos), s (semilla), i (iteraciones), d (cantidad inicial de nodos), h (cantidad final de nodos), inc (incremento)
n=$1
s=$2
i=$3
d=$4
h=$5
inc=$6

while (($d<$h)); do
				../../bin/generador_grafo $n $d $s | ../../bin/golosot $i
        let d=$d+$inc

done
