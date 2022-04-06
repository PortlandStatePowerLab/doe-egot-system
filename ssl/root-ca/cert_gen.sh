#!/bin/bash
ctr=1
while [ $ctr -le $1 ]
do
openssl req -new \
    -config sub-ca.conf \
    -out client$ctr.csr \
    -keyout private/client$ctr.key

openssl ca -batch\
    -config sub-ca.conf \
    -in client$ctr.csr \
    -out client$ctr.crt \
    -extensions client_ext

((ctr++))
done
echo All done