#include <sep/xml/registration_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::Registration *rg) {
  std::string path = "Registration.<xmlattr>.href";
  rg->href = pt.get<std::string>(path, "");
  path = "Registration.<xmlattr>.pollRate";
  rg->poll_rate = pt.get<sep::UInt32>(path, 0);
  path = "Registration.dateTimeRegistered";
  rg->date_time_registered = pt.get<sep::TimeType>(path, 0);
  path = "Registration.pIN";
  rg->pin = pt.get<sep::PINType>(path, 0);
};

void TreeMap(const sep::Registration &rg, boost::property_tree::ptree *pt) {
  std::string path = "Registration.<xmlattr>.pollRate";
  pt->put(path, rg.poll_rate);
  path = "Registration.<xmlattr>.href";
  pt->put(path, rg.href);
  path = "Registration.dateTimeRegistered";
  pt->put(path, rg.date_time_registered);
  path = "Registration.pIN";
  pt->put(path, rg.pin);
};

std::string Serialize(const sep::Registration &rg) {
  boost::property_tree::ptree pt;
  TreeMap(rg, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::Registration *rg) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, rg);
};
} // namespace xml
