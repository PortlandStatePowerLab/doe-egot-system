#include "include/trust_gsp_client.hpp"
#include <trust_xml/trust_xml.hpp>
#include <utilities/utilities.hpp>

TrustGSPClient::TrustGSPClient(const https::Context& gsp, const https::Context& dtm)
{
    // init both singleton clients with context.
    GSPClient::getInstance(gsp);
    DTMClient::getInstance(dtm);
}

TrustGSPClient::~TrustGSPClient()
{
    delete instance_;
}

TrustGSPClient* TrustGSPClient::getInstance(const https::Context& gsp, const https::Context& dtm)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        instance_ = new TrustGSPClient(gsp, dtm);
    }
    return instance_;
}

TrustGSPClient* TrustGSPClient::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(instance_ = nullptr)
    {
        std::cout << "TrustGSPClient : instance not initilized with context" << std::endl;
        abort();
    }
    return instance_;
}

sep::LFDIType TrustGSPClient::getLFDI()
{
    return DTMClient::getInstance()->getLFDI();
}

boost::beast::http::response<boost::beast::http::dynamic_body> TrustGSPClient::Get(const std::string &target, const std::string &query)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "GET";
    msg.args["target"] = target;
    msg.args["query"] = query;
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
    
    auto response = GSPClient::getInstance()->Get(target,query);

    msg.from = "GSP";
    msg.to = "DCM";
    msg.command = "GETResponse";
    msg.args["result"] = std::to_string(response.result_int());
    msg.args["body"] = boost::beast::buffers_to_string(response.body().data());
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    return response;
}

boost::beast::http::response<boost::beast::http::dynamic_body> TrustGSPClient::Post(const std::string &target, const std::string &resource)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "POST";
    msg.args["target"] = target;
    msg.args["body"] = resource;
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
    
    auto response = GSPClient::getInstance()->Post(target,resource);

    msg.from = "GSP";
    msg.to = "DCM";
    msg.command = "POSTResponse";
    msg.args["result"] = std::to_string(response.result_int());
    msg.args["body"] = boost::beast::buffers_to_string(response.body().data());
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    return response;
}

boost::beast::http::response<boost::beast::http::dynamic_body> TrustGSPClient::Put(const std::string &target, const std::string &resource)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "PUT";
    msg.args["target"] = target;
    msg.args["body"] = resource;
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
    
    auto response = GSPClient::getInstance()->Put(target,resource);

    msg.from = "GSP";
    msg.to = "DCM";
    msg.command = "PUTResponse";
    msg.args["result"] = std::to_string(response.result_int());
    msg.args["body"] = boost::beast::buffers_to_string(response.body().data());
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    return response;
}

boost::beast::http::response<boost::beast::http::dynamic_body> TrustGSPClient::Delete(const std::string &target)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "DELETE";
    msg.args["target"] = target;
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));
    
    auto response = GSPClient::getInstance()->Delete(target);

    msg.from = "GSP";
    msg.to = "DCM";
    msg.command = "DELETEResponse";
    msg.args["result"] = std::to_string(response.result_int());
    msg.args["body"] = boost::beast::buffers_to_string(response.body().data());
    msg.timestamp = psu::utilities::getTime();
    DTMClient::getInstance()->Post("/na", dtm::Stringify(msg));

    return response;
}