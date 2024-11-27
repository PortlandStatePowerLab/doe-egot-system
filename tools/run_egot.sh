#!/bin/bash

num="$1"

if [ "$num" = "" ];
then
	echo You must enter the number of clients
else
	tmux new -s ME -d 'python3 build/bin/me.py'
	tmux new -s GSP -d './build/bin/gsp'
	tmux new -s DTMC -d 'python3 build/bin/dtmc.py'
	tmux new -s DERS -d 
	sleep 1
	n=1
	num=$(($num+1))
	while [ $n -lt $num ];
	do
		tmux new-window -t DERS: "./build/bin/dcm $n"
		sleep 0.1 
		let n+=1
	done
fi