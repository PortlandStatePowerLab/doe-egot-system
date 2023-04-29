#ifndef __MIRROR_USAGE_POINT_ADAPTER_H__
#define __MIRROR_USAGE_POINT_ADAPTER_H__
#include <ieee-2030.5/mirror_usage_point.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::MirrorUsagePoint *mup);
    void TreeMap(const sep::MirrorUsagePoint &mup, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::MirrorUsagePoint &mup);
    void Parse(const std::string &xml_str, sep::MirrorUsagePoint *mup);

    std::string Serialize(const sep::MirrorUsagePointList &mup_list);
    void Parse(const std::string &xml_str, sep::MirrorUsagePointList *mups);
} // namespace xml

#endif // __MIRROR_USAGE_POINT_ADAPTER_H__