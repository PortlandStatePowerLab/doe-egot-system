#ifndef __XML_UTILITIES_H__
#define __XML_UTILITIES_H__
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sep/models/simple_types.hpp>
#include <string>
#include <type_traits>
#include <unordered_set>

// C++14 helper
template <class T>
using underlying_type_t = typename std::underlying_type<T>::type;

namespace xml {
namespace util {
///
/// this part overwrite schema info for validation or fills in the attrs that
/// are needed
/// TODO: it would be nice to figure out how to validate without overwriting
/// the xsi stuff
///
static void SetSchema(boost::property_tree::ptree *pt) {
  std::string root = pt->begin()->first;
  pt->put(root + ".<xmlattr>.xmlns", "urn:ieee:std:2030.5:ns");
  pt->put(root + ".<xmlattr>.xmlns:xsi",
          "http://www.w3.org/2001/XMLSchema-instance");
  pt->put(root + ".<xmlattr>.xsi:schemaLocation",
          "urn:ieee:std:2030.5:ns sep.xsd");
};

///
/// utility function to help translate strings to/from objects
///
static boost::property_tree::ptree Treeify(const std::string &xml_str) {
  std::stringstream ss(xml_str);
  boost::property_tree::ptree pt;
  boost::property_tree::xml_parser::read_xml(ss, pt);
  return pt;
};

///
/// utility function to help translate strings to/from objects
///
static std::string Stringify(boost::property_tree::ptree *pt) {
  SetSchema(pt);
  std::stringstream ss;
  boost::property_tree::xml_parser::write_xml(ss, *pt);
  return ss.str();
};

///
/// c++23 helper for c++11
///
template <class Enum> static underlying_type_t<Enum> ToUnderlyingType(Enum e) {
  return static_cast<underlying_type_t<Enum>>(e);
};

///
/// Convert a number into a hex string of any the max boost multiprecision value
///
template <typename T> static std::string Hexify(T number) {
  std::string hex_str;
  bool type_is_number =
      std::is_integral<T>::value || boost::multiprecision::is_number<T>::value;
  if (!type_is_number) {
    return "";
  }

  std::stringstream ss;
  ss << std::uppercase << std::hex << number;
  hex_str = ss.str();

  bool needs_padding = hex_str.length() % 2 > 0;
  if (needs_padding) {
    hex_str.insert(0, "0");
  }

  return hex_str;
};

///
/// Convert a hex value string into a number of the specified template type
///
template <typename T> static T Dehexify(const std::string hexidecimal) {
  T number;
  std::stringstream ss;
  ss << std::hex << hexidecimal;
  ss >> number;
  return number;
};

///
/// IEEE 2030.5 sfdi utility to ensure the sfdi is valid
///
template <typename T> static uint8_t Checksum(T value) {
  T remainder, total;
  for (total = 0; value > 0; value = value / 10) {
    remainder = value % 10;
    total += remainder;
  }

  uint8_t checksum = total % 10;
  return (checksum == 0) ? checksum : 10 - (total % 10);
};

///
/// ensure the sfdi was generated correctly from a lfdi
///
static bool validateSFDI(const uint64_t sfdi) { return Checksum(sfdi) == 0; };

///
/// generate the sfdi for a given lfdi
///
static sep::SFDIType getSFDI(const std::string &lfdi) {
  sep::SFDIType sfdi = Dehexify<uint64_t>(lfdi.substr(0, 9));
  uint8_t checksum = Checksum(sfdi);
  return (sfdi * 10) + checksum;
};

///
/// helper function the generate a pin from the lfdi.
///
/// Note: this should be designated by the ownder of the DER or the server for
/// which the DER interacts.
///
static uint32_t generatePIN(const std::string &lfdi) {
  sep::SFDIType sfdi = Dehexify<sep::SFDIType>(lfdi.substr(0, 9));
  std::string pin = std::to_string(sfdi);
  sfdi = std::stol(pin.substr(0, 5));
  uint8_t checksum = Checksum(sfdi);
  return (sfdi * 10) + checksum;
};

///
/// utility function to recursively walk a tree data structure
///
static void walk_ptree(const boost::property_tree::ptree &tree,
                       const std::string &parent_key,
                       std::unordered_set<std::string> *key_set) {
  if (tree.empty()) {
    key_set->insert(parent_key);
    return;
  }
  for (auto &it : tree) {
    std::string key = parent_key;
    // add a separator between key segments
    if (!key.empty()) {
      key += ".";
    }
    key += it.first;
    walk_ptree(it.second, key, key_set);
  }
};

///
/// utility function to display a given set
///
static void printSet(std::unordered_set<std::string> &key_set) {
  for (auto itr = key_set.begin(); itr != key_set.end(); itr++) {
    std::cout << (*itr) << std::endl;
  }
};
}; // namespace util
}; // namespace xml

#endif // __XML_UTILITIES_H__
