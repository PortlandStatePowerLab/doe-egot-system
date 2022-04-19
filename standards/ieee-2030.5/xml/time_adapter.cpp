#include "include/xml/time_adapter.hpp"

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Time *tm)
    {
        tm->poll_rate = pt.get<uint32_t>("Time.<xmlattr>.pollRate", 900);
        tm->href = pt.get<std::string>("Time.<xmlattr>.href", "");
        tm->current_time = pt.get<sep::TimeType>("Time.currentTime", 0);
        tm->dst_end_time = pt.get<sep::TimeType>("Time.dstEndTime", 0);
        tm->dst_offset = pt.get<sep::TimeOffsetType>("Time.dstOffset", 0);
        tm->dst_start_time = pt.get<sep::TimeType>("Time.dstStartTime", 0);
        tm->local_time = pt.get<sep::TimeType>("Time.dstStartTime", 0);
        tm->quality = pt.get<uint8_t>("Time.quality", 7);
        tm->tz_offset = pt.get<sep::TimeOffsetType>("Time.tzOffset", 7);
    };

    void TreeMap(const sep::Time &tm, boost::property_tree::ptree *pt)
    {
        pt->put("Time.<xmlattr>.pollRate", tm.poll_rate);
        pt->put("Time.<xmlattr>.href", tm.href);
        pt->put("Time.currentTime", tm.current_time);
        pt->put("Time.dstEndTime", tm.dst_end_time);
        pt->put("Time.dstOffset", tm.dst_offset);
        pt->put("Time.dstStartTime", tm.dst_start_time);
        pt->put("Time.localTime", tm.local_time);
        pt->put("Time.quality", tm.quality);
        pt->put("Time.tzOffset", tm.tz_offset);
    };

    std::string Serialize(const sep::Time &tm)
    {
        boost::property_tree::ptree* pt;
        TreeMap(tm, pt);

        xml::util::SetSchema(pt);
        return xml::util::Stringify(pt);
    };

    void Parse(const std::string &xml_str, sep::Time *tm)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, tm);
    };
} // namespace xml
