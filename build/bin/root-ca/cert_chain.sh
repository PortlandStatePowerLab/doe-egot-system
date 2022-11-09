#!/bin/bash
files="client*.crt"
for file in $files
do 
    openssl x509 -in $file >> certs.crt
done