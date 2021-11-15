#ifndef __END_DEVICE_CONTROL_H__
#define __END_DEVICE_CONTROL_H__
#include <cstdint>
#include "randomizable_event.hpp"
#include "appliance_load_reduction_type.hpp"
#include "device_category_type.hpp"
#include "duty_cycle.hpp"
#include "offset.hpp"
#include "set_point.hpp"

namespace sep
{
    // Instructs an EndDevice to perform a specified action.
    struct EndDeviceControl
    {
        sep::RandomizableEvent randomizable_event;
        sep::ApplianceLoadReductionType appliance_load_reduction;
        sep::DeviceCategoryType device_category;
        bool dr_program_mandatory;
        bool load_shift_forward;
        sep::DutyCycle duty_cycle;
        sep::Offset offset;
        uint16_t override_duration;
        sep::SetPoint set_point;
    };    
};     // namespace sep
#endif // __END_DEVICE_CONTROL_H__