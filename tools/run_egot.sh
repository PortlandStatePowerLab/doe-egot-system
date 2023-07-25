#!/bin/bash

num="$1"

tmux new -s GSP -d './build/bin/gsp'
tmux new -s DTMC -d 'python3 build/bin/dtmc.py'
tmux new -s CLASSIFIER -d 'python3 build/bin/classifier.py'
tmux new -s CDTA -d 'python3 build/bin/cdta.py'
tmux new -s DTMC -d 'python3 build/bin/dtmc.py'
tmux new -s DERS -d 

if [ "$num" = "" ];
then
	echo You must enter the number of clients
else
	n=1
	num=$(($num+1))
	while [ $n -lt $num ];
	do
		tmux new-window -t DERS: "./build/bin/dcm $n"
		sleep 0.1 
		let n+=1
	done
fi