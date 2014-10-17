# !/bin/bash
# PARAMS: cantidad de casilleros, cantidad de caballos, ini, incremento, cantidad de iteraciones, semilla
CANTIDAD_CASILLEROS=$1
CANTIDAD_CABALLOS=$2
INI=$3
INC=$4
ITERACIONES=$5
SEM=$6

while ((INI<CANTIDAD_CASILLEROS)); do
        ./gen $INI $CANTIDAD_CABALLOS $SEM | ./ej2test $ITERACIONES $INI
        let INI=$INI+$INC
done
