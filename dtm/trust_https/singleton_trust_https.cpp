#include "include/trust_https/singleton_trust_https.hpp"

SingletonTrustHttps::SingletonTrustHttps(const https::Context& gsp, const https::Context& dtm)
    : client_(gsp,dtm)
{
    // do nothing
}

SingletonTrustHttps::~SingletonTrustHttps()
{
    delete instance_;
}

SingletonTrustHttps* SingletonTrustHttps::getInstance(const https::Context& gsp, const https::Context& dtm)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        instance_ = new SingletonTrustHttps(gsp, dtm);
    }
    return instance_;
}

boost::beast::http::response<boost::beast::http::dynamic_body> SingletonTrustHttps::Get(const std::string &target, const std::string &query)
{
    return client_.Get(target,query);
}

boost::beast::http::response<boost::beast::http::dynamic_body> SingletonTrustHttps::Post(const std::string &target, const std::string &resource)
{
    return client_.Post(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> SingletonTrustHttps::Put(const std::string &target, const std::string &resource)
{
    return client_.Put(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> SingletonTrustHttps::Delete(const std::string &target)
{
    return client_.Delete(target);
}