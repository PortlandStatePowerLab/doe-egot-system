#ifndef __ABSTRACT_CLIENT_H__
#define __ABSTRACT_CLIENT_H__

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <sep/models/simple_types.hpp>
#include <string>

namespace https {
///
/// HTTP context for clients to connect to a server
///
/// \param id informs the client which ssl certificate it should load
/// \param root points to the root path for the client to search for
/// certificates
/// \param host is the server dns/ip address
/// \param port overrides the default 443 for https if the server requires it
///
struct Context {
  std::string id;
  std::string root;
  std::string host;
  std::string port;
};

///
/// HTTP client interface
///
class AbstractClient {
public:
  virtual sep::HexBinary160 getLFDI() = 0;

  virtual boost::beast::http::response<boost::beast::http::dynamic_body>
  Get(const std::string &target, const std::string &query = "") = 0;

  virtual boost::beast::http::response<boost::beast::http::dynamic_body>
  Post(const std::string &target, const std::string &resource) = 0;

  virtual boost::beast::http::response<boost::beast::http::dynamic_body>
  Put(const std::string &target, const std::string &resource) = 0;

  virtual boost::beast::http::response<boost::beast::http::dynamic_body>
  Delete(const std::string &target) = 0;
};
} // namespace https

#endif // __ABSTRACT_CLIENT_H__
