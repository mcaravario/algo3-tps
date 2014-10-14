# !/bin/bash
# PARAMS: cantidad de tablones ini,cantidad de tablones hasta,tablones incremento, capacidad de salto, cantidad de iteraciones
CANT_TABLONES=$1
END=$3
INC=$4
ITERACIONES=$5

while ((CANT_TABLONES<END)); do
        ./prom $CAPACIDAD_SALTO $CANT_TABLONES | ./ej1test $ITERACIONES
        let CANT_TABLONES=$CANT_TABLONES+$INC
done

