#ifndef __HTTPS_SERVER_SESSION_H__
#define __HTTPS_SERVER_SESSION_H__

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "handle_request.hpp"

// Handles an HTTP server connection
class Session
    : public boost::asio::coroutine
    , public std::enable_shared_from_this<Session>
{
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        Session& self_;

        explicit
        send_lambda(Session& self)
            : self_(self)
        {
        }

        template<bool isRequest, class Body, class Fields>
        void
        operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<isRequest, Body, Fields>>(std::move(msg));

            // Store a type-erased version of the shared
            // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.stream_,
                *sp,
                std::bind(
                    &Session::loop,
                    self_.shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2,
                    sp->need_eof()));
        }
    };

    beast::ssl_stream<beast::tcp_stream> stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<const std::string> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;
    std::string fingerprint_;

public:
    // Take ownership of the socket
    explicit
    Session(
        boost::asio::ip::tcp::socket&& socket,
        boost::asio::ssl::context& ctx,
        std::shared_ptr<std::string const> const& doc_root)
        : stream_(std::move(socket), ctx)
        , doc_root_(doc_root)
        , lambda_(*this)
    {
        stream_.set_verify_callback(
            boost::bind<bool>(&Session::IDVerifyCallback, this, false, boost::placeholders::_2));
    }

    // Start the asynchronous operation
    void
    run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this Session.Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        net::dispatch(stream_.get_executor(),
                      beast::bind_front_handler(&Session::loop,
                                                shared_from_this(),
                                                beast::error_code{},
                                                0,
                                                false));
    }

    bool IDVerifyCallback (bool preverified, boost::asio::ssl::verify_context &ctx)
    {
        X509_STORE_CTX *cts = ctx.native_handle();
        X509 *cert = X509_STORE_CTX_get_current_cert(cts);

        // fingerprint
        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int n;
        X509_digest(cert, EVP_sha256(), md, &n);

        // 40 hex character length for fingerprint
        std::ostringstream oss;
        for (size_t i = 0; i < n; i++)
        {
            oss << std::hex << (int)md[i];
        };
        
        fingerprint_ = oss.str().substr(0, 40);

        // This switch will capture all errors we find relavent and if
        // they are not found then we verify the certificate.
        switch (X509_STORE_CTX_get_error(cts))
        {
        case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
            std::cout << "the certificate signature could not be decrypted" << std::endl;
            break;
        case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
            std::cout << "the public key in the certificate SubjectPublicKeyInfo could not be read" << std::endl;
            break;
        case X509_V_ERR_CERT_SIGNATURE_FAILURE:
            std::cout << "the signature of the certificate is invalid" << std::endl;
            break;
        case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
            std::cout << "the passed certificate is self signed and the same certificate cannot be found in the list of trusted certificates" << std::endl;
            break;
        case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
            std::cout << "the current candidate issuer certificate was rejected because its subject name did not match the issuer name of the current certificate" << std::endl;
            break;
        default:
            preverified = true;
            break;
        }
        return preverified;
    };

    void fail(boost::beast::error_code ec, char const *what)
    {
        // ssl::error::stream_truncated, also known as an SSL "short read",
        // indicates the peer closed the connection without performing the
        // required closing handshake (for example, Google does this to
        // improve performance). Generally this can be a security issue,
        // but if your communication protocol is self-terminated (as
        // it is with both HTTP and WebSocket) then you may simply
        // ignore the lack of close_notify.
        //
        // https://github.com/boostorg/beast/issues/38
        //
        // https://security.stackexchange.com/questions/91435/how-to-handle-a-malicious-ssl-tls-shutdown
        //
        // When a short read would cut off the end of an HTTP message,
        // Beast returns the error beast::http::error::partial_message.
        // Therefore, if we see a short read here, it has occurred
        // after the message has been completed, so it is safe to ignore it.

        if (ec == boost::asio::ssl::error::stream_truncated)
            return;

        std::cerr << what << ": " << ec.message() << "\n";
    }

    #include <boost/asio/yield.hpp>

    void
    loop(
        beast::error_code ec,
        std::size_t bytes_transferred,
        bool close)
    {
        boost::ignore_unused(bytes_transferred);
        reenter(*this)
        {
            // Set the timeout.
            beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

            // Perform the SSL handshake
            yield stream_.async_handshake(
                ssl::stream_base::server,
                std::bind(
                    &Session::loop,
                    shared_from_this(),
                    std::placeholders::_1,
                    0,
                    false));

            if(ec)
                return fail(ec, "handshake");

            for(;;)
            {
                // Set the timeout.
                beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

                // Make the request empty before reading,
                // otherwise the operation behavior is undefined.
                req_ = {};

                // Read a request
                yield http::async_read(stream_, buffer_, req_,
                    std::bind(
                        &Session::loop,
                        shared_from_this(),
                        std::placeholders::_1,
                        std::placeholders::_2,
                        false));
                if(ec == http::error::end_of_stream)
                {
                    // The remote host closed the connection
                    break;
                }
                if(ec)
                    return fail(ec, "read");

                // Send the response
                yield HandleRequest(fingerprint_, doc_root_, std::move(req_), lambda_);
                if(ec)
                    return fail(ec, "write");
                if(close)
                {
                    // This means we should close the connection, usually because
                    // the response indicated the "Connection: close" semantic.
                    break;
                }

                // We're done with the response so delete it
                res_ = nullptr;
            }

            // Set the timeout.
            beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

            // Perform the SSL shutdown
            yield stream_.async_shutdown(
                std::bind(
                    &Session::loop,
                    shared_from_this(),
                    std::placeholders::_1,
                    0,
                    false));
            if(ec)
                return fail(ec, "shutdown");

            // At this point the connection is closed gracefully
        }
    }

    #include <boost/asio/unyield.hpp>
};

#endif // __HTTPS_SERVER_SESSION_H__