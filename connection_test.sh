#!/bin/bash
#run lots of simulated DCM
num="$1"

if [ "$num" = "" ];
then
	echo You must enter the number of clients
else
	n=1
	num=$(($num+1))
	while [ $n -lt $num ];
	do
		./build/bin/ScalingClient $n &
		let n+=1
	done
fi

