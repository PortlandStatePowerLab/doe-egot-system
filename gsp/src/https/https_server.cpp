#include "include/https/https_server.hpp"
#include "include/https/server_certificates.hpp"
#include "include/https/send_lambda.hpp"
#include "include/https/handle_request.hpp"
#include <boost/asio/ssl/rfc2818_verification.hpp>

void Fail(beast::error_code ec, char const* what) 
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void DoSession(
    net::ip::tcp::socket& socket,
    ssl::context& ctx,
    std::shared_ptr<std::string> doc_root) 
{
    bool close = false;
    beast::error_code ec;

    // Construct the stream around the socket
    beast::ssl_stream<net::ip::tcp::socket&> stream{socket, ctx};

    // Perform the SSL handshake
    stream.handshake(ssl::stream_base::server, ec);
    if(ec)
        return Fail(ec, "handshake");

    // This buffer is required to persist across reads
    beast::flat_buffer buffer;

    // This lambda is used to send messages
    SendLambda<beast::ssl_stream<net::ip::tcp::socket&>> lambda{stream, close, ec};

    for(;;)
    {
        // Read a request
        http::request<http::string_body> req;
        http::read(stream, buffer, req, ec);
        if(ec == http::error::end_of_stream)
            break;
        if(ec)
            return Fail(ec, "read");

        // Send the response
        HandleRequest(doc_root, std::move(req), lambda);
        if(ec)
            return Fail(ec, "write");
        if(close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            break;
        }
    }

    // Perform the SSL shutdown
    stream.shutdown(ec);
    if(ec)
        return Fail(ec, "shutdown");

    // At this point the connection is closed gracefully
}

HttpsServer::HttpsServer(const std::string &address, uint16_t port, const std::string &doc_root) 
    : address_(address)
    , port_(port)
    , doc_root_(std::make_shared<std::string>(doc_root))
    , io_ctx_(1)
    , ssl_ctx_(boost::asio::ssl::context::tlsv12_server)
    , acceptor_(io_ctx_, {net::ip::make_address(address_), port_})
{
    load_server_certificate(doc_root, ssl_ctx_);
}

HttpsServer::~HttpsServer() 
{
    // do nothing
}

void HttpsServer::Run() 
{
    for(;;)
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
            doc_root_)}.detach();
    }
}