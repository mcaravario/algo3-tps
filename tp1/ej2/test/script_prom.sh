# !/bin/bash
# PARAMS: cantidad de edificios, ini, incremento, cantidad de iteraciones, semilla
CANTIDAD_ED=$1
INI=$2
INC=$3
ITERACIONES=$4
SEM=$5

while ((INI<CANTIDAD_ED)); do
        ./gen $INI $SEM | ./ej2test $ITERACIONES $INI
        let INI=$INI+$INC
done


