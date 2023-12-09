#ifndef __APPLIANCE_LOAD_REDUCTION_TYPE_H__
#define __APPLIANCE_LOAD_REDUCTION_TYPE_H__
#include "simple_types.hpp"

namespace sep {
///
/// Parameter requesting the appliance to respond by providing a moderate
/// load reduction for the duration of a delay period.  Typically referring
/// to a “non-emergency” event in which appliances can continue operating
/// if already in a load consuming period.
///
enum class ApplianceLoadReductionType : UInt8 {
  kDelayApplianceLoad,
  kTemporaryApplianceLoadReduction
};

}; // namespace sep

#endif // __APPLIANCE_LOAD_REDUCTION_TYPE_H__
