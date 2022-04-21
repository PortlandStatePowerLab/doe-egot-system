#ifndef __FLOW_RESERVATION_RESPONSE_ADAPTER_H__
#define __FLOW_RESERVATION_RESPONSE_ADAPTER_H__

#include <ieee-2030.5/models.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::FlowReservationResponse *frp);
    void TreeMap (const sep::FlowReservationResponse &frp, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::FlowReservationResponse &frp);
    void Parse(const std::string &xml_str, sep::FlowReservationResponse *frp);

    std::string Serialize(const std::vector<sep::FlowReservationResponse> &frp_list);    
    void Parse(const std::string &xml_str, std::vector<sep::FlowReservationResponse> *frp_list);
} // namespace xml

#endif // __FLOW_RESERVATION_RESPONSE_ADAPTER_H__