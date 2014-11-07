# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, capacidad de salto, cantidad de iteraciones
NODOS=$1
END=$2
INC=$3
ITERACIONES=$4

while ((NODOS<END)); do
	let CUENTA1=$NODOS-1
	let CUENTA2=$CUENTA1\*$NODOS
	let ARISTAS=$CUENTA2/2
    ./prom $NODOS $ARISTAS | ./ej3test $ITERACIONES
    let NODOS=$NODOS+$INC
done

