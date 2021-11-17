#ifndef __DER_PROGRAM_H__
#define __DER_PROGRAM_H__
#include "subscribable_identified_object.hpp"
#include "active_der_control_list_link.hpp"
#include "default_der_control_link.hpp"
#include "der_control_list_link.hpp"
#include "der_curve_list_link.hpp"
#include "primacy_type.hpp"

namespace sep
{
    // Distributed Energy Resource program
    struct DERProgram : SubscribableIdentifiedObject
    {
        ActiveDERControlListLink active_der_control_list_link;
        DefaultDERControlLink default_der_control_link;
        DERControlListLink der_control_list_link;
        DERCurveListLink der_curve_list_link;
        PrimacyType primacy;
    };
    
} // namespace sep

#endif // __DER_PROGRAM_H__