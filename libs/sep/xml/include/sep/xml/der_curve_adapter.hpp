#ifndef __DER_CURVE_ADAPTER_H__
#define __DER_CURVE_ADAPTER_H__

#include <sep/models/der_curve.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::DERCurve *dc);
    void TreeMap(const sep::DERCurve &dc, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::DERCurve &dc);
    void Parse(const std::string &xml_str, sep::DERCurve *dc);
} // namespace xml

#endif // __DER_CURVE_ADAPTER_H__