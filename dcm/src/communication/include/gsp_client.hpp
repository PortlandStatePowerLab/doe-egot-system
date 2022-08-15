#ifndef __GSP_CLIENT_H__
#define __GSP_CLIENT_H__

#include <https/client.hpp>
#include <mutex>

class GSPClient : public https::AbstractClient
{
public:
    GSPClient(GSPClient &other) = delete;           // clonable
    
    void operator=(const GSPClient &) = delete;     // assignable

    static GSPClient* getInstance(const https::Context& context);
    static GSPClient* getInstance();

    boost::beast::http::response<boost::beast::http::dynamic_body> Get(
        const std::string &target, const std::string &query = "") override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Post(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Put(
        const std::string &target, const std::string &resource) override;

    boost::beast::http::response<boost::beast::http::dynamic_body> Delete(
        const std::string &target) override;

protected:
    GSPClient(const https::Context& context);
    ~GSPClient() noexcept;

private:
    static GSPClient *instance_;
    static std::mutex mutex_;
    https::Client client_;
};

#endif // __GSP_CLIENT_H__