#!/bin/bash
import re
ctr=1
pattern='((:.{2}){20}$)'
reg_file='root-ca/registration.csv'
area_idx=0
areas=(680 633 632 692 675 671 684 652 680 633 632 692 675 671 645 680 633 632 692 675 671 684 611)
rm $reg_file
while [ $ctr -le $1 ]
do
FILE=root-ca/client$ctr.crt
if [[ $(($ctr % 40)) -eq 0 ]]; then
    ((area_idx++))
fi
if [ -f "$FILE" ]; then
    echo "$FILE exists"
    fingerprint=$(openssl x509 -in $FILE -noout -fingerprint -sha256)
    [[ $fingerprint =~ $pattern ]]
    lfdi="${BASH_REMATCH[0]}"
    lfdi=${lfdi//:}
    echo "$ctr,$lfdi,${areas[$area_idx]}">> $reg_file
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
    echo "$ctr,$lfdi,${areas[$area_idx]}">> $reg_file
fi
((ctr++))
done
echo All done