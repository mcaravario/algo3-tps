# !/bin/bash
# PARAMS: cantidad de edificios, ini, incremento, cantidad de iteraciones
CANTIDAD_ED=$1
INI=$2
INC=$3
ITERACIONES=$4

while ((INI<CANTIDAD_ED)); do
        ./gen $INI | ./ej2test $ITERACIONES
        let INI=$INI+$INC
done


