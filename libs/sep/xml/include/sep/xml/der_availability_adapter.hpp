#ifndef __DEVICE_AVAILABILITY_ADAPTER_H__
#define __DEVICE_AVAILABILITY_ADAPTER_H__

#include <sep/models/der_availability.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERAvailability *dera);
    void TreeMap(const sep::DERAvailability &dera, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERAvailability &dera);
    void Parse(const std::string &xml_str, sep::DERAvailability *dera);
} // namespace xml


#endif // __DEVICE_AVAILABILITY_ADAPTER_H__