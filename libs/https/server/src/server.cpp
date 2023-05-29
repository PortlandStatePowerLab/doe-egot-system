#define BOOST_BIND_GLOBAL_PLACEHOLDERS // had to to remove boost warning
#include <https/server/server.hpp>
#include <https/server/listener.hpp>
#include <https/server/session.hpp>
#include <https/server/certificates.hpp>
#include <https/server/send_lambda.hpp>
#include <https/server/handle_request.hpp>
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <ecs/server/sep/world.hpp>
#include <sep/xml/adapter.hpp>
#include <fstream>
#include <boost/asio/ssl.hpp>
#include <boost/bind/bind.hpp>
#include <boost/filesystem.hpp>
#include <utilities/utilities.hpp>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

HttpsServer::HttpsServer(const std::string &address, uint16_t port, const std::string &doc_root, int threads)
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