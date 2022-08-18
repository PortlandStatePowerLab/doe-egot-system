#include "include/xml/response_adapter.hpp"
#include <boost/foreach.hpp>
#include "include/xml/utilities.hpp"

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::Response *rsp)
    {
        rsp->href = pt.get<std::string>("Response.<xmlattr>.href", "");
        rsp->created_date_time = pt.get<sep::TimeType>("Response.createdDateTime", 0);
        rsp->end_device_lfdi = xml::util::Dehexify<boost::multiprecision::uint256_t>(pt.get<std::string>("Response.endDeviceLFDI", ""));
        rsp->status = static_cast<sep::Response::Status>(pt.get<uint8_t>("Response.status", 0));
        rsp->subject = xml::util::Dehexify<sep::MRIDType>(pt.get<std::string>("Response.subject", ""));
    };

    void TreeMap(const sep::Response &rsp, boost::property_tree::ptree *pt)
    {
        pt->put("Response.<xmlattr>.href", rsp.href);
        pt->put("Response.createdDateTime", rsp.created_date_time);
        pt->put("Response.endDeviceLFDI", xml::util::Hexify(rsp.end_device_lfdi));
        pt->put("Response.status", xml::util::ToUnderlyingType(rsp.status));
        pt->put("Response.subject", xml::util::Hexify(rsp.subject));
    };

    std::string Serialize(const sep::Response &rsp)
    {
        boost::property_tree::ptree pt;
        TreeMap(rsp, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse (const std::string &xml_str, sep::Response* rsp)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, rsp);
    };

    std::string Serialize(const std::vector<sep::Response> &rsp_list, const sep::List& list)
    {
        boost::property_tree::ptree pt;
        pt.put("ResponseList.<xmlattr>.all", list.all);
        pt.put("ResponseList.<xmlattr>.results", list.results);
        pt.put("ResponseList.<xmlattr>.href", list.href);
        pt.put("ResponseList.<xmlattr>.pollRate", list.inherited_poll_rate);

        for (const auto& rsp : rsp_list)
        {
            boost::property_tree::ptree pt2;
            TreeMap(rsp, &pt2);
            pt.add_child("ResponseList.Response", pt2.get_child("Response"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };  

    void Parse(const std::string &xml_str, std::vector<sep::Response> *rsp_list)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("ResponseList"))
        {
            if (subtree.first == "Response")
            {
                boost::property_tree::ptree temp;
                temp.add_child("Response", subtree.second);
                
                sep::Response rsp;
                ObjectMap(subtree.second, &rsp);
                rsp.inherited_poll_rate = pt.get<uint32_t>("ResponseList.<xmlattr>.pollRate", 900);
                rsp_list->emplace_back(rsp);
            }
            
        }
    };
} // namespace xml
