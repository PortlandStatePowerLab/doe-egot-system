#!/bin/bash
files="root-ca/client*.crt"
for file in $files
do 
    openssl x509 -in $file >> root-ca/cert_chain.crt
done