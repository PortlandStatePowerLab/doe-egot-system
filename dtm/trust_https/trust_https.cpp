#include "include/trust_https/trust_https.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <utilities/utilities.hpp>
#include <trust_xml/trust_xml.hpp>

// alias to make things easier to read
namespace pt = boost::property_tree;
namespace bb = boost::beast;
namespace net = boost::asio;
namespace ssl = net::ssl;

TrustHttps::TrustHttps(const https::Context &gsp, const https::Context &dtm)
    : gsp_client_(gsp), dtm_client_(dtm)
{
}

TrustHttps::~TrustHttps()
{
    // do nothing
}

bb::http::response<bb::http::dynamic_body>
TrustHttps::Get(const std::string &target, const std::string &query)
{
    dtm_client_->Post("/na", packGetRequest(target, query));
    bb::http::response<bb::http::dynamic_body> rsp = gsp_client_->Get(target, query);
    dtm_client_->Post("/na", packResponse(rsp));
    return rsp;
}

bb::http::response<bb::http::dynamic_body>
TrustHttps::Post(const std::string &target, const std::string &resource)
{
    dtm_client_->Post("/na", packPostRequest(target, resource));
    bb::http::response<bb::http::dynamic_body> rsp = gsp_client_->Post(target, resource);
    dtm_client_->Post("/na", packResponse(rsp));
    return rsp;
}

bb::http::response<bb::http::dynamic_body>
TrustHttps::Put(const std::string &target, const std::string &resource)
{
    dtm_client_->Post("/na", packPutRequest(target, resource));
    bb::http::response<bb::http::dynamic_body> rsp = gsp_client_->Put(target, resource);
    dtm_client_->Post("/na", packResponse(rsp));
    return rsp;
}

bb::http::response<bb::http::dynamic_body>
TrustHttps::Delete(const std::string &target)
{
    dtm_client_->Post("/na", packDeleteRequest(target));
    bb::http::response<bb::http::dynamic_body> rsp = gsp_client_->Delete(target);
    dtm_client_->Post("/na", packResponse(rsp));
    return rsp;
}

std::string TrustHttps::packGetRequest(const std::string &target, const std::string &query);
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.args["target"] = target;
    msg.args["query"] = query;
    msg.timestamp = psu::utilities::getTime();
    return dtm::Stringify(msg);
}

std::string TrustHttps::packPostRequest(const std::string &target, const std::string &body);
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.args["target"] = target;
    msg.args["body"] = body;
    msg.timestamp = psu::utilities::getTime();
    return dtm::Stringify(msg);
}

std::string TrustHttps::packPutRequest(const std::string &target, const std::string &body);
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.args["target"] = target;
    msg.args["body"] = body;
    msg.timestamp = psu::utilities::getTime();
    return dtm::Stringify(msg);
}

std::string TrustHttps::packDeleteRequest(const std::string &target);
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.args["target"] = target;
    msg.timestamp = psu::utilities::getTime();
    return dtm::Stringify(msg);
}

std::string TrustHttps::packResponse(const bb::http::response<bb::http::dynamic_body> &rsp)
{
    dtm::Message msg;
    msg.from = "GSP";
    msg.to = "DCM";
    msg.command = "GETResponse";
    msg.args["result"] = boost::beast::buffers_to_string(rsp.result());
    msg.args["body"] = boost::beast::buffers_to_string(rsp.body().data());
    msg.timestamp = psu::utilities::getTime();
    return dtm::Stringify(msg);
}