#ifndef __DEVICE_CAPABILITY_ADAPTER_H__
#define __DEVICE_CAPABILITY_ADAPTER_H__

#include <ieee-2030.5/device_capability.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DeviceCapability *dcap);
    void TreeMap(const sep::DeviceCapability &dcap, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DeviceCapability &dcap);
    void Parse(const std::string &xml_str, sep::DeviceCapability *dcap);
} // namespace xml


#endif // __DEVICE_CAPABILITY_ADAPTER_H__