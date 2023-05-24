#include <boost/foreach.hpp>
#include <sep/xml/response_set_adapter.hpp>
#include <sep/xml/utilities.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::ResponseSet *rsps) {
  std::string path = "ResponseSet.<xmlattr>.href";
  rsps->href = pt.get<std::string>(path, "");
  path = "ResponseSet.mRID";
  rsps->mrid = pt.get<sep::mRIDType>(path, 0);
  path = "ResponseSet.description";
  if (auto description = pt.get_optional<sep::String32>(path)) {
    rsps->description.value() = description.value();
  }
  path = "ResponseSet.version";
  if (auto version = pt.get_optional<sep::VersionType>(path)) {
    rsps->version.value() = version.value();
  }
  path = "ResponseSet.ResponseListLink.<xmlattr>.href";
  if (auto href = pt.get_optional<std::string>(path)) {
    rsps->response_list_link.value().href = href.value();
  }
  path = "ResponseSet.ResponseListLink.<xmlattr>.all";
  if (auto all = pt.get_optional<sep::UInt32>(path)) {
    rsps->response_list_link.value().all = all.value();
  }
};

void TreeMap(const sep::ResponseSet &rsps, boost::property_tree::ptree *pt) {
  std::string path = "ResponseSet.<xmlattr>.href";
  pt->put(path, rsps.href);
  path = "ResponseSet.mRID";
  pt->put(path, xml::util::Hexify(rsps.mrid));
  if (rsps.description.has_value()) {
    path = "ResponseSet.description";
    pt->put(path, rsps.description.value());
  }
  if (rsps.version.has_value()) {
    path = "ResponseSet.version";
    pt->put(path, rsps.version.value());
  }
  if (rsps.response_list_link.has_value()) {
    path = "ResponseSet.ResponseListLink.<xmlattr>.all";
    pt->put(path, rsps.response_list_link.value().all);
    path = "ResponseSet.ResponseListLink.<xmlattr>.href";
    pt->put(path, rsps.response_list_link.value().href);
  }
};

std::string Serialize(const sep::ResponseSet &rsps) {
  boost::property_tree::ptree pt;
  TreeMap(rsps, &pt);

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::ResponseSet *rsps) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  ObjectMap(pt, rsps);
};

std::string Serialize(const sep::ResponseSetList &rsps_list) {
  boost::property_tree::ptree pt;
  pt.put("ResponseSetList.<xmlattr>.all", rsps_list.all);
  pt.put("ResponseSetList.<xmlattr>.results", rsps_list.response_sets.size());
  pt.put("ResponseSetList.<xmlattr>.href", rsps_list.href);
  pt.put("ResponseSetList.<xmlattr>.pollRate", rsps_list.poll_rate);

  for (const auto &rsps : rsps_list.response_sets) {
    boost::property_tree::ptree pt2;
    TreeMap(rsps, &pt2);
    pt.add_child("ResponseSetList.ResponseSet", pt2.get_child("ResponseSet"));
  }

  xml::util::SetSchema(&pt);
  return xml::util::Stringify(&pt);
};

void Parse(const std::string &xml_str, sep::ResponseSetList *rsps_list) {
  boost::property_tree::ptree pt = xml::util::Treeify(xml_str);
  rsps_list->all = pt.get<sep::UInt32>("ResponseSetList.<xmlattr>.all", 0);
  rsps_list->href = pt.get<std::string>("ResponseSetList.<xmlattr>.href", "");
  rsps_list->results =
      pt.get<sep::UInt32>("ResponseSetList.<xmlattr>.results", 0);
  rsps_list->poll_rate =
      pt.get<sep::UInt32>("ResponseSetList.<xmlattr>.pollRate", 900);

  BOOST_FOREACH (boost::property_tree::ptree::value_type &subtree,
                 pt.get_child("ResponseSetList")) {
    if (subtree.first == "ResponseSet") {
      boost::property_tree::ptree temp;
      temp.add_child("ResponseSet", subtree.second);

      sep::ResponseSet rsps;
      ObjectMap(subtree.second, &rsps);
      rsps_list->response_sets.emplace_back(rsps);
    }
  }
};
} // namespace xml
