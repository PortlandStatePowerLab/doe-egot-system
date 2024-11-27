#!/bin/bash

cd dtm/scripts/
python3 v2_dtm_server_indie.py&
cd ../../dcm
./build/bin/dcm 
