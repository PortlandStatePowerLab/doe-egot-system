
#include <sep/xml/mirror_usage_point_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <boost/foreach.hpp>

using namespace xml;

void ObjectMap(const boost::property_tree::ptree &pt, sep::MirrorUsagePoint *mup)
{
    mup->device_lfdi = xml::util::Dehexify<sep::HexBinary160>(pt.get<std::string>("MirrorUsagePoint.deviceLFDI", ""));
    mup->mirror_meter_reading.last_update_time = pt.get<sep::TimeType>("MirrorUsagePoint.MirrorMeterReading.lastUpdateTime",0);
    mup->post_rate = pt.get<sep::UInt32>("MirrorUsagePoint.postRate",900);
    // TODO
}

void TreeMap(const sep::MirrorUsagePoint &mup, boost::property_tree::ptree *pt)
{

}

std::string Serialize(const sep::MirrorUsagePoint *mup)
{

}

void Parse (const std::string &xml_str, sep::MirrorUsagePoint *mup)
{
    
}

std::string Serialize(const std::vector<sep::MirrorUsagePoint> &mup_list, const sep::List& list)
{

}


void Parse(const std::string &xml_str, std::vector<sep::MirrorUsagePoint> *mups)
{

}
