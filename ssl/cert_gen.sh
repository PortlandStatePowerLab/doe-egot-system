#!/bin/bash
import re
ctr=1
pattern='((:.{2}){20}$)'
reg_file='root-ca/registration.csv'
rm $reg_file
while [ $ctr -le $1 ]
do
FILE=root-ca/client$ctr.crt
if [ -f "$FILE" ]; then
    echo "$FILE exists"
    fingerprint=$(openssl x509 -in $FILE -noout -fingerprint -sha256)
    [[ $fingerprint =~ $pattern ]]
    lfdi="${BASH_REMATCH[0]}"
    lfdi=${lfdi//:}
    echo "$ctr,$lfdi" >> $reg_file
else
    openssl req -new \
        -config sub-ca.conf \
        -out root-ca/client$ctr.csr \
        -keyout root-ca/private/client$ctr.key

    openssl ca -batch\
        -config sub-ca.conf \
        -in root-ca/client$ctr.csr \
        -out root-ca/client$ctr.crt \
        -extensions client_ext

    fingerprint=$(openssl x509 -in $FILE -noout -fingerprint -sha256)
    [[ $fingerprint =~ $pattern ]]
    lfdi="${BASH_REMATCH[0]}"
    lfdi=${lfdi//:}
    echo "$ctr,$lfdi" >> $reg_file
fi
((ctr++))
done
echo All done