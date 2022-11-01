#include "include/xml/flow_reservation_response_adapter.hpp"
#include <boost/foreach.hpp>
#include "include/xml/utilities.hpp"

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::FlowReservationResponse *frp)
    {
        frp->subscribable = static_cast<sep::SubscribableType>(
            pt.get<uint8_t>("FlowReservationResponse.<xmlattr>.subscribable", 0));
        frp->reply_to = pt.get<std::string>("FlowReservationResponse.<xmlattr>.replyTo", "");
        frp->response_required = static_cast<sep::RespondableResource::ResponseRequired>(
            xml::util::Dehexify<uint8_t>(pt.get<std::string>("FlowReservationResponse.<xmlattr>.responseRequired", "00")));
        frp->href = pt.get<std::string>("FlowReservationResponse.<xmlattr>.href", "");
        frp->mrid = xml::util::Dehexify<sep::MRIDType>(pt.get<std::string>("FlowReservationResponse.mRID", ""));
        frp->description = pt.get<std::string>("FlowReservationResponse.description", "");
        frp->version = pt.get<uint16_t>("FlowReservationResponse.version", 0);
        frp->creation_time = pt.get<uint16_t>("FlowReservationResponse.creationTime", 0);
        frp->event_status.current_status = static_cast<sep::CurrentStatus>(
            pt.get<uint8_t>("FlowReservationResponse.EventStatus.currentStatus", 0));
        frp->event_status.date_time = pt.get<uint8_t>("FlowReservationResponse.EventStatus.dateTime", 0);
        frp->event_status.potentially_superseded = pt.get<bool>("FlowReservationResponse.EventStatus.potentiallySuperseded", false);
        frp->event_status.potentially_superseded_time = pt.get<sep::TimeType>("FlowReservationResponse.EventStatus.potentiallySupersededTime", 0);
        frp->event_status.reason = pt.get<std::string>("FlowReservationResponse.EventStatus.reason", "");
        frp->interval.duration = pt.get<uint32_t>("FlowReservationResponse.interval.duration", 0);
        frp->interval.start = pt.get<sep::TimeType>("FlowReservationResponse.interval.start", 0);
        frp->energy_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.energyAvailable.multiplier", 0);
        frp->energy_available.value = pt.get<int64_t>("FlowReservationResponse.energyAvailable.value", 0);
        frp->power_available.multiplier = pt.get<uint8_t>("FlowReservationResponse.powerAvailable.multiplier", 0);
        frp->power_available.value = pt.get<int16_t>("FlowReservationResponse.powerAvailable.value", 0);
        frp->subject = pt.get<std::string>("FlowReservationResponse.subject", "");
    };

    void TreeMap (const sep::FlowReservationResponse &frp, boost::property_tree::ptree *pt)
    {
        pt->put(
            "FlowReservationResponse.<xmlattr>.subscribable",
            xml::util::ToUnderlyingType(frp.subscribable));
        pt->put("FlowReservationResponse.<xmlattr>.replyTo", frp.reply_to);
        pt->put(
            "FlowReservationResponse.<xmlattr>.responseRequired",
            xml::util::Hexify(xml::util::ToUnderlyingType(frp.response_required)));
        pt->put("FlowReservationResponse.<xmlattr>.href", frp.href);
        pt->put("FlowReservationResponse.mRID", xml::util::Hexify(frp.mrid));
        pt->put("FlowReservationResponse.description", frp.description);
        pt->put("FlowReservationResponse.version", frp.version);
        pt->put("FlowReservationResponse.creationTime", frp.creation_time);
        pt->put(
            "FlowReservationResponse.EventStatus.currentStatus",
            xml::util::ToUnderlyingType(frp.event_status.current_status));
        pt->put("FlowReservationResponse.EventStatus.dateTime", frp.event_status.date_time);
        pt->put("FlowReservationResponse.EventStatus.potentiallySuperseded", frp.event_status.potentially_superseded);
        pt->put("FlowReservationResponse.EventStatus.potentiallySupersededTime", frp.event_status.potentially_superseded_time);
        pt->put("FlowReservationResponse.EventStatus.reason", frp.event_status.reason);
        pt->put("FlowReservationResponse.interval.duration", frp.interval.duration);
        pt->put("FlowReservationResponse.interval.start", frp.interval.start);
        pt->put("FlowReservationResponse.energyAvailable.multiplier", frp.energy_available.multiplier);
        pt->put("FlowReservationResponse.energyAvailable.value", frp.energy_available.value);
        pt->put("FlowReservationResponse.powerAvailable.multiplier", frp.power_available.multiplier);
        pt->put("FlowReservationResponse.powerAvailable.value", frp.power_available.value);
        pt->put("FlowReservationResponse.subject", frp.subject);
    };

    std::string Serialize(const sep::FlowReservationResponse &frp)
    {
        boost::property_tree::ptree pt;
        TreeMap(frp, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, sep::FlowReservationResponse *frp)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, frp);
    };

    std::string Serialize(const std::vector<sep::FlowReservationResponse> &frp_list, const sep::List& list)
    {
        boost::property_tree::ptree pt;
        pt.put("FlowReservationResponseList.<xmlattr>.all", list.all);
        pt.put("FlowReservationResponseList.<xmlattr>.results", list.results);
        pt.put("FlowReservationResponseList.<xmlattr>.href", list.href);
        pt.put("FlowReservationResponseList.<xmlattr>.pollRate", list.inherited_poll_rate);

        for (const auto& frp : frp_list)
        {
            boost::property_tree::ptree pt2;
            TreeMap(frp, &pt2);
            pt.add_child("FlowReservationResponseList.FlowReservationResponse", pt2.get_child("FlowReservationResponse"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };  

    void Parse(const std::string &xml_str, std::vector<sep::FlowReservationResponse> *frp_list)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("FlowReservationResponseList"))
        {
            if (subtree.first == "FlowReservationResponse")
            {
                boost::property_tree::ptree temp;
                temp.add_child("FlowReservationResponse", subtree.second);
                
                sep::FlowReservationResponse frp;
                ObjectMap(temp, &frp);
                frp.inherited_poll_rate = pt.get<uint32_t>("FlowReservationResponseList.<xmlattr>.pollRate", 900);
                frp_list->emplace_back(frp);
            }
            
        }
    };

} // namespace xml
