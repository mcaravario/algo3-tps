# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, capacidad de salto, cantidad de iteraciones
CANT_PRODUCTOS=$1
UMBRAL=$2
END=$3
INC=$4
ITERACIONES=$5

while ((CANT_PRODUCTOS<END)); do
        ./prom $CANT_PRODUCTOS $UMBRAL | ./ej3test $ITERACIONES
        let CANT_PRODUCTOS=$CANT_PRODUCTOS+$INC
done

