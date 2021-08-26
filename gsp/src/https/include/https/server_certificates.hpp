#ifndef __ROOT_CERTIFICATE_H__
#define __ROOT_CERTIFICATE_H__

//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <cstddef>
#include <memory>

/*  Load a signed certificate into the ssl context, and configure
    the context for use with a server.
    For this to work with the browser or operating system, it is
    necessary to import the "Beast Test CA" certificate into
    the local certificate store, browser, or operating system
    depending on your environment Please see the documentation
    accompanying the Beast certificate for more details.
*/



// This is temporary since I was struggling to get rfc 2818 to validate with self
// signed certificates on the localhost.
static bool verify_certificate_simple(bool preverified, boost::asio::ssl::verify_context& ctx)
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
    case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
        std::cout << "the current candidate issuer certificate was rejected because its subject name did not match the issuer name of the current certificate" << std::endl;
        preverified = false;
        break;
    default:
        //std::cout << "error: " <<  X509_STORE_CTX_get_error(cts) << std::endl;
        preverified = true;
        break;
    }
}

inline void
load_server_certificate(const std::string &root, ssl::context &ctx)
{
    ctx.set_verify_mode(ssl::verify_peer|ssl::verify_fail_if_no_peer_cert);
    ctx.add_verify_path(root + "/certs/certs");
    ctx.use_certificate_file(root + "/certs/server.crt", ssl::context::pem);
    ctx.use_private_key_file(root + "/certs/private/server.key", ssl::context::pem);
    ctx.set_options(
      boost::asio::ssl::context::default_workarounds |
      boost::asio::ssl::context::single_dh_use
    );

    ctx.set_verify_callback(
        boost::bind(&verify_certificate_simple, true, _2)
    );

    std::string const dh =
        "-----BEGIN DH PARAMETERS-----\n"
        "MIIBCAKCAQEArzQc5mpm0Fs8yahDeySj31JZlwEphUdZ9StM2D8+Fo7TMduGtSi+\n"
        "/HRWVwHcTFAgrxVdm+dl474mOUqqaz4MpzIb6+6OVfWHbQJmXPepZKyu4LgUPvY/\n"
        "4q3/iDMjIS0fLOu/bLuObwU5ccZmDgfhmz1GanRlTQOiYRty3FiOATWZBRh6uv4u\n"
        "tff4A9Bm3V9tLx9S6djq31w31Gl7OQhryodW28kc16t9TvO1BzcV3HjRPwpe701X\n"
        "oEEZdnZWANkkpR/m/pfgdmGPU66S2sXMHgsliViQWpDCYeehrvFRHEdR9NV+XJfC\n"
        "QMUk26jPTIVTLfXmmwU0u8vUkpR7LQKkwwIBAg==\n"
        "-----END DH PARAMETERS-----\n";

    // use custom verify_callback here for debugging purposes

    ctx.use_tmp_dh(
        boost::asio::buffer(dh.data(), dh.size()));
}

#endif // __ROOT_CERTIFICATE_H__