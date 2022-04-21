#include "include/xml/response_set_adapter.hpp"
#include <boost/foreach.hpp>
#include "include/xml/utilities.hpp"

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::ResponseSet *rsps)
    {
        rsps->href = pt.get<std::string>("ResponseSet.<xmlattr>.href", "");
        rsps->mrid = xml::util::Dehexify<sep::MRIDType>(pt.get<std::string>("ResponseSet.mRID", ""));
        rsps->description = pt.get<std::string>("ResponseSet.description", "");
        rsps->version = pt.get<uint16_t>("ResponseSet.version", 0);
        rsps->response_list_link.all = pt.get<uint32_t>("ResponseSet.ResponseListLink.<xmlattr>.all", 0);
        rsps->response_list_link.href = pt.get<std::string>("ResponseSet.ResponseListLink.<xmlattr>.href", "");
    };

    void TreeMap(const sep::ResponseSet &rsps, boost::property_tree::ptree *pt)
    {
        pt->put("ResponseSet.<xmlattr>.href", rsps.href);
        pt->put("ResponseSet.mRID", xml::util::Hexify(rsps.mrid));
        pt->put("ResponseSet.description", rsps.description);
        pt->put("ResponseSet.version", rsps.version);
        pt->put("ResponseSet.ResponseListLink.<xmlattr>.all", rsps.response_list_link.all);
        pt->put("ResponseSet.ResponseListLink.<xmlattr>.href", rsps.response_list_link.href);
    };

    std::string Serialize(const sep::ResponseSet &rsps)
    {
        boost::property_tree::ptree pt;
        TreeMap(rsps, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse (const std::string &xml_str, sep::ResponseSet* rsps)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, rsps);
    };

    std::string Serialize(const std::vector<sep::ResponseSet> &rsps_list)
    {
        boost::property_tree::ptree pt;
        pt.put("ResponseSetList.<xmlattr>.results", rsps_list.size());

        for (const auto& rsps : rsps_list)
        {
            boost::property_tree::ptree pt2;
            TreeMap(rsps, &pt2);
            pt.add_child("ResponseSetList.ResponseSet", pt2.get_child("ResponseSet"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };  

    void Parse(const std::string &xml_str, std::vector<sep::ResponseSet> *rsps_list)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("ResponseSetList"))
        {
            if (subtree.first == "ResponseSet")
            {
                boost::property_tree::ptree temp;
                temp.add_child("ResponseSet", subtree.second);
                
                sep::ResponseSet rsps;
                ObjectMap(subtree.second, &rsps);
                rsps_list->emplace_back(rsps);
            }
            
        }
    };
} // namespace xml
