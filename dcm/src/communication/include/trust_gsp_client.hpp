#ifndef __TRUST_GSP_CLIENT_H__
#define __TRUST_GSP_CLIENT_H__

#include "gsp_client.hpp"
#include "dtm_client.hpp"
#include <https/abstract_client.hpp>
#include <mutex>

class TrustGSPClient : public https::AbstractClient
{
public:
    TrustGSPClient(TrustGSPClient &other) = delete;     // clonable
    
    void operator=(const TrustGSPClient &) = delete;    // assignable

    static TrustGSPClient* getInstance(const https::Context& gsp, const https::Context& dtm);
    static TrustGSPClient* getInstance();

    boost::multiprecision::uint128_t getLFDI() override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

protected:
    TrustGSPClient(const https::Context& gsp, const https::Context& dtm);
    ~TrustGSPClient() noexcept;

private:
    static TrustGSPClient *instance_;
    static std::mutex mutex_;
};

#endif // __TRUST_GSP_CLIENT_H__