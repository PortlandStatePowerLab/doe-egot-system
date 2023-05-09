 #!/bin/bash
tmux new-session -s EGoT \;\
split-window -h \;\
split-window -h send-keys './build/bin/gsp' \;\
select-layout even-horizontal \;
