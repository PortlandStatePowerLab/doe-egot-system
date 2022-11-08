openssl req -new \
    -config root-ca.conf \
    -out root-ca/root-ca.csr \
    -keyout root-ca/private/root-ca.key

openssl ca -selfsign \
    -config root-ca.conf \
    -in root-ca/root-ca.csr \
    -out root-ca/root-ca.crt \
    -extensions ca_ext

openssl req -new \
    -config sub-ca.conf \
    -out root-ca/sub-ca.csr \
    -keyout root-ca/private/sub-ca.key

openssl ca \
    -config root-ca.conf \
    -in root-ca/sub-ca.csr \
    -out root-ca/sub-ca.crt \
    -extensions sub_ca_ext