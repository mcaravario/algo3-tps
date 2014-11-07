# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, capacidad de salto, cantidad de iteraciones
NODOS=$1
END=$2
INC=$3
ITERACIONES=$4

while ((NODOS<END)); do
	let ARISTAS=$NODOS
    ./prom $NODOS $ARISTAS | ./ej3test $ITERACIONES
    let NODOS=$NODOS+$INC
done

