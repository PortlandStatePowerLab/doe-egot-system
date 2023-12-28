#ifndef __DER_SETTINGS_ADAPTER_H__
#define __DER_SETTINGS_ADAPTER_H__

#include <sep/models/der_settings.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERSettings *derg);
    void TreeMap(const sep::DERSettings &derg, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERSettings &derg);
    void Parse(const std::string &xml_str, sep::DERSettings *derg);
} // namespace xml

#endif // __DER_SETTINGS_ADAPTER_H__