#!/bin/bash
num_windows="$1"
PORT=1025
num=$num_windows

# Create a new tmux session
tmux new-session -d -s DTMC
tmux new -s GSP -d './build/bin/gsp'
tmux new -s DERS -d 

if [ "$num_windows" = "" ];
then
	echo You must enter the number of clients
else
	n=0
	num=$(($num+1))
	while [ $n -lt $num ];
	do
		tmux new-window -t DERS: "./build/bin/dcm $n $PORT"
		sleep 0.1 
		let n+=1
		PORT=$((PORT + 1))
	done
fi
PORT=1026
# Loop to create multiple windows
for ((i=1; i<=$num_windows; i++)); do
    # Create a new window
    tmux new-window -t DTMC -n "DTMC_$i"

    # Select the current window
    tmux select-window -t DTMC:$i

    # Send the command to the current window
    tmux send-keys -t DTMC:$i "python3 build/bin/dtmc.py $PORT" Enter
    PORT=$((PORT + 1))
done

# Attach to the tmux session
tmux attach-session -t DTMC