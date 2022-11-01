#include "include/gsp_client.hpp"

GSPClient::GSPClient(const https::Context& context)
    : client_(context)
{
    // do nothing
}

GSPClient::~GSPClient()
{
    delete instance_;
}

GSPClient* GSPClient::getInstance(const https::Context& context)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        instance_ = new GSPClient(context);
    }
    return instance_;
}

GSPClient* GSPClient::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        std::cout << "GSPClient : instance not initilized with context" << std::endl;
        abort();
    }
    return instance_;
}

sep::LFDIType GSPClient::getLFDI()
{
    return client_.getLFDI();
}

boost::beast::http::response<boost::beast::http::dynamic_body> GSPClient::Get(const std::string &target, const std::string &query)
{
    return client_.Get(target,query);
}

boost::beast::http::response<boost::beast::http::dynamic_body> GSPClient::Post(const std::string &target, const std::string &resource)
{
    return client_.Post(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> GSPClient::Put(const std::string &target, const std::string &resource)
{
    return client_.Put(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> GSPClient::Delete(const std::string &target)
{
    return client_.Delete(target);
}