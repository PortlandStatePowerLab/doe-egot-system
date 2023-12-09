#ifndef __END_DEVICE_CONTROL_H__
#define __END_DEVICE_CONTROL_H__
#include "appliance_load_reduction_type.hpp"
#include "device_category_type.hpp"
#include "duty_cycle.hpp"
#include "offset.hpp"
#include "randomizable_event.hpp"
#include "set_point.hpp"
#include "simple_types.hpp"

namespace sep {
///
/// Instructs an EndDevice to perform a specified action.
///
struct EndDeviceControl : RandomizableEvent {
  ApplianceLoadReductionType appliance_load_reduction;
  DeviceCategoryType device_category;
  bool dr_program_mandatory;
  bool load_shift_forward;
  DutyCycle duty_cycle;
  Offset offset;
  UInt16 override_duration;
  SetPoint set_point;
};
};     // namespace sep
#endif // __END_DEVICE_CONTROL_H__
