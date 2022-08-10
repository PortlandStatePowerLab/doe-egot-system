#ifndef __TRUST_HTTPS_H__
#define __TRUST_HTTPS_H__

#include <https/abstract_client.hpp>

// Singleton Design Pattern
class TrustHttps : public https::AbstractClient
{
public:
    TrustHttps(const https::Context& gsp, const https::Context& dtm);
    ~TrustHttps();

    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

    boost::multiprecision::uint256_t getLFDI ();

protected:
    https::Client gsp_client_;
    https::Client dtm_client_;

private:
    void readLFDI (const std::string& root);
    std::string packGetRequest(const std::string& target, const std::string &query);
    std::string packPostRequest(const std::string& target, const std::string &body);
    std::string packPutRequest(const std::string& target, const std::string &body);
    std::string packDeleteRequest(const std::string& target);
    std::string packResponse(const boost::beast::http::response<boost::beast::http::dynamic_body> &rsp);    
};

#endif // __TRUST_HTTPS_H__