#define BOOST_BIND_GLOBAL_PLACEHOLDERS // had to to remove boost warning
#include "include/https/https_client.hpp"
#include "include/https/root_certificates.hpp"
#include <boost/asio/ssl/rfc2818_verification.hpp>
#include <xml/adapter.hpp>

// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio; 
namespace ssl = net::ssl; 

HttpsClient* HttpsClient::instance_{nullptr};
std::mutex HttpsClient::mutex_;

HttpsClient::HttpsClient(const std::string& id, const std::string &root, const std::string &host, const std::string &port) 
    : id_(id),
    root_(root),
    host_(host), 
    port_(port),
    lfdi_(0), 
    ssl_context_(ssl::context::tlsv12_client), 
    resolver_(io_context_)
{
    std::string root_ca = root + "/root-ca";
    readLFDI(root_ca);
    load_root_certificates(id, root_ca, ssl_context_);  
}

HttpsClient::~HttpsClient ()
{
    delete instance_;
}

HttpsClient* HttpsClient::getInstance(const std::string& id, const std::string &root, const std::string &host,const std::string &port)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_ == nullptr)
    {
        instance_ = new HttpsClient(id, root, host, port);
    }
    return instance_;
};

boost::multiprecision::uint256_t HttpsClient::getLFDI ()
{
    return lfdi_;
};

bb::http::response <bb::http::dynamic_body>
HttpsClient::Get(const std::string& target, const std::string& query)
{
    std::string href = target + query;
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::get, href, 11
    };
    req.set(bb::http::field::host, host_);

    req.prepare_payload();
    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Post(const std::string& target, const std::string& resource)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::post, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.body() = resource;
    req.prepare_payload();

    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Put(const std::string& target, const std::string& resource)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::put, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.body() = resource;
    req.prepare_payload();

    return HttpsClient::Send (req);
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Delete(const std::string& target)
{
    bb::http::request <bb::http::string_body> req
    {
        bb::http::verb::delete_, target, 11
    };
    req.set(bb::http::field::host, host_);

    req.prepare_payload();

    return HttpsClient::Send (req);
}

void HttpsClient::readLFDI(const std::string& root)
{
    std::string cert_file = root + "/client" + id_ + ".crt";
    FILE *fp = fopen(cert_file.c_str(), "r");
    X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);

    // fingerprint
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int n;
    X509_digest(cert, EVP_sha256(), md, &n);

    // 40 hex character length for fingerprint
    std::ostringstream oss;
    for (size_t i = 0; i < n; i++)
    {
        oss << std::hex << (int)md[i];
    };

    lfdi_ = xml::util::Dehexify<boost::multiprecision::uint256_t>(oss.str().substr(0, 40));
}

bb::ssl_stream<bb::tcp_stream> HttpsClient::Connect() 
{
    bb::ssl_stream<bb::tcp_stream> stream(io_context_, ssl_context_);

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if(! SSL_set_tlsext_host_name(stream.native_handle(), host_.c_str()))
    {
        bb::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw bb::system_error{ec};
    } 

    // Make the connection on the IP address we get from a lookup
    bb::get_lowest_layer(stream).connect(resolver_.resolve(host_, port_));
    
    stream.handshake(ssl::stream_base::client);

    return stream;
}

bb::http::response <bb::http::dynamic_body>
HttpsClient::Send(bb::http::request<bb::http::string_body>& req)
{
    bb::ssl_stream<bb::tcp_stream> stream = HttpsClient::Connect();

	// Send the HTTP request to the remote host
	bb::http::write(stream, req);

	// This buffer is used for reading and must be persisted
	bb::flat_buffer buffer;

	// Declare a container to hold the response
	bb::http::response<bb::http::dynamic_body> res;

	// Receive the HTTP response
	bb::http::read(stream, buffer, res);

    boost::system::error_code ec;
    stream.shutdown(ec);
    if(ec == net::error::eof)
    {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if(ec)
    {
        throw bb::system_error{ec};
    }

	return res;
}