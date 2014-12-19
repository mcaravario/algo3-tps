# !/bin/bash

# Este script corre los experimentos de complejidad, un experimento por cada criterio.
# Se usa un grafo completo con n = 200,  k = 10.
# El modo de uso de goloso es 1, y el cant_elegir es 10.

# K-iteraciones fijas, irán de 1 a 300, incrementando de a 1
#./complejidad_iteraciones.sh 0 200 10 13 1 300 1 1 10 > grasp.compl.0.out


# K-iteraciones sin mejoras, irán de 1 a 300, incrementando de a 1
./complejidad_iteraciones.sh 1 200 10 13 1 300 1 1 10 > grasp.compl.1.out
