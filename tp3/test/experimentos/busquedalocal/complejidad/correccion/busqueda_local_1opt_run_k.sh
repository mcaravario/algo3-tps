# !/bin/bash
# Itera sobre la cantidad de conjuntos.
# PARAMS: k (cantidad de conjuntos), s (semilla), i (iteraciones), d (cantidad inicial de nodos), h (cantidad final de nodos), inc (incremento)
k=$1
s=$2
i=$3
d=$4
h=$5
inc=$6

while (($k<$h)); do
	../../../../bin/grafos_completos $d $k $s | ../../../../bin/busqueda_local_1opt_aleatorio $s $i 
  let k=$k+$inc

done
