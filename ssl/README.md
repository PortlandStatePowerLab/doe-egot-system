# SSL-CA
This will server as a portable certificate authority for https clients and servers. **DO NOT USE THESE IN PRODUCTION CODE**

## Resources
- [Great Tutorial](https://www.golinuxcloud.com/openssl-create-client-server-certificate/)
- [Certificate Authority](https://en.wikipedia.org/wiki/Certificate_authority)

## Root CA
- [OpenSSL Cookbook](https://www.feistyduck.com/books/openssl-cookbook/)

```shell
mkdir root-ca
cd root-ca
mkdir certs db private
touch db/index
openssl rand -hex 16 > db/serial
echo 1001 > db/crlnumber
```

### certs
Certificate storage; new certificates will be placed here as they are issued.

### db
This directory is used for the certificate database (index) and the files that hold the
next certificate and CRL serial numbers. OpenSSL will create some additional files as
needed.

### private
This directory will store the private keys, one for the CA and the other for the OCSP
responder. It’s important that no other user has access to it.

*NOTE: When creating a new CA certificate, it’s important to initialize the certificate serial numbers with a random number generator, as I do in this section.*

## Root CA Generation
We take two steps to create the root CA. First, we generate the key and the CSR.

```shell
cd root-ca
openssl req -new \
    -config root-ca.conf \
    -out root-ca.csr \
    -keyout private/root-ca.key
```

In the second step, we create a self-signed certificate.

```shell
cd root-ca
openssl ca -selfsign \
    -config root-ca.conf \
    -in root-ca.csr \
    -out root-ca.crt \
    -extensions ca_ext
```

### Root CA Operations
To generate a CRL from the new CA, use the -gencrl switch of the ca command:

```shell
openssl ca -gencrl \
    -config root-ca.conf \
    -out root-ca.crl
```

To issue a certificate, invoke the ca command with the desired parameters.

```shell
openssl ca \
    -config root-ca.conf \
    -in sub-ca.csr \
    -out sub-ca.crt \
    -extensions sub_ca_ext
```

To revoke a certificate, use the -revoke switch of the ca command.

```shell
openssl ca \
    -config root-ca.conf \
    -revoke certs/1002.pem \
    -crl_reason keyCompromise
```

## Create a Certificate for OCSP Signing
First, we create a key and CSR for the OCSP responder. These two operations are done as for
any non-CA certificate, which is why we don’t specify a configuration file:

```shell
openssl req -new \
    -newkey rsa:2048 \
    -subj "/C=US/O=Portland State University/CN=OCSP Root Responder" \
    -keyout private/root-ocsp.key \
    -out root-ocsp.csr
```

Second, use the root CA to issue a certificate.

```shell
openssl ca \
    -config root-ca.conf \
    -in root-ocsp.csr \
    -out root-ocsp.crt \
    -extensions ocsp_ext \
    -days 30
```

For testing, you can do it from the same machine on which the root CA resides. However, for production you must move the OCSP responder key and certificate elsewhere:

```shell
openssl ocsp \
    -port 9080
    -index db/index \
    -rsigner root-ocsp.crt \
    -rkey private/root-ocsp.key \
    -CA root-ca.crt \
    -text
```

You can test the operation of the OCSP responder using the following command line:

```shell
openssl ocsp \
    -issuer root-ca.crt \
    -CAfile root-ca.crt \
    -cert root-ocsp.crt \
    -url http://127.0.0.1:9080
```

In the output, verify OK means that the signatures were correctly verified, and good means
that the certificate hasn’t been revoked.


## Creating a Subordinate CA
To generate a configuration file for the subordinate CA, start with the file we used for the
root CA and make the changes listed here.

### Subordinate CA Generation
First, we generate the key and the CSR.

```shell
openssl req -new \
    -config sub-ca.conf \
    -out sub-ca.csr \
    -keyout private/sub-ca.key
```

In the second step, we get the root CA to issue a certificate.

```shell
openssl ca \
    -config root-ca.conf \
    -in sub-ca.csr \
    -out sub-ca.crt \
    -extensions sub_ca_ext
```

### Subordinate CA Operations
To issue a server certificate, process a CSR while specifying server_ext in the -extensions
switch:

```shell  
openssl req -new \
    -config sub-ca.conf \
    -out server.csr \
    -keyout private/server.key
```

```shell
openssl ca \
    -config sub-ca.conf \
    -in server.csr \
    -out server.crt \
    -extensions server_ext
```

To issue a client certificate, process a CSR while specifying client_ext in the -extensions
switch:

```shell  
openssl req -new \
    -config sub-ca.conf \
    -out client.csr \
    -keyout private/client.key
```

```shell
openssl ca \
    -config sub-ca.conf \
    -in client.csr \
    -out client.crt \
    -extensions client_ext
```

## Script
- [Example Setup](https://github.com/shehio/Mutual-SSL)
To expidite the CA, Server, adn client generation run the bash script to generate the specified number of client certs:

```shell
cd root-ca
chmod u+x cert_gen.sh
./cert_gen.sh 10
```

## Test Client

```shell
cd certs
openssl s_client -connect localhost:443 -state -debug -cert client1.crt -key client1.key
```