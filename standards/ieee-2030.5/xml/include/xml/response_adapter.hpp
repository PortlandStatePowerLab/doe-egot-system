#ifndef __RESPONSE_ADAPTER_H__
#define __RESPONSE_ADAPTER_H__

#include <ieee-2030.5/response.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Response *rsp);
    void TreeMap(const sep::Response &rsp, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::Response &rsp);
    void Parse (const std::string &xml_str, sep::Response* rsp);

    std::string Serialize(const sep::ResponseList &rsp_list);    
    void Parse(const std::string &xml_str, sep::ResponseList *rsp_list);
} // namespace xml

#endif // __RESPONSE_ADAPTER_H__