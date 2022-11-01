#ifndef __ABSTRACT_CLIENT_H__
#define __ABSTRACT_CLIENT_H__

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <ieee-2030.5/lfdi_type.hpp>

#include <string>
#include <memory>
#include <iostream>

namespace https
{
    struct Context
    {
        std::string id;
        std::string root;
        std::string host;
        std::string port;
    };
    
    class AbstractClient
    {
    public:
        virtual sep::LFDIType getLFDI() = 0;
        
        virtual boost::beast::http::response<boost::beast::http::dynamic_body> Get(
            const std::string &target, const std::string &query = "") = 0;

        virtual boost::beast::http::response<boost::beast::http::dynamic_body> Post(
            const std::string &target, const std::string &resource) = 0;

        virtual boost::beast::http::response<boost::beast::http::dynamic_body> Put(
            const std::string &target, const std::string &resource) = 0;

        virtual boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
            const std::string &target) = 0;
    };
}

#endif // __ABSTRACT_CLIENT_H__