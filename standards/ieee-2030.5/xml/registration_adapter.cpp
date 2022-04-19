#include "include/xml/registration_adapter.hpp"

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Registration *rg)
    {
        rg->poll_rate = pt.get<uint32_t>("Registration.<xmlattr>.pollRate", 0);
        rg->href = pt.get<std::string>("Registration.<xmlattr>.href", "");
        rg->date_time_registered = pt.get<sep::TimeType>("Registration.dateTimeRegistered", 0);
        rg->pin = pt.get<sep::PINType>("Registration.pIN", 0);
    };

    void TreeMap(const sep::Registration &rg, boost::property_tree::ptree *pt)
    {
        pt->put("Registration.<xmlattr>.pollRate", rg.poll_rate);
        pt->put("Registration.<xmlattr>.href", rg.href);
        pt->put("Registration.dateTimeRegistered", rg.date_time_registered);
        pt->put("Registration.pIN", rg.pin);
    };

    std::string Serialize(const sep::Registration &rg)
    {
        boost::property_tree::ptree* pt;
        TreeMap(rg, pt);

        xml::util::SetSchema(pt);
        return xml::util::Stringify(pt);
    };

    void Parse (const std::string &xml_str, sep::Registration* rg)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, rg);
    };
} // namespace xml
