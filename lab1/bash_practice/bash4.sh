#! /bin/bash

echo "1st Number : "
read x
echo "2nd Number : "
read y
echo "3rd Number : "
read z

result=0
if [ $x -le $y ]; then
	min=$x
	max=$y
else
	min=$y
	max=$x
fi

if [ $min -ge $z ]; then
	min=$z
fi

if [ $max -le $z ]; then
	max=$z
fi

echo "Max : $max"
echo "Min : $min"
