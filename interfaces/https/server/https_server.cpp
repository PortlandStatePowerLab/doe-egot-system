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

#include "include/https/listener.hpp"
#include "include/https/session.hpp"

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

HttpsServer::HttpsServer(const std::string &address, uint16_t port, const std::string &doc_root, size_t threads)
    : stop(false),
      address_(address),
      port_(port),
      doc_root_(std::make_shared<std::string>(doc_root))
{

    net::io_context io_ctx{threads};
    ssl::context ssl_ctx(boost::asio::ssl::context::tlsv12_server);

    std::vector<std::thread> pool;
    pool.reserve(threads - 1);

    load_server_certificate(doc_root, ssl_ctx);

    // Create and launch a listening port

    std::make_shared<Listener>(
        io_ctx,
        ssl_ctx,
        tcp::endpoint{net::ip::make_address(address_), port},
        doc_root_)
        ->run();

    // Run the I/O service on the requested number of threads
    for(size_t i = 1; i < threads; i++)
        pool.emplace_back(
        [&io_ctx]
        {
            io_ctx.run();
        });
    io_ctx.run();
}

HttpsServer::~HttpsServer()
{
    // do nothing
}