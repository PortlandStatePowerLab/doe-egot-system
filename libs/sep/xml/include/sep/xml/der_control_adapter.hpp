#ifndef __DER_CONTROL_ADAPTER_H__
#define __DER_CONTROL_ADAPTER_H__

#include <sep/models/der_control.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERControl *derc);
    void TreeMap(const sep::DERControl &derc, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERControl &derc);
    void Parse(const std::string &xml_str, sep::DERControl *derc);
} // namespace xml


#endif // __DER_CONTROL_ADAPTER_H__