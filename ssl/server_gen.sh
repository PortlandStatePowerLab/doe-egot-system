openssl req -new \
    -config sub-ca.conf \
    -out root-ca/server.csr \
    -keyout root-ca/private/server.key

openssl ca \
    -config sub-ca.conf \
    -in root-ca/server.csr \
    -out root-ca/server.crt \
    -extensions server_ext