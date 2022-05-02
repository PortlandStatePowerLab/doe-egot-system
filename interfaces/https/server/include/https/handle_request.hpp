#include "server_certificates.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/config.hpp>
#include <world/world.hpp>
#include <wadl/wadl.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>

// Return a reasonable mime type based on the extension of a file.
beast::string_view
mime_type(beast::string_view path)
{
    using beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind(".");
        if (pos == beast::string_view::npos)
            return beast::string_view{};
        return path.substr(pos);
    }();
    if (iequals(ext, ".htm"))
        return "text/html";
    if (iequals(ext, ".html"))
        return "text/html";
    if (iequals(ext, ".php"))
        return "text/html";
    if (iequals(ext, ".css"))
        return "text/css";
    if (iequals(ext, ".txt"))
        return "text/plain";
    if (iequals(ext, ".js"))
        return "application/javascript";
    if (iequals(ext, ".json"))
        return "application/json";
    if (iequals(ext, ".xml"))
        return "application/xml";
    if (iequals(ext, ".swf"))
        return "application/x-shockwave-flash";
    if (iequals(ext, ".flv"))
        return "video/x-flv";
    if (iequals(ext, ".png"))
        return "image/png";
    if (iequals(ext, ".jpe"))
        return "image/jpeg";
    if (iequals(ext, ".jpeg"))
        return "image/jpeg";
    if (iequals(ext, ".jpg"))
        return "image/jpeg";
    if (iequals(ext, ".gif"))
        return "image/gif";
    if (iequals(ext, ".bmp"))
        return "image/bmp";
    if (iequals(ext, ".ico"))
        return "image/vnd.microsoft.icon";
    if (iequals(ext, ".tiff"))
        return "image/tiff";
    if (iequals(ext, ".tif"))
        return "image/tiff";
    if (iequals(ext, ".svg"))
        return "image/svg+xml";
    if (iequals(ext, ".svgz"))
        return "image/svg+xml";
    return "application/text";
}

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string
path_cat(
    beast::string_view base,
    beast::string_view path)
{
    if (base.empty())
        return std::string(path);
    std::string result(base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if (result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
    for (auto &c : result)
        if (c == '/')
            c = path_separator;
#else
    char constexpr path_separator = '/';
    if (result.back() == path_separator)
        result.resize(result.size() - 1);
    result.append(path.data(), path.size());
#endif
    return result;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template <class Body, class Allocator, class Send>
void HandleRequest(
    const std::string fingerprint,
    std::shared_ptr<std::string> doc_root,
    http::request<Body, http::basic_fields<Allocator>> &&req,
    Send &&send)
{
    // Returns a bad request response
    auto const bad_request =
        [&req](beast::string_view why)
    {
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    // Returns a method not allowed
    auto const method_not_allowed =
        [&req](beast::string_view allow)
    {
        http::response<http::string_body> res{http::status::method_not_allowed, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.set(http::field::allow, allow);
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return res;
    };

    // Returns a not found response
    auto const not_found =
        [&req](beast::string_view target)
    {
        http::response<http::string_body> res{http::status::not_found, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "The resource '" + std::string(target) + "' was not found.";
        res.prepare_payload();
        return res;
    };

    // Returns a server error response
    auto const server_error =
        [&req](beast::string_view what)
    {
        http::response<http::string_body> res{http::status::internal_server_error, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = "An error occurred: '" + std::string(what) + "'";
        res.prepare_payload();
        return res;
    };

    // If open path "/" then default to dcap
    std::string path = path_cat("", req.target());
    if (req.target().back() == '/')
    {
        path.append("dcap");
    }

    // verify the path is legal
    std::string wadl_path = *doc_root + "/sep_xml/sep_wadl.xml";
    sep::WADLResource wadl_access = sep::WADL::getInstance(wadl_path)->getResource(path);
    if (wadl_access.methods.at(0).content_type.at(0) == "")
    {
        return send(not_found(path));
    }

    /* // verify method is legal for specific resource
    if ((wadl_access & (1<<static_cast<int>(req.method()))) == 0)
    {
        std::string allowed;
        if ((wadl_access & 1<<1) > 0)
        {
            allowed += "DELETE, ";
        }
        if ((wadl_access & 1<<2) > 0)
        {
            allowed += "GET, ";
        }
        if ((wadl_access & 1<<3) > 0)
        {
            allowed += "HEAD, ";
        }
        if ((wadl_access & 1<<4) > 0)
        {
            allowed += "POST, ";
        }
        if ((wadl_access & 1<<5) > 0)
        {
            allowed += "PUT, ";
        }
        allowed.pop_back(); // remove space
        allowed.pop_back(); // remove comma
        return send(method_not_allowed(allowed));
    } */

    // build href query for ecs
    Href href;
    href.lfdi = fingerprint;
    href.uri = path;
    href.query = {0, 0, 0}; // TODO

    // Respond to DELETE request
    if(req.method() == http::verb::delete_)
    {
        // attempt to access resource
        World *ecs = World::getInstance();
        ecs->Delete(href);

        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "application/sep+xml");
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    if (req.method() == http::verb::get)
    {
        // attempt to access resource
        World *ecs = World::getInstance();
        std::string body = ecs->Get(href);

        // Cache the size since we need it after the move
        auto const size = body.size();

        // Respond to GET request
        http::response<http::string_body> res{
            std::piecewise_construct,
            std::make_tuple(std::move(body)),
            std::make_tuple(http::status::ok, req.version())};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "application/sep+xml");
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    // Respond to HEAD request
    if(req.method() == http::verb::head)
    {
        // attempt to access resource
        World *ecs = World::getInstance();
        std::string body = ecs->Get(href);

        // Cache the size since we need it after the move
        auto const size = body.size();

        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "application/sep+xml");
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    if (req.method() == http::verb::post)
    {
        boost::beast::string_view content_type = req[http::field::content_type];
        if (content_type != "application/sep+xml")
        {
            return send(bad_request("Bad content_type"));
        }

        // attempt to access resource
        World *ecs = World::getInstance();
        ecs->Post(href, req.body());

        http::response<http::string_body> res{http::status::created, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return send(std::move(res));
    }

    if (req.method() == http::verb::put)
    {
        boost::beast::string_view content_type = req[http::field::content_type];
        if (content_type != "application/sep+xml")
        {
            return send(bad_request("Bad content_type"));
        }

        // attempt to access resource
        World *ecs = World::getInstance();
        ecs->Put(href, req.body());

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return send(std::move(res));
    }

    // // Handle an unknown error
    // if (ec)
    // {
    //     return send(server_error(ec.message()));
    // }
}
