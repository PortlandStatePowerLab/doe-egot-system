#ifndef __TRUST_HTTPS_H__
#define __TRUST_HTTPS_H__

#include <https/client.hpp>
#include <ieee-2030.5/simple_types.hpp>

namespace trust
{
    // Singleton Design Pattern
    class HttpsClient : public https::AbstractClient
    {
    public:
        // rule of 5
        HttpsClient(HttpsClient &other) = delete;     // clonable
        void operator=(const HttpsClient &) = delete; // assignable

        static HttpsClient &getInstance(
            const https::Context &gsp_ctx = {"", "", "", ""},
            const https::Context &dtm_ctx = {"", "", "", ""});

        boost::beast::http::response<boost::beast::http::dynamic_body> Get(
            const std::string &target, const std::string &query = "") override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Post(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Put(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
            const std::string &target) override;

        sep::HexBinary160 getLFDI();

    protected:
        https::Client gsp_client_;
        https::Client dtm_client_;

    private:
        HttpsClient(const https::Context &gsp, const https::Context &dtm);
        ~HttpsClient();

        std::string packGetRequest(const std::string &target, const std::string &query);
        std::string packPostRequest(const std::string &target, const std::string &body);
        std::string packPutRequest(const std::string &target, const std::string &body);
        std::string packDeleteRequest(const std::string &target);
        std::string packResponse(const boost::beast::http::response<boost::beast::http::dynamic_body> &rsp);
    };
} // namespace trust

#endif // __TRUST_HTTPS_H__