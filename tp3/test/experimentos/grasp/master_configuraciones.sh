# !/bin/bash

# Probaremos las 4 posibilidades de combinar criterios para  grasp y goloso aleatorio.
# En cada posibilidad variaremos las variables, para así experimentar todo.

#00 k-it fijas y elegir entre bolsas
./run_grasp_k.sh 200 500 20 13 0 0 10 5 > grasp.00.10.5.out
./run_grasp_k.sh 200 500 20 13 0 0 100 5 > grasp.00.100.5.out
./run_grasp_k.sh 200 500 20 13 0 0 10 10 > grasp.00.10.10.out
./run_grasp_k.sh 200 500 20 13 0 0 100 10 > grasp.00.100.10.out

#01 k-it fijas y elegir entre nodos
./run_grasp_n.sh 200 500 20 13 0 1 10 20 > grasp.01.10.20.out
./run_grasp_n.sh 200 500 20 13 0 1 100 20 > grasp.01.100.20.out
./run_grasp_n.sh 200 500 20 13 0 1 10 40 > grasp.01.10.40.out
./run_grasp_n.sh 200 500 20 13 0 1 100 40 > grasp.01.100.40.out

#10 no hay mejora en k-it y elegir entre bolsas
./run_grasp_k.sh 200 500 20 13 1 0 5 5 > grasp.10.25.5.out
./run_grasp_k.sh 200 500 20 13 1 0 25 5 > grasp.10.100.5.out
./run_grasp_k.sh 200 500 20 13 1 0 5 10 > grasp.10.25.10.out
./run_grasp_k.sh 200 500 20 13 1 0 25 10 > grasp.10.100.10.out

#11 no hay mejora en k-it y elegir entre nodos
./run_grasp_n.sh 200 500 20 13 1 1 5 20 > grasp.11.25.20.out
./run_grasp_n.sh 200 500 20 13 1 1 25 20 > grasp.11.100.20.out
./run_grasp_n.sh 200 500 20 13 1 1 5 40 > grasp.11.25.40.out
./run_grasp_n.sh 200 500 20 13 1 1 25 40 > grasp.11.100.40.out
