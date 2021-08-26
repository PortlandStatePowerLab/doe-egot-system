#ifndef __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#define __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#include <string>
#include "resource.hpp"

namespace sep
{
    // Defines a collection of function set instances that are to be used by one or more 
    // devices as indicated by the EndDevice object(s) of the server.
    struct FunctionSetAssignmentsBase : Resource
    {
        std::string customer_account_list_link;
        std::string demand_response_program_list_link;
        std::string der_program_list_link;
        std::string file_list_link;
        std::string messaging_program_list_link;
        std::string prepayment_list_link;
        std::string response_set_list_link;
        std::string tariff_profile_list_link;
        std::string time_link;
        std::string usage_point_list_link;
    };
    
} // namespace sep

#endif // __FUNCTION_SET_ASSIGNMENTS_BASE_H__