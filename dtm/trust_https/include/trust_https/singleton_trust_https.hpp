#ifndef __SINGLETON_TRUST_HTTPS_H__
#define __SINGLETON_TRUST_HTTPS_H__

#include "trust_https.hpp"
#include <string>
#include <memory>
#include <mutex>

class SingletonTrustHttps : public https::AbstractClient
{
public:
    SingletonTrustHttps(SingletonTrustHttps &other) = delete;   // clonable
    
    void operator=(const SingletonTrustHttps &) = delete;       // assignable
    
    static SingletonTrustHttps* getInstance(const https::Context& gsp, const https::Context& dtm);
    
    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

protected:
    SingletonTrustHttps(const https::Context& gsp, const https::Context& dtm);
    ~SingletonTrustHttps() noexcept;

private:
    static SingletonTrustHttps *instance_;
    static std::mutex mutex_;
    TrustHttps client_;
};

#endif // __SINGLETON_TRUST_HTTPS_H__