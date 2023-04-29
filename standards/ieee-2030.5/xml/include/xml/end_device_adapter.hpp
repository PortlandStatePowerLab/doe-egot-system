#ifndef __END_DEVICE_ADAPTER_H__
#define __END_DEVICE_ADAPTER_H__

#include <ieee-2030.5/end_device.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::EndDevice *edev);
    void TreeMap(const sep::EndDevice &edev, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::EndDevice &edev);
    void Parse(const std::string &xml_str, sep::EndDevice *edev);

    std::string Serialize(const sep::EndDeviceList &edev_list);
    void Parse(const std::string &xml_str, sep::EndDeviceList *edevs);
} // namespace xml

#endif // __END_DEVICE_ADAPTER_H__