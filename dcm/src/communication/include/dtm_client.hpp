#ifndef __DTM_CLIENT_H__
#define __DTM_CLIENT_H__

#include <https/client.hpp>
#include <mutex>

class DTMClient : public https::AbstractClient
{
public:
    DTMClient(DTMClient &other) = delete;           // clonable
    
    void operator=(const DTMClient &) = delete;     // assignable

    static DTMClient* getInstance(const https::Context& context);
    static DTMClient* getInstance();

    sep::LFDIType getLFDI() override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

protected:
    DTMClient(const https::Context& context);
    ~DTMClient() noexcept;

private:
    static DTMClient *instance_;
    static std::mutex mutex_;
    https::Client client_;
};


#endif // __DTM_CLIENT_H__