#include <boost/optional.hpp>
#include <sep/models/simple_types.hpp>
#include <sep/xml/der_status_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DERStatus *ders) {
  std::string path = "DERStatus.<xmlattr>.href";
  ders->href = pt.get<std::string>(path);

  path = "DERStatus.<xmlatter>.subscribable";
  ders->subscribable =
      static_cast<sep::SubscribableType>(pt.get<sep::UInt8>(path, 0));

  path = "DERStatus.readingTime";
  ders->reading_time = pt.get<sep::TimeType>(path);

  path = "DERStatus.alarmStatus";
  if (auto opt = pt.get_optional<std::string>(path)) {
    auto obj = static_cast<sep::DERStatus::AlarmStatus>(
        util::Dehexify<sep::HexBinary16>(opt.value()));
    ders->alarm_status = obj;
  }

  path = "DERStatus.genConnectStatus";
  if (auto child = pt.get_child_optional(path)) {
    sep::ConnectStatusType obj;
    obj.date_time = child.value().get<sep::TimeType>("dateTime", 0);
    obj.value = static_cast<sep::ConnectStatusType::Status>(
        util::Dehexify<sep::HexBinary16>(
            child.value().get<std::string>("value", "")));
    ders->gen_connection_status = obj;
  }

  path = "DERStatus.inverterStatus";
  if (auto child = pt.get_child_optional(path)) {
    sep::InverterStatusType obj;
    obj.date_time = child.value().get<sep::TimeType>("dateTime", 0);
    obj.value = static_cast<sep::InverterStatusType::Status>(
        child.value().get<sep::UInt8>("value", 0));
    ders->inverter_status = obj;
  }

  path = "DERStatus.localControlModeStatus";
  if (auto child = pt.get_child_optional(path)) {
    sep::LocalControlModeStatusType obj;
    obj.date_time = child.value().get<sep::TimeType>("dateTime", 0);
    obj.value = static_cast<sep::LocalControlModeStatusType::ControlStatus>(
        child.value().get<sep::UInt8>("value", 0));
    ders->local_control_mode_status = obj;
  }
  path = "DERStatus.manufacturerStatus";
  if (auto child = pt.get_child_optional(path)) {
    sep::ManufacturerStatusType obj;
    obj.date_time = child.value().get<sep::TimeType>("dateTime", 0);
    obj.value = child.value().get<sep::String6>("value", "");
    ders->manufacturer_status = obj;
  }

  path = "DERStatus.operationalModeStatus";
  if (auto child = pt.get_child_optional(path)) {
    auto dt = child.value().get<sep::TimeType>("dateTime", 0);
    auto val = child.value().get<sep::UInt8>("value", 0);
    sep::OperationalModeStatusType obj;
    obj.date_time = dt;
    obj.value = static_cast<sep::OperationalModeStatusType::Status>(val);
    ders->operational_mode_status = obj;
  }

  path = "DERStatus.stateOfChargeStatus";
  if (auto child = pt.get_child_optional(path)) {
    auto dt = child.value().get<sep::TimeType>("dateTime", 0);
    auto val = child.value().get<sep::PerCent>("value", 0);
    sep::StateOfChargeStatusType obj;
    obj.date_time = dt;
    obj.value = val;
    ders->state_of_charge_status = obj;
  }

  path = "DERStatus.storageModeStatus";
  if (auto child = pt.get_child_optional(path)) {
    auto dt = child.value().get<sep::TimeType>("dateTime", 0);
    auto val = child.value().get<sep::UInt8>("value", 0);
    sep::StorageModeStatusType obj;
    obj.date_time = dt;
    obj.value = static_cast<sep::StorageModeStatusType::Status>(val);
    ders->storage_mode_status = obj;
  }

  path = "DERStatus.storConnectStatus";
  if (auto child = pt.get_child_optional(path)) {
    auto dt = child.value().get<sep::TimeType>("dateTime", 0);
    auto val = child.value().get<std::string>("value", "");
    sep::ConnectStatusType obj;
    obj.date_time = dt;
    obj.value = static_cast<sep::ConnectStatusType::Status>(
        util::Dehexify<sep::HexBinary16>(val));
    ders->stor_connect_status = obj;
  }
};

void TreeMap(const sep::DERStatus &ders, boost::property_tree::ptree *pt) {
  std::string path = "DERStatus.<xmlattr>.href";
  pt->put(path, ders.href);

  path = "DERStatus.<xmlattr>.subscribable";
  pt->put(path, util::ToUnderlyingType(ders.subscribable));

  path = "DERStatus.readingTime";
  pt->put(path, ders.reading_time);

  if (ders.alarm_status.is_initialized()) {
    path = "DERStatus.alarmStatus";
    pt->put(path,
            util::Hexify(util::ToUnderlyingType(ders.alarm_status.value())));
  }

  if (ders.gen_connection_status.is_initialized()) {
    path = "DERStatus.genConnectStatus.dateTime";
    pt->put(path, ders.gen_connection_status->date_time);
    path = "DERStatus.genConnectStatus.value";
    pt->put(path, util::Hexify(util::ToUnderlyingType(
                      ders.gen_connection_status->value)));
  }

  if (ders.inverter_status.is_initialized()) {
    path = "DERStatus.inverterStatus.dateTime";
    pt->put(path, ders.inverter_status->date_time);
    path = "DERStatus.inverterStatus.value";
    pt->put(path, util::ToUnderlyingType(ders.inverter_status->value));
  }

  if (ders.local_control_mode_status.is_initialized()) {
    path = "DERStatus.localControlModeStatus.dateTime";
    pt->put(path, ders.local_control_mode_status->date_time);
    path = "DERStatus.localControlModeStatus.value";
    pt->put(path,
            util::ToUnderlyingType(ders.local_control_mode_status->value));
  }

  if (ders.manufacturer_status.is_initialized()) {
    path = "DERStatus.manufacturerStatus.dateTime";
    pt->put(path, ders.manufacturer_status->date_time);
    path = "DERStatus.manufacturerStatus.value";
    pt->put(path, ders.manufacturer_status->value);
  }

  if (ders.operational_mode_status.is_initialized()) {
    path = "DERStatus.operationalModeStatus.dateTime";
    pt->put(path, ders.operational_mode_status->date_time);
    path = "DERStatus.operationalModeStatus.value";
    pt->put(path, util::ToUnderlyingType(ders.operational_mode_status->value));
  }

  if (ders.state_of_charge_status.is_initialized()) {
    path = "DERStatus.stateOfChargeStatus.dateTime";
    pt->put(path, ders.state_of_charge_status->date_time);
    path = "DERStatus.stateOfChargeStatus.value";
    pt->put(path, ders.state_of_charge_status->value);
  }

  if (ders.storage_mode_status.is_initialized()) {
    path = "DERStatus.storageModeStatus.dateTime";
    pt->put(path, ders.storage_mode_status->date_time);
    path = "DERStatus.storageModeStatus.value";
    pt->put(path, util::ToUnderlyingType(ders.storage_mode_status->value));
  }

  if (ders.stor_connect_status.is_initialized()) {
    path = "DERStatus.storConnectStatus.dateTime";
    pt->put(path, ders.stor_connect_status->date_time);
    path = "DERStatus.storConnectStatus.value";
    pt->put(path, util::Hexify(
                      util::ToUnderlyingType(ders.stor_connect_status->value)));
  }
};

std::string Serialize(const sep::DERStatus &ders) {
  boost::property_tree::ptree pt;
  TreeMap(ders, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
}

void Parse(const std::string &xml_str, sep::DERStatus *ders) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, ders);
}
} // namespace xml
