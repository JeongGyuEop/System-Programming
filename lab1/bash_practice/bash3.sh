#! /bin/bash

num1=1
num2=1

for i in $(seq 1 10); do
	if ((${i}<3)); then
		echo "1"
	else
		answer=`expr $num1 + $num2`
		echo $answer
		num2=$num1
		num1=$answer
	fi
done
