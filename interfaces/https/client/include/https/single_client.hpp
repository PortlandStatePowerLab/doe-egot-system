#ifndef __HTTPS_CLIENT_H__
#define __HTTPS_CLIENT_H__

#include <string>
#include <ieee-2030.5/lfdi_type.hpp>
#include "client.hpp"

namespace https
{

    // Singleton Design Pattern
    class SingleClient : public AbstractClient
    {
    public:
        // rule of 5
        SingleClient(SingleClient &other) = delete;    // clonable
        void operator=(const SingleClient &) = delete; // assignable

        static SingleClient &getInstance(const Context &context = {"","","",""});

        sep::LFDIType getLFDI();

        boost::beast::http::response<boost::beast::http::dynamic_body> Get(
            const std::string &target, const std::string &query = "") override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Post(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Put(
            const std::string &target, const std::string &resource) override;

        boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
            const std::string &target) override;

    protected:
        SingleClient(const Context &context);
        ~SingleClient() noexcept;

    private:
        Client client_;
    };

} // namespace https

#endif // __HTTPS_CLIENT_H__