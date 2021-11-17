#ifndef __ACTIVE_DER_CONTROL_H__
#define __ACTIVE_DER_CONTROL_H__
#include <cstdint>
#include "subscribable_identified_object.hpp"
#include "der_control_base.hpp"

namespace sep
{
    struct ActiveDERControl : SubscribableIdentifiedObject
    {
        DERControlBase der_control_base;
        uint32_t set_es_delay;
        uint16_t set_es_high_freq;
        uint16_t set_es_high_volt;
        uint16_t set_es_low_freq;
        uint16_t set_es_low_volt;
        uint32_t set_es_ramp_tms;
        uint32_t set_es_random_delay;
        uint16_t set_grad_w;
        uint16_t set_soft_grad_w;    
    };
    
} // namespace sep

#endif // __ACTIVE_DER_CONTROL_H__