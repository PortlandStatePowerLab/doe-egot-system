#include <boost/asio/ssl/error.hpp>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS // had to to remove boost warning
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <https/client/client.hpp>
#include <https/client/root_certificates.hpp>
#include <sep/xml/utilities.hpp>

// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio;
namespace ssl = net::ssl;

namespace https {
Client::Client(const Context &context)
    : context_(context), ssl_context_(ssl::context::tlsv12_client),
      resolver_(io_context_) {
  std::string root_ca = context_.root + "/root-ca";
  load_root_certificates(context_.id, root_ca, ssl_context_);
  readLFDI();
}

Client::~Client() {
  // do nothing
}

sep::HexBinary160 Client::getLFDI() { return lfdi_; }

Context Client::getContext() { return context_; }

bb::http::response<bb::http::dynamic_body>
Client::Get(const std::string &target, const std::string &query) {
  std::string href = target + query;
  bb::http::request<bb::http::string_body> req{bb::http::verb::get, href, 11};

  req.set(bb::http::field::host, context_.host);
  req.prepare_payload();
  return Client::Send(req);
}

bb::http::response<bb::http::dynamic_body>
Client::Post(const std::string &target, const std::string &resource) {
  bb::http::request<bb::http::string_body> req{bb::http::verb::post, target,
                                               11};

  req.set(bb::http::field::host, context_.host);
  req.set(bb::http::field::content_type, "application/sep+xml");
  req.body() = resource;
  req.prepare_payload();
  return Client::Send(req);
}

bb::http::response<bb::http::dynamic_body>
Client::Put(const std::string &target, const std::string &resource) {
  bb::http::request<bb::http::string_body> req{bb::http::verb::put, target, 11};

  req.set(bb::http::field::host, context_.host);
  req.set(bb::http::field::content_type, "application/sep+xml");
  req.body() = resource;
  req.prepare_payload();
  return Client::Send(req);
}

bb::http::response<bb::http::dynamic_body>
Client::Delete(const std::string &target) {
  bb::http::request<bb::http::string_body> req{bb::http::verb::delete_, target,
                                               11};

  req.set(bb::http::field::host, context_.host);
  req.prepare_payload();
  return Client::Send(req);
}

void Client::readLFDI() {
  std::string cert_file =
      context_.root + "/root-ca/client" + context_.id + ".crt";
  FILE *fp = fopen(cert_file.c_str(), "r");
  X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);

  // fingerprint
  unsigned char md[EVP_MAX_MD_SIZE];
  unsigned int n;
  X509_digest(cert, EVP_sha256(), md, &n);

  // 40 hex character length for fingerprint
  std::ostringstream oss;
  for (size_t i = 0; i < n; i++) {
    oss << std::hex << (int)md[i];
  };

  lfdi_ = xml::util::Dehexify<sep::HexBinary160>(oss.str().substr(0, 40));
}

bb::ssl_stream<bb::tcp_stream> Client::Connect() {
  bb::ssl_stream<bb::tcp_stream> stream(io_context_, ssl_context_);

  // Set SNI Hostname (many hosts need this to handshake successfully)
  if (!SSL_set_tlsext_host_name(stream.native_handle(),
                                context_.host.c_str())) {
    bb::error_code ec{static_cast<int>(::ERR_get_error()),
                      net::error::get_ssl_category()};
    throw bb::system_error{ec};
  }

  // Make the connection on the IP address we get from a lookup
  bb::get_lowest_layer(stream).connect(
      resolver_.resolve(context_.host, context_.port));
  stream.handshake(ssl::stream_base::client);
  return stream;
}

bb::http::response<bb::http::dynamic_body>
Client::Send(bb::http::request<bb::http::string_body> &req) {
  boost::system::error_code ec;

  // Declare a container to hold the response
  bb::http::response<bb::http::dynamic_body> res;
  try {
    bb::ssl_stream<bb::tcp_stream> stream = Client::Connect();

    // Send the HTTP request to the remote host
    bb::http::write(stream, req);

    // This buffer is used for reading and must be persisted
    bb::flat_buffer buffer;

    // Receive the HTTP response
    bb::http::read(stream, buffer, res);
  } catch (const boost::beast::error_code &e) {
    if (e != boost::asio::ssl::error::stream_truncated) {
      std::cerr << e << '\n';
    }
  }

  return res;
}
} // namespace https
