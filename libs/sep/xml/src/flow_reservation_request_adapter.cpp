#include <boost/foreach.hpp>
#include <sep/xml/flow_reservation_request_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt,
               sep::FlowReservationRequest *frq) {
  std::string path = "FlowReservationRequest.<xmlattr>.href";
  frq->href = pt.get<std::string>(path, "");
  path = "FlowReservationRequest.mRID";
  frq->mrid = xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>(path, ""));
  path = "FlowReservationRequest.description";
  frq->description = pt.get<std::string>(path, "");
  path = "FlowReservationRequest.version";
  frq->version = pt.get<sep::UInt16>(path, 0);
  path = "FlowReservationRequest.creationTime";
  frq->creation_time = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationRequest.durationRequested";
  if (auto duration = pt.get_optional<sep::UInt16>(path)) {
    frq->duration_requested.emplace(duration.value());
  }
  path = "FlowReservationRequest.energyRequested.multiplier";
  frq->energy_requested.multiplier =
      pt.get<sep::PowerOfTenMultiplierType>(path, 0);
  path = "FlowReservationRequest.energyRequested.value";
  frq->energy_requested.value = pt.get<sep::UInt64>(path, 0);
  path = "FlowReservationRequest.intervalRequested.duration";
  frq->interval_requested.duration = pt.get<sep::Int32>(path, 0);
  path = "FlowReservationRequest.intervalRequested.start";
  frq->interval_requested.start = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationRequest.powerRequested.multiplier";
  frq->power_requested.multiplier =
      pt.get<sep::PowerOfTenMultiplierType>(path, 0);
  path = "FlowReservationRequest.powerRequested.value";
  frq->power_requested.value = pt.get<sep::Int16>(path, 0);
  path = "FlowReservationRequest.RequestStatus.dateTime";
  frq->request_status.datetime = pt.get<sep::TimeType>(path, 0);
  path = "FlowReservationRequest.RequestStatus.requestStatus";
  frq->request_status.status =
      static_cast<sep::RequestStatus::Status>(pt.get<sep::UInt8>(path, 0));
};

void TreeMap(const sep::FlowReservationRequest &frq,
             boost::property_tree::ptree *pt) {
  std::string path = "FlowReservationRequest.<xmlattr>.href";
  pt->put(path, frq.href);
  path = "FlowReservationRequest.mRID";
  pt->put(path, xml::util::Hexify(frq.mrid));
  path = "FlowReservationRequest.description";
  pt->put(path, frq.description);
  path = "FlowReservationRequest.version";
  pt->put(path, frq.version);
  path = "FlowReservationRequest.creationTime";
  pt->put(path, frq.creation_time);
  if (frq.duration_requested.is_initialized()) {
    path = "FlowReservationRequest.durationRequested";
    pt->put(path, frq.duration_requested.value());
  }
  path = "FlowReservationRequest.energyRequested.multiplier";
  pt->put(path, frq.energy_requested.multiplier);
  path = "FlowReservationRequest.energyRequested.value";
  pt->put(path, frq.energy_requested.value);
  path = "FlowReservationRequest.intervalRequested.duration";
  pt->put(path, frq.interval_requested.duration);
  path = "FlowReservationRequest.intervalRequested.start";
  pt->put(path, frq.interval_requested.start);
  path = "FlowReservationRequest.powerRequested.multiplier";
  pt->put(path, frq.power_requested.multiplier);
  path = "FlowReservationRequest.powerRequested.value";
  pt->put(path, frq.power_requested.value);
  path = "FlowReservationRequest.RequestStatus.dateTime";
  pt->put(path, frq.request_status.datetime);
  path = "FlowReservationRequest.RequestStatus.requestStatus";
  pt->put(path, xml::util::ToUnderlyingType(frq.request_status.status));
};

std::string Serialize(const sep::FlowReservationRequest &frq) {
  boost::property_tree::ptree pt;
  TreeMap(frq, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::FlowReservationRequest *frq) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, frq);
};

std::string Serialize(const sep::FlowReservationRequestList &frq_list) {
  boost::property_tree::ptree pt;
  pt.put("FlowReservationRequestList.<xmlattr>.all", frq_list.all);
  pt.put("FlowReservationRequestList.<xmlattr>.results",
         frq_list.flow_reservation_requests.size());
  pt.put("FlowReservationRequestList.<xmlattr>.href", frq_list.href);
  pt.put("FlowReservationRequestList.<xmlattr>.pollRate", frq_list.poll_rate);

  for (const auto &frq : frq_list.flow_reservation_requests) {
    boost::property_tree::ptree pt2;
    TreeMap(frq, &pt2);
    pt.add_child("FlowReservationRequestList.FlowReservationRequest",
                 pt2.get_child("FlowReservationRequest"));
  }

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str,
           sep::FlowReservationRequestList *frq_list) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  frq_list->all =
      pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.all", 0);
  frq_list->href =
      pt.get<std::string>("FlowReservationRequestList.<xmlattr>.href", "");
  frq_list->results =
      pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.results", 0);
  frq_list->poll_rate =
      pt.get<sep::UInt32>("FlowReservationRequestList.<xmlattr>.pollRate", 900);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree,
                 pt.get_child("FlowReservationRequestList")) {
    if (subtree.first == "FlowReservationRequest") {
      boost::property_tree::ptree temp;
      temp.add_child("FlowReservationRequest", subtree.second);

      sep::FlowReservationRequest frq;
      ObjectMap(temp, &frq);
      frq_list->flow_reservation_requests.emplace_back(frq);
    }
  }
};
} // namespace xml