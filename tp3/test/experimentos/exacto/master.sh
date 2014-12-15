# !/bin/bash
# Script encargado de correr el experimento
# Llama a los scrips que miden tiempos.

# Sin poda
#./exacto_run_n.sh 2 13 5 6 28 1 > ek2.out
./exacto_run_n.sh 3 13 5 6 28 1 > ek3.out
./exacto_run_n.sh 4 13 5 6 28 1 > ek4.out


# Con poda
./pexacto_run_n.sh 2 13 5 6 28 1 > pek2.out
./pexacto_run_n.sh 3 13 5 6 28 1 > pek3.out
./pexacto_run_n.sh 4 13 5 6 28 1 > pek4.out
