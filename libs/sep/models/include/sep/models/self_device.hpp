#ifndef __SELF_DEVICE_H__
#define __SELF_DEVICE_H__
#include "abstract_device.hpp"
#include "simple_types.hpp"

namespace sep {
struct SelfDeviceLink : Link {};

///
/// The EndDevice providing the resources available within the
/// DeviceCapabilities.
///
struct SelfDevice : AbstractDevice {
  UInt32 poll_rate = 900;
};

} // namespace sep

#endif // __SELF_DEVICE_H__
