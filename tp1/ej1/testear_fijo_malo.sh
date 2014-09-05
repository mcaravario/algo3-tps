# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, proporcion(denominador), cantidad de iteraciones
typeset -i i END
let i=$1 END=$2 INC=$3 

while ((i<END)); do
	let c=$i/$4
	if [c==0]
		then c=1
	fi
	./malo $c $i | ./ej1test $5
	i=$i+$INC
done
