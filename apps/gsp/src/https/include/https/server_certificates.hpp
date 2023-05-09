#ifndef __SERVER_ROOT_CERTIFICATE_H__
#define __SERVER_ROOT_CERTIFICATE_H__

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
#include <iostream>
#include <sstream>

/*  Load a signed certificate into the ssl context, and configure
    the context for use with a server.
    For this to work with the browser or operating system, it is
    necessary to import the "Beast Test CA" certificate into
    the local certificate store, browser, or operating system
    depending on your environment Please see the documentation
    accompanying the Beast certificate for more details.
*/

inline void
load_server_certificate(const std::string &root, boost::asio::ssl::context &ctx)
{
    ctx.set_verify_mode(boost::asio::ssl::verify_peer | boost::asio::ssl::verify_fail_if_no_peer_cert);
    ctx.add_verify_path(root + "/root-ca/certs");
    ctx.use_certificate_file(root + "/root-ca/server.crt", boost::asio::ssl::context::pem);
    ctx.use_private_key_file(root + "/root-ca/private/server.key", boost::asio::ssl::context::pem);
    ctx.set_options(
        boost::asio::ssl::context::default_workarounds |
        boost::asio::ssl::context::single_dh_use);

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

#endif // __SERVER_ROOT_CERTIFICATE_H__