#ifndef __TRUST_XML_H__
#define __TRUST_XML_H__

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <map>

namespace dtm
{
    struct Message
    {
        std::string to;
        std::string from;
        std::string command;
        std::map<std::string, std::string> args;
        // TODO std::string expected;
        uint64_t timestamp;
    };

    boost::property_tree::ptree Treeify(const Message& message);
    std::string Stringify(const boost::property_tree::ptree& pt);
} // namespace dtm

#endif // __TRUST_struct Message