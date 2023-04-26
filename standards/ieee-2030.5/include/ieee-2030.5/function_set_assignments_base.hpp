#ifndef __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#define __FUNCTION_SET_ASSIGNMENTS_BASE_H__
#include "simple_types.hpp"
#include "customer_account.hpp"
#include "demand_response.hpp"
#include "der_program.hpp"
#include "file.hpp"
#include "messaging_program.hpp"
#include "prepayment.hpp"
#include "response_set.hpp"
#include "tariff_profile.hpp"
#include "time.hpp"

namespace sep
{
    // Defines a collection of function set instances that are to be used by one or more 
    // devices as indicated by the EndDevice object(s) of the server.
    struct FunctionSetAssignmentsBase : Resource
    {
        CustomerAccountListLink customer_account_list_link;
        DemandResponseProgramListLink demand_response_program_list_link;
        DERProgramListLink der_program_list_link;
        FileListLink file_list_link;
        MessagingProgramListLink messaging_program_list_link;
        PrepaymentListLink prepayment_list_link;
        ResponseSetListLink response_set_list_link;
        TariffProfileListLink tariff_profile_list_link;
        TimeLink time_link;
        UsagePointListLink usage_point_list_link;
    };
    
} // namespace sep

#endif // __FUNCTION_SET_ASSIGNMENTS_BASE_H__