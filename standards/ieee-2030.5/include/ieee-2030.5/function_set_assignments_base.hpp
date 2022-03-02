#ifndef __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#define __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#include <string>
#include "resource.hpp"
#include "link.hpp"
#include "list_link.hpp"

namespace sep
{
    // Defines a collection of function set instances that are to be used by one or more 
    // devices as indicated by the EndDevice object(s) of the server.
    struct FunctionSetAssignmentsBase : Resource
    {
        ListLink customer_account_list_link;
        ListLink demand_response_program_list_link;
        ListLink der_program_list_link;
        ListLink file_list_link;
        ListLink messaging_program_list_link;
        ListLink prepayment_list_link;
        ListLink response_set_list_link;
        ListLink tariff_profile_list_link;
        Link time_link;
        ListLink usage_point_list_link;
    };
    
} // namespace sep

#endif // __FUNCTION_SET_ASSIGNMENTS_BASE_H__