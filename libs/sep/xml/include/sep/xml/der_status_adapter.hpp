#ifndef __DER_STATUS_ADAPTER_H__
#define __DER_STATUS_ADAPTER_H__

#include <sep/models/der_status.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERStatus *ders);
    void TreeMap(const sep::DERStatus &ders, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERStatus &ders);
    void Parse(const std::string &xml_str, sep::DERStatus *ders);
} // namespace xml

#endif // __DER_STATUS_ADAPTER_H__