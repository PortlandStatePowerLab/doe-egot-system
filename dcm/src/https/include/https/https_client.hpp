#ifndef __HTTPS_CLIENT_H__
#define __HTTPS_CLIENT_H__

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <string>
#include <memory>

extern std::string g_program_path;

// Singleton Design Pattern
class HttpsClient
{
public:
    HttpsClient (const std::string &root, const std::string &host,const std::string &port);
    ~HttpsClient ();

    boost::beast::http::response <boost::beast::http::dynamic_body> Get
    (
        const std::string& target, const std::string& query = ""
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Post
    (
        const std::string& target, const std::string& resource
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Put
    (
        const std::string& target, const std::string& resource
    );

    boost::beast::http::response <boost::beast::http::dynamic_body> Delete
    (
        const std::string& target
    );

private:
    boost::beast::ssl_stream<boost::beast::tcp_stream> Connect ();
    boost::beast::http::response <boost::beast::http::dynamic_body> Send
    (
        boost::beast::http::request <boost::beast::http::string_body>& req
    );

private:
    std::string root_;
    std::string host_;
    std::string port_;

    // required for all boost beast I/O
    boost::asio::io_context io_context_;
    boost::asio::ssl::context ssl_context_;
    boost::asio::ip::tcp::resolver resolver_;
};

#endif // __HTTPS_CLIENT_H__