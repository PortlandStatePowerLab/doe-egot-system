#ifndef __TRUST_HTTPS_H__
#define __TRUST_HTTPS_H__

#include <https/abstract_client.hpp>

// Singleton Design Pattern
class TrustHttps : public AbstractClient
{
public:
    // rule of 5
    TrustHttps(TrustHttps &other) = delete;         // clonable
    void operator=(const TrustHttps &) = delete;    // assignable

    static TrustHttps *getInstance();

    boost::multiprecision::uint256_t getLFDI ();

    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

protected:
    HttpsClient(const std::string& id, const std::string &root, const std::string &host, const std::string &port);
    ~HttpsClient() noexcept;

private:
    void readLFDI (const std::string& root);
    boost::beast::ssl_stream<boost::beast::tcp_stream> Connect();
    boost::beast::http::response<boost::beast::http::dynamic_body> Send(
        boost::beast::http::request<boost::beast::http::string_body> &req);

private:
    std::string id_;
    std::string root_;
    std::string host_;
    std::string port_;
    boost::multiprecision::uint256_t lfdi_;

    // required for all boost beast I/O
    boost::asio::io_context io_context_;
    boost::asio::ssl::context ssl_context_;
    boost::asio::ip::tcp::resolver resolver_;

private:
    // thread-safe singleton instance
    static HttpsClient *instance_;
    static std::mutex mutex_;
};

#endif // __TRUST_HTTPS_H__