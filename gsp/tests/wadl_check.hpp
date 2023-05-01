#ifndef __WADL_CHECK_H__
#define __WADL_CHECK_H__
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/beast/http.hpp>


static bool checkContentType(const std::string &http_content, const std::vector<std::string> &content)
{
    if (content.size() == 0)
    {
        return true;
    }

    bool found = false;
    for (const auto &value : content)
    {
        if (value == http_content)
        {
            found = true;
        }
    }
    return found;
};

static bool checkStatus(unsigned int http_status, const std::vector<unsigned int> &status)
{
    if (status.size() == 0)
    {
        return true;
    }
    
    bool found = false;
    for (const auto &value : status)
    {
        if (value == http_status)
        {
            found = true;
        }
    }
    return found;
};

// fields : location, size, allow, ocntent_type
// params : location, s, a, l, allow
static bool checkParams(const std::vector <std::string>& http_fields, const std::vector<std::string> &params)
{
    if (params.size() == 0)
    {
        return true;
    }
    
    for (const auto &value : params)
    {
        if (value == "s" || value == "a" || value == "l")
        {
            // do nothing
        }
        else
        {
            auto it = std::find(http_fields.begin(), http_fields.end(), value);
            if (it == http_fields.end())
            {
                return false;
            }
        }
    }
    return true;
};

static std::vector <std::string> headerFields (boost::beast::http::response<boost::beast::http::dynamic_body> resp)
{
    std::vector <std::string> fields;
    for (const auto& field : resp)
    {
        fields.emplace_back(field.name_string());
    }
    return fields;
}

#endif // __WADL_CHECK_H__