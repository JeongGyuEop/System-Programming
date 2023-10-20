#! /bin/bash

echo "Test Command"
filelist=($(ls))

for i in ${filelist[@]} ; do
	if [ -f $i ] ; then
		echo $i
	fi
done
