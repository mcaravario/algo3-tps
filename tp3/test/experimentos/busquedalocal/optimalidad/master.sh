# !/bin/bash

# Este script ejecuta los test de Comparacion entre las dos búsquedas locales (1opt-2opt)

#>>>  Resultado Aleatorio
# Fijaremos k = 2,3,4 y variaremos el n = [5,22]
./run_aleatorio.sh 2 5 23 20 > blocal.rand.k2.out
./run_aleatorio.sh 3 5 23 20 > blocal.rand.k3.out
./run_aleatorio.sh 4 5 23 20 > blocal.rand.k4.out

#>>>  Caso Malo
# Fijaremos k = 2,3,4 y variaremos el n = [5,22]
./run_malo.sh 2 5 23 13 > blocal.malo.k2.out
./run_malo.sh 3 5 23 13 > blocal.malo.k3.out
./run_malo.sh 4 5 23 13 > blocal.malo.k4.out

