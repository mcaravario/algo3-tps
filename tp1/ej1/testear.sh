# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, capacidad de salto, cantidad de iteraciones
typeset -i i END
let i=$1 END=$2 INC=$3

while ((i<END)); do
	./gen $4 $i | ./ej1test $5
	i=$i+$INC
done
