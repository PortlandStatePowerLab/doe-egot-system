#ifndef __TIME_ADAPTER_H__
#define __TIME_ADAPTER_H__

#include <ieee-2030.5/models.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Time *tm);
    void TreeMap(const sep::Time &tm, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::Time &tm);
    void Parse(const std::string &xml_str, sep::Time *tm);
} // namespace xml

#endif // __TIME_ADAPTER_H__