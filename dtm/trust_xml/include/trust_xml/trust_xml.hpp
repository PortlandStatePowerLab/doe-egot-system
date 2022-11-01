#ifndef __TRUST_XML_H__
#define __TRUST_XML_H__

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <map>

namespace trust
{
    struct Message
    {
        std::string to;
        std::string from;
        std::string timestamp;
        std::map<std::string, std::string> contents;
    };

    boost::property_tree::ptree Treeify(const Message& message);
    std::string Stringify(const boost::property_tree::ptree& pt);
    std::string Stringify(const Message& message);
} // namespace trust

#endif // __TRUST_struct Message