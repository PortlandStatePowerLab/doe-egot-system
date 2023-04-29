#ifndef __FLOW_RESERVATION_REQUEST_ADAPTER_H__
#define __FLOW_RESERVATION_REQUEST_ADAPTER_H__

#include <ieee-2030.5/flow_reservation_request.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap (const boost::property_tree::ptree &pt, sep::FlowReservationRequest *frq);
    void TreeMap (const sep::FlowReservationRequest &frq, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::FlowReservationRequest &frq);
    void Parse(const std::string &xml_str, sep::FlowReservationRequest *frq);

    std::string Serialize(const sep::FlowReservationRequestList &frq_list);    
    void Parse(const std::string &xml_str, sep::FlowReservationRequestList *frq_list);
} // namespace xml

#endif // __FLOW_RESERVATION_REQUEST_ADAPTER_H__