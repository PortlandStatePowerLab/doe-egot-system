#ifndef __DER_H__
#define __DER_H__
#include "subscribable_resource.hpp"
#include "associated_der_program_list_link.hpp"
#include "associated_usage_program_link.hpp"
#include "current_der_program_link.hpp"
#include "list_link.hpp"

namespace sep
{
    // Contains links to DER resources.
    struct DER : SubscribableResource
    {
        ListLink associated_der_program_list_link;
        Link associated_usage_program_link;
        Link current_der_program_link;
        Link der_availability_link;
        Link der_capability_link;
        Link der_settings_link;
        Link der_status_link;
    };
    
} // namespace sep

#endif // __DER_H__