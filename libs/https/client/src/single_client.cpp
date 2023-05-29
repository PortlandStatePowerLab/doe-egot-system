#define BOOST_BIND_GLOBAL_PLACEHOLDERS // had to to remove boost warning
#include <https/client/single_client.hpp>
#include <sep/xml/adapter.hpp>

// alias to make things easier to read
namespace bb = boost::beast;
namespace net = boost::asio;
namespace ssl = net::ssl;

static bool initialized_s;

namespace https
{
    SingleClient::SingleClient(const Context &context) : client_(context)
    {
        // do nothing
    }

    SingleClient::~SingleClient()
    {
        // do nothing
    }

    SingleClient &SingleClient::getInstance(const Context &context)
    {
        if (context.host != "" && !initialized_s)
        {
            initialized_s = true;
        }

        if (initialized_s)
        {
            static SingleClient instance(context);
            return instance;
        }            
        
        throw "SingleClient must be initialized with context first!";
    };

    sep::HexBinary160 SingleClient::getLFDI()
    {
        return client_.getLFDI();
    };

    bb::http::response<bb::http::dynamic_body>
    SingleClient::Get(const std::string &target, const std::string &query)
    {
        return client_.Get(target, query);
    }

    bb::http::response<bb::http::dynamic_body>
    SingleClient::Post(const std::string &target, const std::string &resource)
    {
        return client_.Post(target, resource);
    }

    bb::http::response<bb::http::dynamic_body>
    SingleClient::Put(const std::string &target, const std::string &resource)
    {
        return client_.Put(target, resource);
    }

    bb::http::response<bb::http::dynamic_body>
    SingleClient::Delete(const std::string &target)
    {
        return client_.Delete(target);
    }

} // namespace https