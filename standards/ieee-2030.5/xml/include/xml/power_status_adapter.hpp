#ifndef __POWER_STATUS_ADAPTER_H__
#define __POWER_STATUS_ADAPTER_H__


#include <ieee-2030.5/models.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::PowerStatus *ps);
    void TreeMap (const sep::PowerStatus &ps, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::PowerStatus &ps);
    void Parse(const std::string &xml_str, sep::PowerStatus *ps);
} // namespace xml

#endif // __POWER_STATUS_ADAPTER_H__