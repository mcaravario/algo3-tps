# !/bin/bash

# Corre goloso con los valores ya descriptos en master

d=50
h=200
k=0
s=0
inc=10
divisor=25
p=0

while (($d<=$h)); do
	let k=$((d/20))
	let s=$d
	let p=$((d/divisor))
	../../bin/grafos_completos $d $k $s | ../../bin/opt_grasp $s 1 1 5 $p
	let d=$d+$inc
done
