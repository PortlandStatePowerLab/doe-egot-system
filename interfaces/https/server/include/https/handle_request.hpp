#ifndef __HTTPS_SERVER_HANDLE_REQUEST_H__
#define __HTTPS_SERVER_HANDLE_REQUEST_H__

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
#include <regex>

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
inline std::string
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

inline std::string seperateQuery(const std::string& target, Href* href)
{
    std::vector <std::string> parts;
    size_t pos = target.find("?");
    if (pos != std::string::npos)
    {
        std::string base_uri = target.substr(0,pos);
        std::string query = target.substr(pos);

        std::regex start_regex("(s=(\\d+))");
        std::regex after_regex("(a=(\\d+))");
        std::regex limit_regex("(l=(\\d+))");
        std::smatch match;

        if(std::regex_search(query, match, start_regex))
        {
            href->query.start = std::stol(match[0].str());
        }

        if(std::regex_search(query, match, after_regex))
        {
            href->query.after = std::stoull(match[0].str());
        }

        if(std::regex_search(query, match, limit_regex))
        {
            href->query.limit = std::stoull(match[0].str());
        }

        return base_uri;
    }
    return target;
}

inline void seperateUri(const std::string& target, Href* href)
{
    std::regex path_regex("((\\/\\w+))");
    std::smatch match;

    if(std::regex_search(target, match, path_regex))
    {
        href->uri = match.str();
    }

    std::string subject = match.suffix();
    if(std::regex_search(subject, match, path_regex))
    {
        href->uri += "/*";
        href->subject = match.str().substr(1);
    }
}

inline Href extractHref (const std::string& target, const std::string& fingerprint)
{
    Href href;
    href.lfdi = fingerprint;

    std::string uri = seperateQuery(target, &href);

    seperateUri(uri, &href);
    return href;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template <class Body, class Allocator, class Send>
void HandleRequest(
    const std::string fingerprint,
    std::shared_ptr<const std::string> doc_root,
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
    Href href = extractHref(path, fingerprint);

    // verify the path is legal, might still send not_found when
    // the ECS actually tries to get the resource.
    std::string wadl_path = *doc_root + "/sep_xml/sep_wadl.xml";   
    sep::WADL* wadl = sep::WADL::getInstance(wadl_path);
    sep::WADLResource wadl_res = wadl->getResource(href.uri);

    if(wadl_res.properties.empty())
    {
        return send(not_found(path));
    }

    // verify method is legal for specific resource
    std::stringstream ss;
    ss << req.method();

    if (wadl_res.properties[ss.str()].allow == false)
    {
        std::string allowed;
        for (const auto& methods : wadl_res.properties)
        {
            if (methods.second.allow)
            {
                allowed += methods.first + ", ";
            }
        }

        allowed.pop_back(); // remove space
        allowed.pop_back(); // remove comma
        return send(method_not_allowed(allowed));
    }

    // Respond to DELETE request
    if(req.method() == http::verb::delete_)
    {
        // attempt to access resource
        World::getInstance().Delete(href);

        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    if (req.method() == http::verb::get)
    {
        // attempt to access resource
        std::string body = World::getInstance().Get(href);

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
        std::string body = World::getInstance().Get(href);

        // TODO if body == "" then send not found

        // Cache the size since we need it after the move
        auto const size = body.size();

        http::response<http::empty_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.content_length(size);
        res.keep_alive(req.keep_alive());
        return send(std::move(res));
    }

    if (req.method() == http::verb::post)
    {
        boost::beast::string_view content_type = req[http::field::content_type];
        if (content_type != "application/sep+xml")
        {
            return send(bad_request("Bad Content-Type"));
        }

        // attempt to access resource
        std::string loc = World::getInstance().Post(href, req.body());

        http::response<http::string_body> res{http::status::created, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.set(http::field::location, loc);
        res.keep_alive(req.keep_alive());
        res.prepare_payload();
        return send(std::move(res));
    }

    if (req.method() == http::verb::put)
    {
        boost::beast::string_view content_type = req[http::field::content_type];
        if (content_type != "application/sep+xml")
        {
            return send(bad_request("Bad Content-Type"));
        }

        // attempt to access resource
        std::string loc = World::getInstance().Put(href, req.body());

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.set(http::field::location, loc);
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

#endif // __HTTPS_SERVER_HANDLE_REQUEST_H__