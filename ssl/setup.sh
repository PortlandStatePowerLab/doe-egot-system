mkdir -p root-ca/certs root-ca/db root-ca/private
touch root-ca/db/index
openssl rand -hex 16 > root-ca/db/serial
echo 1001 > root-ca/db/crlnumber