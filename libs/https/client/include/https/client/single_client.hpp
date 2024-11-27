#ifndef __HTTPS_CLIENT_H__
#define __HTTPS_CLIENT_H__

#include "client.hpp"
#include <string>

namespace https {

///
/// Singleton for http client that allows the application to query a
/// preconfigured server from anywhere within the program
///
/// \code{.cpp}
/// Context ctx;
/// ctx.id = 1;
/// ctx.root = ".";
/// ctx.address = "www.google.com";
/// ctx.port = 443;
/// ctx.id = 1;
///
/// SingleClient::getInstance(ctx).Get("index.html");
/// // then every call after that can call without the context
/// SingleClient::getInstance().Get("index.html")
/// \endcode
///
class SingleClient : public AbstractClient {
public:
  // rule of 5
  SingleClient(SingleClient &other) = delete;    // clonable
  void operator=(const SingleClient &) = delete; // assignable

  static SingleClient &getInstance(const Context &context = {"", "", "", ""});

  sep::HexBinary160 getLFDI() override;

  boost::beast::http::response<boost::beast::http::dynamic_body>
  Get(const std::string &target, const std::string &query = "") override;

  boost::beast::http::response<boost::beast::http::dynamic_body>
  Post(const std::string &target, const std::string &resource) override;

  boost::beast::http::response<boost::beast::http::dynamic_body>
  Put(const std::string &target, const std::string &resource) override;

  boost::beast::http::response<boost::beast::http::dynamic_body>
  Delete(const std::string &target) override;

protected:
  SingleClient(const Context &context);
  ~SingleClient() noexcept;

private:
  Client client_;
};

} // namespace https

#endif // __HTTPS_CLIENT_H__
