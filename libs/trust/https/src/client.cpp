#include <trust/https/client.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <utilities/utilities.hpp>
#include <trust/xml/utils.hpp>
#include <sep/xml/utilities.hpp>

// alias to make things easier to read
namespace pt = boost::property_tree;
namespace bb = boost::beast;
namespace net = boost::asio;
namespace ssl = net::ssl;

static bool initialized_s;

namespace trust
{
    HttpsClient::HttpsClient(const https::Context &gsp, const https::Context &dtm)
        : gsp_client_(gsp), dtm_client_(dtm)
    {
        // do nothing
    }

    HttpsClient::~HttpsClient()
    {
        // do nothing
    }

    HttpsClient &HttpsClient::getInstance(const https::Context &gsp, const https::Context &dtm)
    {
        if (gsp.host != "" && dtm.host != "" && !initialized_s)
        {
            initialized_s = true;
        }

        if (initialized_s)
        {
            static HttpsClient instance(gsp, dtm);
            return instance;
        }            
        
        throw "Trust client must be initialized with GSP and DTMC context first!";
    };

    sep::HexBinary160 HttpsClient::getLFDI()
    {
        return gsp_client_.getLFDI();
    }

    bb::http::response<bb::http::dynamic_body>
    HttpsClient::Get(const std::string &target, const std::string &query)
    {
        bb::http::response<bb::http::dynamic_body> rsp;

        try
        {
            dtm_client_.Post("/na", packGetRequest(target, query));
            rsp = gsp_client_.Get(target, query);
            dtm_client_.Post("/na", packResponse(rsp));
        }
        catch(const std::exception& e)
        {
            std::cout << "TrustHTTP Error : " << target 
                << "\n\t" << e.what() << '\n';
        }
        
        return rsp;
    }

    bb::http::response<bb::http::dynamic_body>
    HttpsClient::Post(const std::string &target, const std::string &resource)
    {
        bb::http::response<bb::http::dynamic_body> rsp;
        try
        {
            dtm_client_.Post("/na", packPostRequest(target, resource));
            rsp = gsp_client_.Post(target, resource);
            dtm_client_.Post("/na", packResponse(rsp));
        }
        catch(const std::exception& e)
        {
            std::cout << "TrustHTTP Error : " << target 
                << "\n\t" << e.what() << '\n';
        }

        return rsp;
    }

    bb::http::response<bb::http::dynamic_body>
    HttpsClient::Put(const std::string &target, const std::string &resource)
    {
        bb::http::response<bb::http::dynamic_body> rsp;
        try
        {
            dtm_client_.Post("/na", packPutRequest(target, resource));
            rsp = gsp_client_.Put(target, resource);
            dtm_client_.Post("/na", packResponse(rsp));
        }
        catch(const std::exception& e)
        {
            std::cout << "TrustHTTP Error : " << target 
                << "\n\t" << e.what() << '\n';
        }
        
        return rsp;
    }

    bb::http::response<bb::http::dynamic_body>
    HttpsClient::Delete(const std::string &target)
    {
        bb::http::response<bb::http::dynamic_body> rsp;
        try
        {
            dtm_client_.Post("/na", packDeleteRequest(target));
            rsp = gsp_client_.Delete(target);
            dtm_client_.Post("/na", packResponse(rsp));
        }
        catch(const std::exception& e)
        {
            std::cout << "TrustHTTP Error : " << target 
                << "\n\t" << e.what() << '\n';
        }
        
        return rsp;
    }

    std::string HttpsClient::packGetRequest(const std::string &target, const std::string &query)
    {
        trust::Message msg;
        msg.to = "GSP";
        msg.from = "DCM";
        msg.timestamp = psu::utilities::getTime();
        msg.contents["method"] = "GET";
        msg.contents["version"] = "11";
        msg.contents["host"] = gsp_client_.getContext().host;
        msg.contents["target"] = target;
        msg.contents["query"] = query;
        return trust::Stringify(msg);
    }

    std::string HttpsClient::packPostRequest(const std::string &target, const std::string &body)
    {
        trust::Message msg;
        msg.to = "GSP";
        msg.from = "DCM";
        msg.timestamp = psu::utilities::getTime();
        msg.contents["method"] = "POST";
        msg.contents["version"] = "11";
        msg.contents["host"] = gsp_client_.getContext().host;
        msg.contents["target"] = target;
        msg.contents["body"] = body;
        return trust::Stringify(msg);
    }

    std::string HttpsClient::packPutRequest(const std::string &target, const std::string &body)
    {
        trust::Message msg;
        msg.to = "GSP";
        msg.from = "DCM";
        msg.timestamp = psu::utilities::getTime();
        msg.contents["method"] = "PUT";
        msg.contents["version"] = "11";
        msg.contents["host"] = gsp_client_.getContext().host;
        msg.contents["target"] = target;
        msg.contents["body"] = body;
        return trust::Stringify(msg);
    }

    std::string HttpsClient::packDeleteRequest(const std::string &target)
    {
        trust::Message msg;
        msg.to = "GSP";
        msg.from = "DCM";
        msg.timestamp = psu::utilities::getTime();
        msg.contents["method"] = "DELETE";
        msg.contents["version"] = "11";
        msg.contents["host"] = gsp_client_.getContext().host;
        msg.contents["target"] = target;
        return trust::Stringify(msg);
    }

    std::string HttpsClient::packResponse(const bb::http::response<bb::http::dynamic_body> &rsp)
    {
        trust::Message msg;
        msg.to = "DCM";
        msg.from = "GSP";
        msg.timestamp = psu::utilities::getTime();
        msg.contents["version"] = std::to_string(rsp.version());
        msg.contents["statusCode"] = std::to_string(rsp.result_int());
        msg.contents["body"] = boost::beast::buffers_to_string(rsp.body().data());

        for (const auto &key : rsp)
        {
            msg.contents[key.name_string().to_string()] = key.value().to_string();
        }

        return trust::Stringify(msg);
    }
} // namespace trust