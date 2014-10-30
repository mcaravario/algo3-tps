# !/bin/bash
# PARAMS: cantidad de vuelos, hora maxima, ini, incremento, cantidad de iteraciones, semilla
CANTIDAD_VUELOS=$1
HORA_MAX=$2
INI=$3
INC=$4
ITERACIONES=$5
SEM=$6

while ((INI<CANTIDAD_VUELOS)); do
        ./gen $INI $HORA_MAX  $SEM | ./ej1test $ITERACIONES $INI
        let INI=$INI+$INC
done


