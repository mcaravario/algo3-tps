# !/bin/bash

# Corre goloso con los valores ya descriptos en master

d=50
h=200
k=0
s=0
inc=10

while (($d<=$h)); do
	let k=$((d/20))
	let s=$d
	../../bin/grafos_completos $d $k $s | ../busquedalocal/optimalidad/bin/busqueda_local_1opt_aleatorio $s 5 1
	let d=$d+$inc
done
