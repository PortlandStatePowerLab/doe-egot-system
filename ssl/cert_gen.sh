#!/bin/bash
ctr=1
while [ $ctr -le $1 ]
do
openssl req -new \
    -config sub-ca.conf \
    -out root-ca/client$ctr.csr \
    -keyout root-ca/private/client$ctr.key

openssl ca -batch\
    -config sub-ca.conf \
    -in root-ca/client$ctr.csr \
    -out root-ca/client$ctr.crt \
    -extensions client_ext

((ctr++))
done
echo All done