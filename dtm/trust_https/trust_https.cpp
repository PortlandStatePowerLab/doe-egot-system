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

TrustHttps::TrustHttps(HttpsClient *https_client, HttpsClient *dtm_client)
    : https_client_(https_client), dtm_client_(dtm_client)
{
    // do nothing
}

TrustHttps::~TrustHttps()
{
    // do nothing
}

bb::http::response<bb::http::dynamic_body>
TrustHttps::Get(const std::string &target, const std::string &query)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "GET";
    msg.args["target"] = target;
    msg.args["query"] = query;
    msg.timestamp = psu::utilities::getTime();

    dtm_client_->Post("/na", dtm::Stringify(msg));
}

bb::http::response<bb::http::dynamic_body>
HttpsClient::Post(const std::string &target, const std::string &resource)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "POST";
    msg.args["target"] = target;
    msg.args["resource"] = resource;
    msg.timestamp = psu::utilities::getTime();

    dtm_client_->Post("/na", dtm::Stringify(msg));
}

bb::http::response<bb::http::dynamic_body>
HttpsClient::Put(const std::string &target, const std::string &resource)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "PUT";
    msg.args["target"] = target;
    msg.args["resource"] = resource;
    msg.timestamp = psu::utilities::getTime();

    dtm_client_->Post("/na", dtm::Stringify(msg));
}

bb::http::response<bb::http::dynamic_body>
HttpsClient::Delete(const std::string &target)
{
    dtm::Message msg;
    msg.from = "DCM";
    msg.to = "GSP";
    msg.command = "Delete";
    msg.args["target"] = target;
    msg.timestamp = psu::utilities::getTime();

    dtm_client_->Post("/na", dtm::Stringify(msg));
}