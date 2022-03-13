#ifndef __DEVICE_CAPABILITY_H__
#define __DEVICE_CAPABILITY_H__
#include <cstdint>
#include <string>
#include "list_link.hpp"
#include "function_set_assignments_base.hpp"

namespace sep
{
    // Returned by the URI provided by DNS-SD, to allow clients to find the URIs 
    // to the resources in which they are interested.
    struct DeviceCapability : FunctionSetAssignmentsBase
    {
        uint32_t poll_rate = 900;
        ListLink end_device_list_link;
        ListLink mirror_usage_point_list_link;
        Link self_device_link;

        friend bool operator == (const DeviceCapability& lhs, const DeviceCapability& rhs)
        {
            return 
                (lhs.customer_account_list_link.all == rhs.customer_account_list_link.all)
                && (lhs.customer_account_list_link.href == rhs.customer_account_list_link.href)
                && (lhs.demand_response_program_list_link.all == rhs.demand_response_program_list_link.all)
                && (lhs.demand_response_program_list_link.href == rhs.demand_response_program_list_link.href)
                && (lhs.der_program_list_link.all == rhs.der_program_list_link.all)
                && (lhs.der_program_list_link.href == rhs.der_program_list_link.href)
                && (lhs.end_device_list_link.all == rhs.end_device_list_link.all)
                && (lhs.end_device_list_link.href == rhs.end_device_list_link.href)
                && (lhs.file_list_link.all == rhs.file_list_link.all)
                && (lhs.file_list_link.href == rhs.file_list_link.href)
                && (lhs.href == rhs.href)
                && (lhs.messaging_program_list_link.all == rhs.messaging_program_list_link.all)
                && (lhs.messaging_program_list_link.href == rhs.messaging_program_list_link.href)
                && (lhs.mirror_usage_point_list_link.all == rhs.mirror_usage_point_list_link.all)
                && (lhs.mirror_usage_point_list_link.href == rhs.mirror_usage_point_list_link.href)
                && (lhs.poll_rate == rhs.poll_rate)
                && (lhs.prepayment_list_link.all == rhs.prepayment_list_link.all)
                && (lhs.prepayment_list_link.href == rhs.prepayment_list_link.href)
                && (lhs.response_set_list_link.all == rhs.response_set_list_link.all)
                && (lhs.response_set_list_link.href == rhs.response_set_list_link.href)
                && (lhs.self_device_link.href == rhs.self_device_link.href);
        };
    };
} // namespace sep

#endif // __DEVICE_CAPABILITY_H__