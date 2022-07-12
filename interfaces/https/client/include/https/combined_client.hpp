#ifndef __COMBINED_CLIENT_H__
#define __COMBINED_CLIENT_H__

#include <iostream>
#include <dtm_msg_writer/announce_xml.h>
#include "https_client.hpp"
#include "abstract_client.hpp"

class CombinedHttpsClient : public AbstractClient
{
    public:
        CombinedHttpsClient(const std::string &gsp_root, const std::string &gsp_host, const std::string &gsp_port,
                            const std::string &dtm_root, const std::string &dtm_host, const std::string &dtm_port);
        ~CombinedHttpsClient();
        boost::beast::http::response <boost::beast::http::dynamic_body> Get
        (
            const std::string& target, const std::string& query = ""
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Post
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Put
        (
            const std::string& target, const std::string& resource
        );
        boost::beast::http::response <boost::beast::http::dynamic_body> Delete
        (
            const std::string& target
        );
        
    private:
        HttpsClient dtm_client_;
        HttpsClient gsp_client_;
        dcm::xml::XMLCommandAdapter xml_writer_;
};


#endif // __COMBINED_CLIENT_H__