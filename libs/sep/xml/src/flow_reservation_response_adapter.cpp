#include <boost/foreach.hpp>
#include <sep/xml/flow_reservation_response_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt,
               sep::FlowReservationResponse *frp) {
  std::string path = "FlowReservationResponse.<xmlattr>.subscribable";
  frp->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));
  path = "FlowReservationResponse.<xmlattr>.replyTo";
  frp->reply_to = pt.get<std::string>(path, "");
  path = "FlowReservationResponse.<xmlattr>.responseRequired";
  frp->response_required =
      static_cast<sep::RespondableResource::ResponseRequired>(
          pt.get<sep::HexBinary8>(path, 0));
  path = "FlowReservationResponse.<xmlattr>.href";
  frp->href = pt.get<std::string>(path, "");
  path = "FlowReservationResponse.mRID";
  frp->mrid = xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>(path, ""));
  path = "FlowReservationResponse.description";
  frp->description = pt.get<sep::String32>(path, "");
  path = "FlowReservationResponse.version";
  frp->version = pt.get<sep::VersionType>(path, 0);
  path = "FlowReservationResponse.creationTime";
  frp->creation_time = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationResponse.EventStatus.currentStatus";
  frp->event_status.current_status =
      static_cast<sep::EventStatus::CurrentStatus>(pt.get<sep::UInt8>(path, 0));
  path = "FlowReservationResponse.EventStatus.dateTime";
  frp->event_status.date_time = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationResponse.EventStatus.potentiallySuperseded";
  frp->event_status.potentially_superseded = pt.get<bool>(path, false);
  path = "FlowReservationResponse.interval.duration";
  frp->interval.duration = pt.get<sep::Int32>(path, 0);
  path = "FlowReservationResponse.interval.start";
  frp->interval.start = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationResponse.energyAvailable.multiplier";
  frp->energy_available.multiplier =
      pt.get<sep::PowerOfTenMultiplierType>(path, 0);
  path = "FlowReservationResponse.energyAvailable.value";
  frp->energy_available.value = pt.get<sep::Int48>(path, 0);
  path = "FlowReservationResponse.powerAvailable.multiplier";
  frp->power_available.multiplier =
      pt.get<sep::PowerOfTenMultiplierType>(path, 0);
  path = "FlowReservationResponse.powerAvailable.value";
  frp->power_available.value = pt.get<sep::Int16>(path, 0);
  path = "FlowReservationResponse.subject";
  frp->subject = pt.get<sep::mRIDType>(path, 0);
  path = "FlowReservationResponse.EventStatus.potentiallySupersededTime";
  frp->event_status.potentially_superseded_time =
      pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationResponse.EventStatus.reason";
  frp->event_status.reason = pt.get<sep::String192>(path, "");
};

void TreeMap(const sep::FlowReservationResponse &frp,
             boost::property_tree::ptree *pt) {
  std::string path = "FlowReservationResponse.<xmlattr>.subscribable";
  pt->put(path, xml::util::ToUnderlyingType(frp.subscribable));
  path = "FlowReservationResponse.<xmlattr>.replyTo";
  pt->put(path, frp.reply_to);
  path = "FlowReservationResponse.<xmlattr>.responseRequired";
  pt->put(path, xml::util::ToUnderlyingType(frp.response_required));
  path = "FlowReservationResponse.<xmlattr>.href";
  pt->put(path, frp.href);
  path = "FlowReservationResponse.mRID";
  pt->put(path, xml::util::Hexify(frp.mrid));
  path = "FlowReservationResponse.description";
  pt->put(path, frp.description);
  path = "FlowReservationResponse.version";
  pt->put(path, frp.version);
  path = "FlowReservationResponse.creationTime";
  pt->put(path, frp.creation_time);
  path = "FlowReservationResponse.EventStatus.currentStatus";
  pt->put(path, xml::util::ToUnderlyingType(frp.event_status.current_status));
  path = "FlowReservationResponse.EventStatus.dateTime";
  pt->put(path, frp.event_status.date_time);
  path = "FlowReservationResponse.EventStatus.potentiallySuperseded";
  pt->put(path, frp.event_status.potentially_superseded);
  path = "FlowReservationResponse.interval.duration";
  pt->put(path, frp.interval.duration);
  path = "FlowReservationResponse.interval.start";
  pt->put(path, frp.interval.start);
  path = "FlowReservationResponse.energyAvailable.multiplier";
  pt->put(path, frp.energy_available.multiplier);
  path = "FlowReservationResponse.energyAvailable.value";
  pt->put(path, frp.energy_available.value);
  path = "FlowReservationResponse.powerAvailable.multiplier";
  pt->put(path, frp.power_available.multiplier);
  path = "FlowReservationResponse.powerAvailable.value";
  pt->put(path, frp.power_available.value);
  path = "FlowReservationResponse.subject";
  pt->put(path, xml::util::Hexify(frp.subject));
  if (frp.event_status.potentially_superseded_time.has_value()) {
    path = "FlowReservationResponse.EventStatus.potentiallySupersededTime";
    pt->put(path, frp.event_status.potentially_superseded_time.value());
  }
  if (frp.event_status.reason.has_value()) {
    path = "FlowReservationResponse.EventStatus.reason";
    pt->put(path, frp.event_status.reason.value());
  }
};

std::string Serialize(const sep::FlowReservationResponse &frp) {
  boost::property_tree::ptree pt;
  TreeMap(frp, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::FlowReservationResponse *frp) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, frp);
};

std::string Serialize(const sep::FlowReservationResponseList &frp_list) {
  boost::property_tree::ptree pt;
  pt.put("FlowReservationResponseList.<xmlattr>.all", frp_list.all);
  pt.put("FlowReservationResponseList.<xmlattr>.results",
         frp_list.flow_reservation_responses.size());
  pt.put("FlowReservationResponseList.<xmlattr>.href", frp_list.href);
  pt.put("FlowReservationResponseList.<xmlattr>.pollRate", frp_list.poll_rate);

  for (const auto &frp : frp_list.flow_reservation_responses) {
    boost::property_tree::ptree pt2;
    TreeMap(frp, &pt2);
    pt.add_child("FlowReservationResponseList.FlowReservationResponse",
                 pt2.get_child("FlowReservationResponse"));
  }

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str,
           sep::FlowReservationResponseList *frp_list) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  frp_list->all =
      pt.get<sep::UInt32>("FlowReservationResponseList.<xmlattr>.all", 0);
  frp_list->href =
      pt.get<std::string>("FlowReservationResponseList.<xmlattr>.href", "");
  frp_list->results =
      pt.get<sep::UInt32>("FlowReservationResponseList.<xmlattr>.results", 0);
  frp_list->poll_rate = pt.get<sep::UInt32>(
      "FlowReservationResponseList.<xmlattr>.pollRate", 900);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree,
                 pt.get_child("FlowReservationResponseList")) {
    if (subtree.first == "FlowReservationResponse") {
      boost::property_tree::ptree temp;
      temp.add_child("FlowReservationResponse", subtree.second);

      sep::FlowReservationResponse frp;
      ObjectMap(temp, &frp);
      frp_list->flow_reservation_responses.emplace_back(frp);
    }
  }
};

} // namespace xml
