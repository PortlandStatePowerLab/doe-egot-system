#ifndef __DER_CONTROL_H__
#define __DER_CONTROL_H__
#include "der_control_base.hpp"
#include "device_category_type.hpp"
#include "randomizable_event.hpp"
#include "simple_types.hpp"

namespace sep {
struct DERControlListLink : ListLink {};
struct DERControlLink : Link {};

struct ActiveDERControlListLink : ListLink {};
struct ActiveDERControlLink : Link {};

struct DefaultDERControlListLink : ListLink {};
struct DefaultDERControlLink : Link {};

///
/// Distributed Energy Resource (DER) time/event-based control.
///
struct DERControl : RandomizableEvent {
  DERControlBase der_control_base;
  DeviceCategoryType device_category;
};
};     // namespace sep
#endif // __DER_CONTROL_H__
