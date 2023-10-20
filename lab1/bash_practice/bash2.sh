#! /bin/bash

for i in $(seq 1 9) ; do
	for j in $(seq 1 9) ; do
		result=$((i*j))
		printf "$i X $j = $result\t"
	done
	echo
done	
