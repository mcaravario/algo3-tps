# !/bin/bash
# PARAMS: cantidad de casilleros, cantidad de caballos, ini, incremento, cantidad de iteraciones, semilla
CANTIDAD_CASILLEROS=$1
CANTIDAD_CABALLOS=$2
INI=$3
INC=$4
ITERACIONES=$5
SEM=$6

while ((INI<CANTIDAD_CABALLOS)); do
        ./gen $CANTIDAD_CASILLEROS $INI $SEM | ./ej2test $ITERACIONES
        let INI=$INI+$INC
done


