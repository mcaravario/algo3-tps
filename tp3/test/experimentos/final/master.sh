# !/bin/bash

# Experimento comparativo final, sin exacto
# Corre grafos completos, n=[50,200], k=n/20, s=n

./run_goloso.sh > goloso.final.out
./run_local1.sh > local1.final.out
./run_local2.sh > local2.final.out
./run_grasp.sh > grasp.final.out
