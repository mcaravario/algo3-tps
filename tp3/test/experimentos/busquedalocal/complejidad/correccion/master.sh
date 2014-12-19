# !/bin/bash 

#Este script ejecuta los test de Complejidad de las dos búsquedas locales (1opt-2opt)

# Busqueda Local 1-opt K fijo 5 y N entre [10-150] semilla 13
#./busqueda_local_1opt_run.sh 5 13 10 30 251 1 > test_n_1opt_5_13_10_151_1.txt

# Busqueda Local 2-opt K fijo 5 y N entre [10-150] semilla 13
#./busqueda_local_2opt_run.sh 5 13 10 30 251 1 > test_n_2opt_5_13_10_151_1.txt

# Busqueda Local 1-opt N fijo 250  y K entre [10-150] semilla 13
#./busqueda_local_1opt_run_k.sh 10 13 10 250 201 1 > test2_k_1opt_10_13_10_250_201.txt

# Busqueda Local 2-opt N fijo 250  y K entre [10-150] semilla 13
./busqueda_local_2opt_run_k.sh 10 13 10 250 201 1 > test2_k_2opt_10_13_250_151_1.txt
