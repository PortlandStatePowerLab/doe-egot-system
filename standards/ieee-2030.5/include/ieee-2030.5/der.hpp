#ifndef __DER_H__
#define __DER_H__
#include "subscribable_resource.hpp"
#include "der_program.hpp"
#include "der_availability.hpp"
#include "der_capability.hpp"
#include "der_settings.hpp"
#include "der_status.hpp"
#include "usage_point_base.hpp"

namespace sep
{
    struct DERListLink : ListLink {};
    struct DERList : List {};

    // Contains links to DER resources.
    struct DER : SubscribableResource
    {
        AssociatedDERProgramListLink associated_der_program_list_link;
        AssociatedUsagePointLink associated_usage_program_link;
        CurrentDERProgramLink current_der_program_link;
        DERAvailabilityLink der_availability_link;
        DERCapabilityLink der_capability_link;
        DERSettingsLink der_settings_link;
        DERStatusLink der_status_link;
    };
    
} // namespace sep

#endif // __DER_H__