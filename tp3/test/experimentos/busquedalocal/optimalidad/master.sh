# !/bin/bash

# Este script ejecuta los test de Comparacion entre las dos búsquedas locales (1opt-2opt)

#>>>  Resultado Aleatorio
# Fijaremos k = 2,3,4 y variaremos el n = [5,20]
./run_aleatorio.sh 2 5 20 13 > blocal.rand.k2.txt
./run_aleatorio.sh 3 5 20 13 > blocal.rand.k3.txt
./run_aleatorio.sh 4 5 20 13 > blocal.rand.k4.txt

#>>>  Resultado con Arista costosa en un conjunto
# Fijaremos k = 2,3,4 y variaremos el n = [5,20]
./run_costosa_en_conjunto.sh 2 5 20 13 > blocal.costosa.k2.txt
./run_costosa_en_conjunto.sh 3 5 20 13 > blocal.costosa.k3.txt
./run_costosa_en_conjunto.sh 4 5 20 13 > blocal.costosa.k4.txt

#Genero resultados con el exacto para las mismas instancias (para comparar)
./run_exacto_aleatorio.sh 2 5 20 13 > exacto.rand.k2.txt
./run_exacto_aleatorio.sh 3 5 20 13 > exacto.rand.k3.txt
./run_exacto_aleatorio.sh 4 5 20 13 > exacto.rand.k4.txt
