#ifndef __INTERFACE_HTTPS_CLIENT_H__
#define __INTERFACE_HTTPS_CLIENT_H__

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include <string>

#include "abstract_client.hpp"

namespace https
{    
    class Client : AbstractClient
    {
    public:
        Client(const Context& context);

        ~Client();

        sep::HexBinary160 getLFDI() override;
        Context getContext();

        boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Post(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Put(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
            const std::string &target) override;

    private:
        Context context_;
        sep::HexBinary160 lfdi_;

        // required for all boost beast I/O
        boost::asio::io_context io_context_;
        boost::asio::ssl::context ssl_context_;
        boost::asio::ip::tcp::resolver resolver_;

    private:
        void readLFDI();
        boost::beast::ssl_stream<boost::beast::tcp_stream> Connect();
        boost::beast::http::response<boost::beast::http::dynamic_body> Send(
            boost::beast::http::request<boost::beast::http::string_body> &req);
    };
    
} // namespace https


#endif // __INTERFACE_HTTPS_CLIENT_H__