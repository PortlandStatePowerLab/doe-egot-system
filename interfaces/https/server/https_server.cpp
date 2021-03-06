#define BOOST_BIND_GLOBAL_PLACEHOLDERS // had to to remove boost warning
#include "include/https/https_server.hpp"
#include "include/https/server_certificates.hpp"
#include "include/https/send_lambda.hpp"
#include "include/https/handle_request.hpp"
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <world/world.hpp>
#include <xml/adapter.hpp>
#include <ieee-2030.5/models.hpp>
#include <fstream>
#include <boost/asio/ssl.hpp>
#include <boost/bind/bind.hpp>
#include <boost/filesystem.hpp>
#include <utilities/utilities.hpp>

void Fail(beast::error_code ec, char const *what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void DoSession(
    net::ip::tcp::socket &socket,
    ssl::context &ctx,
    std::shared_ptr<std::string> doc_root)
{
    bool close = false;
    beast::error_code ec;

    // Perform the SSL handshake
    std::string fingerprint;

    // This is temporary since I was struggling to get rfc 2818 to validate with self
    // signed certificates on the localhost.
    auto VerifyCallback = [&fingerprint](bool preverified, boost::asio::ssl::verify_context &ctx) mutable
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
        fingerprint = oss.str().substr(0, 40);

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

    ctx.set_verify_callback(
        boost::bind<bool>(VerifyCallback, false, boost::placeholders::_2));

    // Construct the stream around the socket
    beast::ssl_stream<net::ip::tcp::socket &> stream{socket, ctx};

    stream.handshake(ssl::stream_base::server, ec);
    if (ec)
        return Fail(ec, "handshake");

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    SendLambda<beast::ssl_stream<net::ip::tcp::socket &>> lambda{stream, close, ec};

    while (true)
    {
        // Read a request
        http::request<http::string_body> req;
        http::read(stream, buffer, req, ec);
        if (ec == http::error::end_of_stream)
            break;
        if (ec)
            return Fail(ec, "read");

        // Send the response
        HandleRequest(fingerprint, doc_root, std::move(req), lambda);
        if (ec)
            return Fail(ec, "write");
        if (close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            break;
        }
    }

    // Perform the SSL shutdown
    stream.shutdown(ec);
    if (ec)
        return Fail(ec, "shutdown");

    // At this point the connection is closed gracefully
}

HttpsServer::HttpsServer(const std::string &address, uint16_t port, const std::string &doc_root)
    : stop(false), address_(address), port_(port), doc_root_(std::make_shared<std::string>(doc_root)), io_ctx_(1), ssl_ctx_(boost::asio::ssl::context::tlsv12_server), acceptor_(io_ctx_, {net::ip::make_address(address_), port_})
{
    load_server_certificate(doc_root, ssl_ctx_);
}

HttpsServer::~HttpsServer()
{
    // do nothing
}

void HttpsServer::Run()
{
    while (!stop)
    {
        // This will receive the new connection
        net::ip::tcp::socket socket{io_ctx_};

        // Block until we get a connection
        acceptor_.accept(socket);

        // Launch the session, transferring ownership of the socket
        std::thread{std::bind(
                        &DoSession,
                        std::move(socket),
                        std::ref(ssl_ctx_),
                        doc_root_)}
            .detach();
    }
}

void HttpsServer::Stop()
{
    stop = true;
    io_ctx_.stop();
    acceptor_.close();
}