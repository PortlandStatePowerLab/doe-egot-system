#ifndef __ROOT_CERTIFICATES_H__
#define __ROOT_CERTIFICATES_H__

//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <string>
#include <iostream>

/*
    PLEASE READ
    These root certificates here are included just to make the
    SSL client examples work. They are NOT intended to be
    illustrative of best-practices for performing TLS certificate
    verification.
    A REAL program which needs to verify the authenticity of a
    server IP address resolved from a given DNS name needs to
    consult the operating system specific certificate store
    to validate the chain of signatures, compare the domain name
    properly against the domain name in the certificate, check
    the certificate revocation list, and probably do some other
    things.
    ALL of these operations are entirely outside the scope of
    both Boost.Beast and Boost.Asio.
    See (work in progress):
        https://github.com/djarek/certify
    tl;dr: root_certificates.hpp should not be used in production code
*/

// This is temporary since I was struggling to get rfc 2818 to validate with self
// signed certificates on the localhost.
bool verify_certificate_simple(bool preverified, boost::asio::ssl::verify_context& ctx)
{
    X509_STORE_CTX *cts = ctx.native_handle();
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(cts);
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

    // fingerprint
    const EVP_MD *digest = EVP_get_digestbyname("sha256");
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int n;
    X509_digest(cert, digest, md, &n);

    switch (X509_STORE_CTX_get_error(cts))
    {
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
        std::cout << "the issuer certificate could not be found" << std::endl;
        preverified = false;
        break;
    case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
        std::cout << "the certificate signature could not be decrypted" << std::endl;
        preverified = false;
        break;
    case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
        std::cout << "the public key in the certificate SubjectPublicKeyInfo could not be read" << std::endl;
        preverified = false;
        break;
    case X509_V_ERR_CERT_SIGNATURE_FAILURE:
        std::cout << "the signature of the certificate is invalid" << std::endl;
        preverified = false;
        break;
    case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
        std::cout << "the passed certificate is self signed and the same certificate cannot be found in the list of trusted certificates" << std::endl;
        preverified = false;
        break;
    case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
        //std::cout << "the issuer certificate of a locally looked up certificate could not be found" << std::endl;
        preverified = true;
        break;
    case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
        std::cout << "the current candidate issuer certificate was rejected because its subject name did not match the issuer name of the current certificate" << std::endl;
        preverified = false;
        break;
    default:
        preverified = true;
        break;
    }

    return preverified;
}

namespace detail
{

    inline void
    load_root_certificates(const std::string & id, const std::string & root, boost::asio::ssl::context &ctx, boost::system::error_code &ec)
    {
        ctx.set_verify_mode(boost::asio::ssl::verify_peer);

        ctx.add_verify_path(root + "/certs");

        ctx.use_certificate_file(root + "/client" + id + ".crt" , boost::asio::ssl::context::pem);

        ctx.use_private_key_file(root + "/private/client" + id + ".key", boost::asio::ssl::context::pem);

        ctx.set_verify_callback(
            boost::bind<bool>(verify_certificate_simple, false, boost::placeholders::_2)
        );
    }

} // detail

// Load the root certificates into an ssl::context

inline void
load_root_certificates(const std::string & id, const std::string & root, boost::asio::ssl::context &ctx, boost::system::error_code &ec)
{
    detail::load_root_certificates(id, root, ctx, ec);
}

inline void
load_root_certificates(const std::string & id, const std::string &root, boost::asio::ssl::context &ctx)
{
    boost::system::error_code ec;
    detail::load_root_certificates(id, root, ctx, ec);
    if (ec)
        throw boost::system::system_error{ec};
}

#endif // __ROOT_CERTIFICATES_H__