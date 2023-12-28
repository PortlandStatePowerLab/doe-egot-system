#ifndef __FUNCTION_SET_ASSIGNMENTS_ADAPTER_H__
#define __FUNCTION_SET_ASSIGNMENTS_ADAPTER_H__

#include <sep/models/function_set_assignments.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace xml
{
    void ObjectMap(const boost::property_tree::ptree &pt, sep::FunctionSetAssignments *fsa);
    void TreeMap(const sep::FunctionSetAssignments &fsa, boost::property_tree::ptree *pt);

    std::string Serialize(const sep::FunctionSetAssignments &fsa);
    void Parse(const std::string &xml_str, sep::FunctionSetAssignments *fsa);
} // namespace xml

#endif // __FUNCTION_SET_ASSIGNMENTS_ADAPTER_H__