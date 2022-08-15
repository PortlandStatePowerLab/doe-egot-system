#include "include/dtm_client.hpp"

DTMClient::DTMClient(const https::Context& context)
    : client_(context)
{
    // do nothing
}

DTMClient::~DTMClient()
{
    delete instance_;
}

DTMClient* DTMClient::getInstance(const https::Context& context)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        instance_ = new DTMClient(context);
    }
    return instance_;
}

DTMClient* DTMClient::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        std::cout << "DTMClient : instance not initilized with context" << std::endl;
        abort();
    }
    return instance_;
}

boost::beast::http::response<boost::beast::http::dynamic_body> DTMClient::Get(const std::string &target, const std::string &query)
{
    return client_.Get(target,query);
}

boost::beast::http::response<boost::beast::http::dynamic_body> DTMClient::Post(const std::string &target, const std::string &resource)
{
    return client_.Post(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> DTMClient::Put(const std::string &target, const std::string &resource)
{
    return client_.Put(target,resource);
}

boost::beast::http::response<boost::beast::http::dynamic_body> DTMClient::Delete(const std::string &target)
{
    return client_.Delete(target);
}