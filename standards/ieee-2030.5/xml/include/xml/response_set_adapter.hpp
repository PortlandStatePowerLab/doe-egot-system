#ifndef __RESPONSE_SET_ADAPTER_H__
#define __RESPONSE_SET_ADAPTER_H__

#include "utilities.hpp"
#include <ieee-2030.5/models.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::ResponseSet *rsps);
    void TreeMap(const sep::ResponseSet &rsps, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::ResponseSet &rsps);
    void Parse (const std::string &xml_str, sep::ResponseSet* rsps);

    std::string Serialize(const std::vector<sep::ResponseSet> &rsps_list);    
    void Parse(const std::string &xml_str, std::vector<sep::ResponseSet> *rsps_list);
} // namespace xml

#endif // __RESPONSE_SET_ADAPTER_H__