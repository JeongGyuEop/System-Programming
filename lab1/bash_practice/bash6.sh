#! /bin/bash

for i in 5 4 3 2 1

	do

	for ((j=$i; j>0; j--)) do
	echo -n "*"
	done
	echo
done
