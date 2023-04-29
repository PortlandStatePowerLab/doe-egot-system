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
            xml::util::Dehexify<sep::HexBinary8>(pt.get<std::string>("FlowReservationResponse.<xmlattr>.responseRequired", "00")));
        frp->href = pt.get<std::string>("FlowReservationResponse.<xmlattr>.href", "");
        frp->mrid = xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>("FlowReservationResponse.mRID", ""));
        frp->description = pt.get<sep::String32>("FlowReservationResponse.description", "");
        frp->version = pt.get<sep::VersionType>("FlowReservationResponse.version", 0);
        frp->creation_time = pt.get<sep::TimeType>("FlowReservationResponse.creationTime", 0);
        frp->event_status.current_status = static_cast<sep::EventStatus::CurrentStatus>(
            pt.get<sep::UInt8>("FlowReservationResponse.EventStatus.currentStatus", 0));
        frp->event_status.date_time = pt.get<sep::TimeType>("FlowReservationResponse.EventStatus.dateTime", 0);
        frp->event_status.potentially_superseded = pt.get<bool>("FlowReservationResponse.EventStatus.potentiallySuperseded", false);
        frp->event_status.potentially_superseded_time = pt.get<sep::TimeType>("FlowReservationResponse.EventStatus.potentiallySupersededTime", 0);
        frp->event_status.reason = pt.get<sep::String192>("FlowReservationResponse.EventStatus.reason", "");
        frp->interval.duration = pt.get<sep::Int32>("FlowReservationResponse.interval.duration", 0);
        frp->interval.start = pt.get<sep::TimeType>("FlowReservationResponse.interval.start", 0);
        frp->energy_available.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationResponse.energyAvailable.multiplier", 0);
        frp->energy_available.value = pt.get<sep::Int48>("FlowReservationResponse.energyAvailable.value", 0);
        frp->power_available.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationResponse.powerAvailable.multiplier", 0);
        frp->power_available.value = pt.get<sep::Int16>("FlowReservationResponse.powerAvailable.value", 0);
        frp->subject = xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>("FlowReservationResponse.subject", ""));
    };

    void TreeMap (const sep::FlowReservationResponse &frp, boost::property_tree::ptree *pt)
    {
        pt->put("FlowReservationResponse.<xmlattr>.subscribable",
            xml::util::ToUnderlyingType(frp.subscribable));
        pt->put("FlowReservationResponse.<xmlattr>.replyTo", frp.reply_to);
        pt->put("FlowReservationResponse.<xmlattr>.responseRequired",
            xml::util::Hexify(xml::util::ToUnderlyingType(frp.response_required)));
        pt->put("FlowReservationResponse.<xmlattr>.href", frp.href);
        pt->put("FlowReservationResponse.mRID", xml::util::Hexify(frp.mrid));
        pt->put("FlowReservationResponse.description", frp.description);
        pt->put("FlowReservationResponse.version", frp.version);
        pt->put("FlowReservationResponse.creationTime", frp.creation_time);
        pt->put("FlowReservationResponse.EventStatus.currentStatus",
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
        pt->put("FlowReservationResponse.subject", xml::util::Hexify(frp.subject));
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

    std::string Serialize(const sep::FlowReservationResponseList& frp_list)
    {
        boost::property_tree::ptree pt;
        pt.put("FlowReservationResponseList.<xmlattr>.all", frp_list.all);
        pt.put("FlowReservationResponseList.<xmlattr>.results", frp_list.flow_reservation_responses.size());
        pt.put("FlowReservationResponseList.<xmlattr>.href", frp_list.href);
        pt.put("FlowReservationResponseList.<xmlattr>.pollRate", frp_list.poll_rate);

        for (const auto& frp : frp_list.flow_reservation_responses)
        {
            boost::property_tree::ptree pt2;
            TreeMap(frp, &pt2);
            pt.add_child("FlowReservationResponseList.FlowReservationResponse", pt2.get_child("FlowReservationResponse"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };  

    void Parse(const std::string &xml_str, sep::FlowReservationResponseList *frp_list)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        frp_list->all = pt.get<sep::UInt32>("FlowReservationResponseList.<xmlattr>.all", 0);
        frp_list->href = pt.get<std::string>("FlowReservationResponseList.<xmlattr>.href", "");
        frp_list->results = pt.get<sep::UInt32>("FlowReservationResponseList.<xmlattr>.results", 0);
        frp_list->poll_rate = pt.get<sep::UInt32>("FlowReservationResponseList.<xmlattr>.pollRate", 900);

        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("FlowReservationResponseList"))
        {
            if (subtree.first == "FlowReservationResponse")
            {
                boost::property_tree::ptree temp;
                temp.add_child("FlowReservationResponse", subtree.second);
                
                sep::FlowReservationResponse frp;
                ObjectMap(temp, &frp);
                frp_list->flow_reservation_responses.emplace_back(frp);
            }
            
        }
    };

} // namespace xml
