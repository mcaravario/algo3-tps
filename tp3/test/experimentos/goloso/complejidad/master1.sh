# !/bin/bash
# Este script realiza llos experimentos de verificación de complejidad del goloso.
# Ésto es, ver lineal en k, y ver cuadrático en n.

######## Testeo con grafos aleatorios #############
# Cuadrático en n.
<<<<<<< HEAD
./goloso_run_n.sh 3 13 15 10 10000 100 > r_k3.out
./goloso_run_n.sh 50 13 15 10 10000 100 > r_k50.out
./goloso_run_n.sh 100 13 15 10 10000 100 > r_k100.out

# Lineal en k.
./goloso_run_k.sh 100 13 15 10 10000 100 > r_n100.out
./goloso_run_k.sh 1000 13 15 10 10000 100 > r_n1000.out
./goloso_run_k.sh 10000 13 15 10 10000 100 > r_n10000.out

######## Testeo con casos malos  #############

./goloso_malo_n.sh 3 13 15 10 10000 100 > m_k3.out
./goloso_malo_n.sh 50 13 15 10 10000 100 > m_k50.out
./goloso_malo_n.sh 100 13 15 10 10000 100 > m_k100.out

# Lineal en k.
./goloso_malo_k.sh 100 13 15 10 10000 100 > m_n100.out
./goloso_malo_k.sh 1000 13 15 10 10000 100 > m_n1000.out
./goloso_malo_k.sh 10000 13 15 10 10000 100 > m_n10000.out


=======
./goloso_run_n.sh 10 13 15 100 10000 100 > k3.out
./goloso_run_n.sh 50 13 15 100 10000 100 > k50.out
./goloso_run_n.sh 100 13 15 100 10000 100 > k100.out

# Lineal en k.
./goloso_run_k.sh 1000 13 15 10 1000 10 > n1000.out
./goloso_run_k.sh 10000 13 15 10 1000 10 > n10000.out
>>>>>>> 5f6f7bd3060cdf04d2ebd9c7e9757936f20f1b21
