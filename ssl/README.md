# SSL-CA
This will server as a portable certificate authority for https clients and servers. **DO NOT USE THESE IN PRODUCTION CODE**

## Resources
- [Great Tutorial](https://www.golinuxcloud.com/openssl-create-client-server-certificate/)
- [Certificate Authority](https://en.wikipedia.org/wiki/Certificate_authority)
- [OpenSSL Cookbook](https://www.feistyduck.com/books/openssl-cookbook/)

## Setup
Create the ssl directory structure and seed db index and crlnumber.

```shell
./setup.sh
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

```shell
./ca_gen.sh
```

### Root CA Operations
To revoke a certificate, use the -revoke switch of the ca command.

```shell
openssl ca \
    -config root-ca.conf \
    -revoke root-ca/certs/1002.pem \
    -crl_reason keyCompromise
```

### Subordinate CA Operations

```shell 
./server_gen.sh
```

## Script
- [Example Setup](https://github.com/shehio/Mutual-SSL)
To expidite the CA, Server, adn client generation run the bash script to generate the specified number of client certs:

```shell
cert_gen.sh 10
```

## Test Client

```shell
cd certs
openssl s_client -connect localhost:443 -state -debug -cert client1.crt -key client1.key
```