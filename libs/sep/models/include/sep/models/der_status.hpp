#ifndef __DER_STATUS_H__
#define __DER_STATUS_H__
#include "connect_status_type.hpp"
#include "inverter_status_type.hpp"
#include "local_control_mode_status_type.hpp"
#include "manufacturer_status_type.hpp"
#include "operational_mode_status_type.hpp"
#include "simple_types.hpp"
#include "state_of_charge_status_type.hpp"
#include "storage_mode_status_type.hpp"
#include "subscribable_resource.hpp"
#include <boost/optional.hpp>

namespace sep {
struct DERStatusLink : Link {};

///
/// DER status information
///
struct DERStatus : SubscribableResource {
  enum class AlarmStatus : HexBinary16 {
    kOverCurrent = 0,
    kOverVoltage = 1 << 0,
    kUnderVoltage = 1 << 1,
    kOverFrequency = 1 << 2,
    kUnderFrequency = 1 << 3,
    kVoltageImbalance = 1 << 4,
    kCurrentImbalance = 1 << 5,
    kEmergencyLocal = 1 << 6,
    kEmergencyRemote = 1 << 7,
    kLowPowerInput = 1 << 8,
    kPhaseRotation = 1 << 9
  };

  TimeType reading_time;
  boost::optional<AlarmStatus> alarm_status;
  boost::optional<ConnectStatusType> gen_connection_status;
  boost::optional<InverterStatusType> inverter_status;
  boost::optional<LocalControlModeStatusType> local_control_mode_status;
  boost::optional<ManufacturerStatusType> manufacturer_status;
  boost::optional<OperationalModeStatusType> operational_mode_status;
  boost::optional<StateOfChargeStatusType> state_of_charge_status;
  boost::optional<StorageModeStatusType> storage_mode_status;
  boost::optional<ConnectStatusType> stor_connect_status;
};

} // namespace sep

#endif // __DER_STATUS_H__
