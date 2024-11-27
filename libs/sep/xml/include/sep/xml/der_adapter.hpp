#ifndef __DER_ADAPTER_H__
#define __DER_ADAPTER_H__

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sep/models/der.hpp>

namespace xml {
void ObjectMap(const boost::property_tree::ptree &pt, sep::DER *der);
void TreeMap(const sep::DER &der, boost::property_tree::ptree *pt);

std::string Serialize(const sep::DER &tm);
void Parse(const std::string &xml_str, sep::DER *der);

std::string Serialize(const sep::DERList &list);
void Parse(const std::string &xml_str, sep::DERList *list);
} // namespace xml

#endif // __DER_ADAPTER_H__
