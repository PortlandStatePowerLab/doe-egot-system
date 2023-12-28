#ifndef __DER_CAPABILITY_ADAPTER_H__
#define __DER_CAPABILITY_ADAPTER_H__

#include <sep/models/der_capability.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERCapability *dercap);
    void TreeMap(const sep::DERCapability &dercap, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERCapability &dercap);
    void Parse(const std::string &xml_str, sep::DERCapability *dercap);
} // namespace xml


#endif // __DER_CAPABILITY_ADAPTER_H__