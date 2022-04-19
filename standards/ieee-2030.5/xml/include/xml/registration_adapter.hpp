#ifndef __REGISTRATION_ADAPTER_H__
#define __REGISTRATION_ADAPTER_H__

#include "utilities.hpp"
#include <ieee-2030.5/models.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Registration *rg);
    void TreeMap(const sep::Registration &rg, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::Registration &rg);
    void Parse (const std::string &xml_str, sep::Registration* rg);
} // namespace xml

#endif // __REGISTRATION_ADAPTER_H__