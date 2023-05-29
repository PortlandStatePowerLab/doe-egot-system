#include <boost/foreach.hpp>
#include <sep/xml/response_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::Response *rsp) {
  std::string path = "Response.<xmlattr>.href";
  rsp->href = pt.get<std::string>(path, "");
  path = "Response.createdDateTime";
  if (auto created_datetime = pt.get_optional<sep::TimeType>(path)) {
    rsp->created_date_time.emplace(created_datetime.value());
  }
  path = "Response.endDeviceLFDI";
  rsp->end_device_lfdi =
      xml::util::Dehexify<sep::HexBinary160>(pt.get<std::string>(path, ""));
  path = "Response.status";
  if (auto status = pt.get_optional<sep::UInt8>(path)) {
    rsp->status.emplace(static_cast<sep::Response::Status>(status.value()));
  }
  path = "Response.subject";
  rsp->subject =
      xml::util::Dehexify<sep::mRIDType>(pt.get<std::string>(path, ""));
};

void TreeMap(const sep::Response &rsp, boost::property_tree::ptree *pt) {
  pt->put("Response.<xmlattr>.href", rsp.href);
  if (rsp.created_date_time.is_initialized()) {
    pt->put("Response.createdDateTime", rsp.created_date_time.value());
  }
  pt->put("Response.endDeviceLFDI", xml::util::Hexify(rsp.end_device_lfdi));
  if (rsp.status.is_initialized()) {
    pt->put("Response.status", xml::util::ToUnderlyingType(rsp.status.value()));
  }
  pt->put("Response.subject", xml::util::Hexify(rsp.subject));
};

std::string Serialize(const sep::Response &rsp) {
  boost::property_tree::ptree pt;
  TreeMap(rsp, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::Response *rsp) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, rsp);
};

std::string Serialize(const sep::ResponseList &rsp_list) {
  boost::property_tree::ptree pt;
  pt.put("ResponseList.<xmlattr>.all", rsp_list.all);
  pt.put("ResponseList.<xmlattr>.results", rsp_list.responses.size());
  pt.put("ResponseList.<xmlattr>.href", rsp_list.href);

  for (const auto &rsp : rsp_list.responses) {
    boost::property_tree::ptree pt2;
    TreeMap(rsp, &pt2);
    pt.add_child("ResponseList.Response", pt2.get_child("Response"));
  }

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::ResponseList *rsp_list) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  rsp_list->all = pt.get<sep::UInt32>("ResponseList.<xmlattr>.all", 0);
  rsp_list->href = pt.get<std::string>("ResponseList.<xmlattr>.href", "");
  rsp_list->results = pt.get<sep::UInt32>("ResponseList.<xmlattr>.results", 0);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree,
                 pt.get_child("ResponseList")) {
    if (subtree.first == "Response") {
      boost::property_tree::ptree temp;
      temp.add_child("Response", subtree.second);

      sep::Response rsp;
      ObjectMap(subtree.second, &rsp);
      rsp_list->responses.emplace_back(rsp);
    }
  }
};
} // namespace xml
