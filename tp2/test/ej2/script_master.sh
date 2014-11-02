# !/bin/bash
# Este script pone a correr a los dos test

./script_caballos.sh 50 500 10 15 25 1 > test_c_1.out
./script_caballos.sh 200 500 10 15 25 1 > test_c_2.out

./script_tablero.sh 500 50 10 15 25 1 > test_t_1.out
./script_tablero.sh 500 200 10 15 25 1 > test_t_2.out



