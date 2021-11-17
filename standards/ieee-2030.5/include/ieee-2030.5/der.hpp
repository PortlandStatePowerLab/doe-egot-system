#ifndef __DER_H__
#define __DER_H__
#include "subscribable_resource.hpp"
#include "associated_der_program_list_link.hpp"
#include "associated_usage_program_link.hpp"
#include "current_der_program_link.hpp"
#include "der_availability_link.hpp"
#include "der_capability_link.hpp"
#include "der_settings_link.hpp"
#include "der_status_link.hpp"

namespace sep
{
    // Contains links to DER resources.
    struct DER : SubscribableResource
    {
        AssociatedDERProgramListLink associated_der_program_list_link;
        AssociatedUsageProgramLink associated_usage_program_link;
        CurrentDERProgramLink current_der_program_link;
        DERAvailabilityLink der_availability_link;
        DERCapabilityLink der_capability_link;
        DERSettingsLink der_settings_link;
        DERStatusLink der_status_link;
    };
    
} // namespace sep

#endif // __DER_H__