#ifndef __TRUST_HTTPS_H__
#define __TRUST_HTTPS_H__

#include <https/https_client.hpp>

/**
 * The base Decorator class follows the same interface as the other components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize
 * it.
 */
class TrustHttps : public AbstractClient
{
public:
    TrustHttps(HttpsClient *https_client, HttpsClient *dtm_client);
    ~TrustHttps();

    // The Decorator delegates all work to the wrapped component.
    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "");

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource);

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource);

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target);

protected:
    HttpsClient *https_client_;
    HttpsClient *dtm_client_;
};

#endif // __TRUST_HTTPS_H__