#include <sep/xml/flow_reservation_request_adapter.hpp>
#include <sep/xml/utilities.hpp>
#include <boost/foreach.hpp>

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::FlowReservationRequest *frq)
    {
        frq->href = pt.get<std::string>("FlowReservationRequest.<xmlattr>.href", "");
        frq->mrid = xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>("FlowReservationRequest.mRID", ""));
        frq->description = pt.get<std::string>("FlowReservationRequest.description", "");
        frq->version = pt.get<sep::UInt16>("FlowReservationRequest.version", 0);
        frq->creation_time = pt.get<sep::TimeType>("FlowReservationRequest.creationTime", 0);
        frq->duration_requested = pt.get<sep::UInt16>("FlowReservationRequest.durationRequested", 0);
        frq->energy_requested.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.energyRequested.multiplier", 0);
        frq->energy_requested.value = pt.get<sep::UInt64>("FlowReservationRequest.energyRequested.value", 0);
        frq->interval_requested.duration = pt.get<sep::Int32>("FlowReservationRequest.intervalRequested.duration", 0);
        frq->interval_requested.start = pt.get<sep::TimeType>("FlowReservationRequest.intervalRequested.start", 0);
        frq->power_requested.multiplier = pt.get<sep::PowerOfTenMultiplierType>("FlowReservationRequest.powerRequested.multiplier", 0);
        frq->power_requested.value = pt.get<sep::Int16>("FlowReservationRequest.powerRequested.value", 0);
        frq->request_status.datetime = pt.get<sep::TimeType>("FlowReservationRequest.RequestStatus.dateTime", 0);
        frq->request_status.status = static_cast<sep::RequestStatus::Status>(pt.get<uint8_t>("FlowReservationRequest.RequestStatus.requestStatus", 0));
    };

    void TreeMap (const sep::FlowReservationRequest &frq, boost::property_tree::ptree *pt)
    {
        pt->put("FlowReservationRequest.<xmlattr>.href", frq.href);
        pt->put("FlowReservationRequest.mRID", xml::util::Hexify(frq.mrid));
        pt->put("FlowReservationRequest.description", frq.description);
        pt->put("FlowReservationRequest.version", frq.version);
        pt->put("FlowReservationRequest.creationTime", frq.creation_time);
        pt->put("FlowReservationRequest.durationRequested", frq.duration_requested);
        pt->put("FlowReservationRequest.energyRequested.multiplier", frq.energy_requested.multiplier);
        pt->put("FlowReservationRequest.energyRequested.value", frq.energy_requested.value);
        pt->put("FlowReservationRequest.intervalRequested.duration", frq.interval_requested.duration);
        pt->put("FlowReservationRequest.intervalRequested.start", frq.interval_requested.start);
        pt->put("FlowReservationRequest.powerRequested.multiplier", frq.power_requested.multiplier);
        pt->put("FlowReservationRequest.powerRequested.value", frq.power_requested.value);
        pt->put("FlowReservationRequest.RequestStatus.dateTime", frq.request_status.datetime);
        pt->put("FlowReservationRequest.RequestStatus.requestStatus",
            xml::util::ToUnderlyingType(frq.request_status.status));
    };

    std::string Serialize(const sep::FlowReservationRequest &frq)
    {
        boost::property_tree::ptree pt;
        TreeMap(frq, &pt);

        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };

    void Parse(const std::string &xml_str, sep::FlowReservationRequest *frq)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        ObjectMap(pt, frq);
    };

    std::string Serialize(const sep::FlowReservationRequestList &frq_list)
    {
        boost::property_tree::ptree pt;
        pt.put("FlowReservationRequestList.<xmlattr>.all", frq_list.all);
        pt.put("FlowReservationRequestList.<xmlattr>.results", frq_list.flow_reservation_requests.size());
        pt.put("FlowReservationRequestList.<xmlattr>.href", frq_list.href);
        pt.put("FlowReservationRequestList.<xmlattr>.pollRate", frq_list.poll_rate);

        for (const auto& frq : frq_list.flow_reservation_requests)
        {
            boost::property_tree::ptree pt2;
            TreeMap(frq, &pt2);
            pt.add_child("FlowReservationRequestList.FlowReservationRequest", pt2.get_child("FlowReservationRequest"));
        }
        
        xml::util::SetSchema(&pt);
        return xml::util::Stringify(&pt);
    };    

    void Parse(const std::string &xml_str, sep::FlowReservationRequestList *frq_list)
    {
        boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
        frq_list->all = pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.all", 0);
        frq_list->href = pt.get<std::string>("FlowReservationRequestList.<xmlattr>.href", "");
        frq_list->results = pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.results", 0);
        frq_list->poll_rate = pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.pollRate", 900);

        BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree, pt.get_child("FlowReservationRequestList"))
        {
            if (subtree.first == "FlowReservationRequest")
            {
                boost::property_tree::ptree temp;
                temp.add_child("FlowReservationRequest", subtree.second);

                sep::FlowReservationRequest frq;
                ObjectMap(temp, &frq);
                frq_list->flow_reservation_requests.emplace_back(frq);
            }
            
        }
    };
} // namespace xml