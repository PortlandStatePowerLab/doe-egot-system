#ifndef __HTTPS_SERVER_LISTENER_H__
#define __HTTPS_SERVER_LISTENER_H__

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

#include "session.hpp"

// Accepts incoming connections and launches the sessions
class Listener
    : public boost::asio::coroutine
    , public std::enable_shared_from_this<Listener>
{
    boost::asio::io_context& ioc_;
    boost::asio::ssl::context& ctx_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<std::string const> doc_root_;

public:
    Listener(
        boost::asio::io_context& ioc,
        boost::asio::ssl::context& ctx,
        boost::asio::ip::tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : ioc_(ioc)
        , ctx_(ctx)
        , acceptor_(boost::asio::make_strand(ioc))
        , socket_(boost::asio::make_strand(ioc))
        , doc_root_(doc_root)
    {
        boost::beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
        if(ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if(ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            boost::asio::socket_base::max_listen_connections, ec);
        if(ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
    run()
    {
        loop();
    }

private:

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

    void loop(boost::beast::error_code ec = {})
    {
        reenter(*this)
        {
            for(;;)
            {
                yield acceptor_.async_accept(
                    socket_,
                    std::bind(
                        &Listener::loop,
                        shared_from_this(),
                        std::placeholders::_1));
                if(ec)
                {
                    fail(ec, "accept");
                }
                else
                {
                    // Create the session and run it
                    std::make_shared<Session>(
                        std::move(socket_),
                        ctx_,
                        doc_root_)->run();
                }

                // Make sure each session gets its own strand
                socket_ = boost::asio::ip::tcp::socket(boost::asio::make_strand(ioc_));
            }
        }
    }

    #include <boost/asio/unyield.hpp>
};

#endif // __HTTPS_SERVER_LISTENER_H__